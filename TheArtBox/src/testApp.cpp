#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {

	// SYSTEM
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofHideCursor();
	ofSetFrameRate(60);
	
	// SCREEN
    ofEnableAlphaBlending();
    ofBackground(100);
    width = ofGetWindowWidth();
    height = ofGetWindowHeight();
	
	// KINECT
	kinect.setRegistration(true);
	kinect.init();	
	kinect.open();
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}
	angle = 23;
	kinect.setCameraTiltAngle(angle);
	
	// OPENCV
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	grayBg.allocate(kinect.width, kinect.height);
	grayDiff.allocate(kinect.width, kinect.height);
	closePoints.allocate(kinect.width, kinect.height, GL_RGBA32F_ARB); 

	nearThreshold = 250;
	farThreshold = 112;
	bLearnBakground = true;
	threshold = 80;
	bThreshWithOpenCV = false;
	minBlob = 25; 
	maxBlob = (kinect.width*kinect.height)/2; 
	
	// STATE
	presenting = true;
	tooSunny = true;
	fboAge = 0; 
	imageTimer = 0; 
	playState = 1;
	currentBrightness = 0;
	targetAlpha = 155;
	
    // XML ASSETS
    assets.loadFile("xml/assets.xml");
    if( assets.loadFile("xml/assets.xml") ) {
        ofLog(OF_LOG_NOTICE, "Loaded xml file !!! \n");
        // Load Fonts
        loadFonts();
        // Load Artist Names
        loadArtists();
        // Load Media Names
        loadAssets();
    }
    else {
        ofLog(OF_LOG_ERROR, "UNABLE to load xml file :( \n");
    }

    //  INDEX
    currentIndex = 0;
    updateCurrentIndex();

    // ASSETS
    brush.loadImage("images/brush.png");
	stamp.loadImage("logo/stamp_white2.png");
	demo.loadMovie("demo/studio_in_the_city_6_promo.mp4");

    // FBO & GLSL SHADER
    setupGL(width, height);
    
    // MEMORY
    checkMemory();

	cout << "Setup Is Done \n" << endl;

}

//--------------------------------------------------------------
void testApp::update() {
	
	// Screen
	ofBackground(0);
	
	// Age FBO
	if(fboAge < 100) {
		fboAge++; 
	}
	
	if(playState < 2) {
		kinect.update();
		if(kinect.isFrameNew()) {	
			
			// RGB
			if(tooSunny) {				
				colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
				colorImg.mirror(false, true);
				grayImage = colorImg;

				// Set Timer For New BG
				if(ofGetMinutes() % 1 == 0) {
					bLearnBakground = true;
				}
				
				// Learn A New Background Image
				if (bLearnBakground == true){
					grayBg = grayImage;		
					bLearnBakground = false;
				}

				// take the abs value of the difference between background and incoming and then threshold:
				grayDiff.absDiff(grayBg, grayImage);
				grayDiff.threshold(threshold);

				// update the cv images
				grayImage.flagImageChanged();
		
				// Find The Blobs
				contourFinder.findContours(grayDiff, minBlob, maxBlob, 20, false);

			}

			// IR
			else {
				grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
				grayImage.mirror(false, true);
				if(bThreshWithOpenCV) {
					grayThreshNear = grayImage;
					grayThreshFar = grayImage;
					grayThreshNear.threshold(nearThreshold, true);
					grayThreshFar.threshold(farThreshold);
					cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
				} 
				else {
					unsigned char * pix = grayImage.getPixels();
					int numPixels = grayImage.getWidth() * grayImage.getHeight();
					for(int i = 0; i < numPixels; i++) {
						if(pix[i] < nearThreshold && pix[i] > farThreshold) {
							pix[i] = 155;
						} else {
							pix[i] = 0;
						}
					}
				}

				// update the cv images
				grayImage.flagImageChanged();
		
				// Find The Blobs
				contourFinder.findContours(grayImage, minBlob, maxBlob, 20, false);
			}

		} // new frame
	
		// Are There Blobs ?
		if (contourFinder.nBlobs > 0 ) {
			// Draw Logo Into FBO and Fade Everything Else
			closePoints.begin();
				ofFill(); 
				ofSetColor(ofColor(0, 2));
				ofRect(0, 0, closePoints.getWidth(), closePoints.getHeight());
				ofSetColor(ofColor::white);
				stamp.draw(75, 0, closePoints.getWidth()- 130, closePoints.getHeight());
			closePoints.end();
		
			// Loop Through All The Blobs
			for (int i = 0; i < contourFinder.nBlobs; i ++) {
				ofVec2f frontPoint = ofVec2f (0, 0); 
				unsigned char * pix = grayImage.getPixels();
				grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height); // ???

				int tempBright;
				int brightPixel = grayImage.getWidth()*contourFinder.blobs[i].boundingRect.getMinY() +contourFinder.blobs[i].boundingRect.getMinX();
				tempBright = pix[brightPixel]; 
		
				for (int j = contourFinder.blobs[i].boundingRect.getMinY(); j <= contourFinder.blobs[i].boundingRect.getMaxY(); j++){ 
					for (int k = contourFinder.blobs[i].boundingRect.getMinX(); k <= contourFinder.blobs[i].boundingRect.getMaxX(); k++){
						int brightestPixelCandidate = (grayImage.getWidth()*j+k);
						if (pix[brightestPixelCandidate] > tempBright) {
							tempBright = pix[brightestPixelCandidate]; 
							frontPoint = ofVec2f(k,j); 
						}
					}
				}

				// Trace The Contour Into A Shape
				ofPath blobShape ; 
				for (int p = 0; p < contourFinder.blobs[i].pts.size(); p++) {
					blobShape.lineTo(contourFinder.blobs[i].pts[p]); 
				}

				// Draw That Shape Into The FBO
				if(fboAge > 90) {
					closePoints.begin();
						ofFill(); 
						ofSetColor(ofColor(0,0,255)); 
						blobShape.setFillColor(ofColor::red); 
						blobShape.draw();  
					closePoints.end(); 
				}
		
				blobShape.clear();
			}
		}
		
		// No Blobs
		else {
			// Still Draw The Logo & Fade
			closePoints.begin();
				ofFill(); 
				ofSetColor(ofColor(0, 2));
				ofRect(0, 0, closePoints.getWidth(), closePoints.getHeight());
				ofSetColor(ofColor::white);
				stamp.draw(75, 0, closePoints.getWidth()- 130, closePoints.getHeight());
			closePoints.end();
		}

		// Update FBOs
		maskFbo.begin();
			ofSetColor(ofColor::aliceBlue); // Color ??
			closePoints.draw(-250, -250, maskFbo.getWidth() + 450, maskFbo.getHeight() +250); // Magic Numbers ??
		maskFbo.end();

		fbo.begin();
			ofClear(0, 0, 0, 0);
			shader.begin();
				shader.setUniformTexture("maskTex", maskFbo.getTextureReference(), 1);
				thumbnail.draw(0, 0);
			shader.end();
		fbo.end();

		// Check Brightness Every Two Seconds
		if(ofGetFrameNum() % 60 == 0) {
			currentBrightness = getCurrentBrightness();
			if(currentBrightness >= targetAlpha) {
				//Play Media
				if (currentAssetIsMovie) {
					video.stop();
					video.setFrame(0);
					video.play(); 
					video.setLoopState(OF_LOOP_NONE);
				}
				else {
					imageTimer = 0; 
				}
				playState = 2;
				currentBrightness = 0;
			}
		}

	} // play state < 2
		
    // Idle Video
	if(currentAssetIsMovie) {
		video.update();
	}

	if(playState == 4) {
		demo.update();
	}


	// Time To Write Soem Diagnostic Info To File
	if(ofGetMinutes() % 10 == 0) {
		// Set File
		ofLogToFile("logs/ArtBoxLog.txt", true);
		
		// FPS
		ofLog() << "Frame Rate is " << ofToString(ofGetFrameRate()) << endl;
		
		// State
		ofLog() << "Current State is " << ofToString(playState) << endl;
		ofLog() << "Presenting State is " << ofToString(int(presenting)) << endl;
		
		
	}


}

//--------------------------------------------------------------
void testApp::draw() {

	// DEBUG VIEW
	if(presenting == false ) {
	
		// Draw IR Images
		kinect.drawDepth(10, 10, 400, 300); // Depth
		kinect.draw(420, 10, 400, 300); // RGB
		contourFinder.draw(10, 320, 400, 300); // Blobs
		closePoints.draw(420, 320, 400, 300); // FBO

		// Draw The CV Images
		colorImg.draw(1100, 10, 400, 300); // RGB
		grayImage.draw(1510, 20, 400, 300); // Grayscale
		grayBg.draw(1100, 280, 400, 300); // Background
		grayDiff.draw(1510, 280, 400, 300); // Difference
	
		// Debug Info
		ofSetColor(255, 255, 255);
		stringstream reportStream;
		reportStream 
		<< "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
		<< "set near threshold " << nearThreshold << " (press: + -)" << endl
		<< "set far threshold " << farThreshold << " (press: < >)" << endl
		<< "num blobs found " << contourFinder.nBlobs << endl
		<< "current brightness is " << currentBrightness << endl
		<< "fps: " << ofGetFrameRate() << endl
		<< "play state is " << playState << endl
		<< "Too Sunny ? = " << int(tooSunny) << endl
		<< "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl;
		if(kinect.hasCamTiltControl()) {
    		reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
			<< "press 1-5 & 0 to change the led mode" << endl;
		}
		ofDrawBitmapString(reportStream.str(), 20, 652);

	} // presenting

	// INTERACTIVE VIEW
	else if(presenting == true && playState == 1) {
		// Draw FBO
		fbo.draw(0, 0, maskFbo.getWidth(), maskFbo.getHeight());
	}

	// PLAYING VIEW
	else if(presenting == true && playState == 2) {
		// Movie
		if (currentAssetIsMovie) {
			video.draw(0, 0, 3240, 1920); 
		}
		
		// Image
		else {
			image.draw(0, 0, 3240, 1920);
			imageTimer++; 
		}

		// Caption
		ofSetColor(0, 255);
		font.drawString(artistNames[currentIndex], 105, ofGetScreenHeight() - 95);
		ofSetColor(255, 255);
		font.drawString(artistNames[currentIndex], 100, ofGetScreenHeight() - 100);

		// DONE ???
		
		// Movie
		if(currentAssetIsMovie) {
			if(video.getIsMovieDone()) {
				cout << "DONE" << endl;
				playState = 1; 
				imageTimer = 0; 
				video.stop(); 
			
				// Increase Play
				currentIndex++;

				// Check Limit
				if(currentIndex >= maxIndex) {
					currentIndex = 0;
				}

				// Update Assets
				updateCurrentIndex();
			}
		}
		
		// Image
		else {
			if (imageTimer > 500 ) {
				cout << "DONE" << endl;
				playState = 1; 
				imageTimer = 0; 
			
				// Increase Play
				currentIndex++;

				// Check Limit
				if(currentIndex >= maxIndex) {
					currentIndex = 0;
				}

				// Update Assets
				updateCurrentIndex();
			}
		}

	} // playback

	// TRAILER VIEW
	else if(presenting == true && playState == 4) {
		if(demo.getIsMovieDone()) {
			playState = 1;
			demo.stop();
		}
		else {
			if(currentAssetIsMovie) {
				video.stop()	;
			}
			demo.draw(0, 0, 3240, 1920); 
		}
	} // trailer

} // draw()



void testApp::autoPlay() {

	if (currentAssetIsMovie) {
		video.stop();
		video.setFrame(0);
		video.play(); 
		video.setLoopState(OF_LOOP_NONE);
	}
	else {
		imageTimer = 0; 
	}

	playState = 2;
	currentBrightness = 0;
}


//--------------------------------------------------------------

// CUSTOM XML FUNCTIONS



void testApp::loadFonts() {

    // Push In
    assets.pushTag("assets");
    assets.pushTag("fonts");

    // Get Font Path
    string fontName = assets.getValue("file", "null", 0);
    ofLog(OF_LOG_NOTICE, "The Name Of The Font Is: " + fontName);


    // Console Padding
    cout << "" << endl;

    // Make Sure Its Valid
    if(fontName.length() > 0) {
        font.loadFont(fontName, 48);
    }

    // Pop Out
    assets.popTag();
    assets.popTag();

}



void testApp::loadArtists() {

    // Push In
    assets.pushTag("assets");
    assets.pushTag("artists");

    // Find Number
    int num = assets.getNumTags("file");
    artistNames.resize(num);

    // Iterate & Assign

    for(int i = 0; i < artistNames.size(); i++) {
        artistNames[i] = assets.getValue("file", "null", i);
        ofLog(OF_LOG_NOTICE, "Name #" + ofToString(i) + " is " + artistNames[i]);
    }

    // Console Padding
    cout << "" << endl;

    // Pop Out
    assets.popTag();
    assets.popTag();


}



void testApp::loadAssets() {

    // Push In
    assets.pushTag("assets");
    assets.pushTag("media");

    // Find Number
    int num = assets.getNumTags("file");
    artistMedia.resize(num);
    maxIndex = num;

    // Iterate & Assign
    for(int i = 0; i < artistMedia.size(); i++) {
        artistMedia[i] = assets.getValue("file", "null", i);
        ofLog(OF_LOG_NOTICE, "File #" + ofToString(i) + " is " + artistMedia[i]);
    }

    // Console Padding
    cout << "" << endl;

    // Pop Out
    assets.popTag();
    assets.popTag();

}



//--------------------------------------------------------------

// CUSTOM IMAGE FUNCTIONS



void testApp::setAssets(int _currentIndex) {



    // Cast to String

    string file = artistMedia[_currentIndex];

    ofLogNotice("File Path Is " + file);



    // Copy & Trim String

    string temp = file;

    temp.erase(temp.begin(), temp.end() - 3);



    // Convert Copy To Uppercase

    string fileExtension = ofToUpper(temp);

    ofLogNotice("Object Is A " + fileExtension + " File ");



    // Video

    if (fileExtension == "MP4" || fileExtension == "MOV") {

        ofLogNotice("FILE IS A MOVIE");

        currentAssetIsMovie = true;



        // Clear Movie ?

        if(video.isLoaded() == true) {

            ofLog(OF_LOG_NOTICE, "Clearing Video Pixels...");

            video.closeMovie();

        }

        else {

            ofLog(OF_LOG_NOTICE, "Video Pixels Already Empty...");

        }



        // Load Movie

        video.loadMovie(artistMedia[_currentIndex]);

		

        video.firstFrame();

		video.setFrame(video.getTotalNumFrames() - 100);

		video.update();

        video.setPaused(true);



    }

    // Image

    else if (fileExtension == "JPG" || fileExtension == "PNG") {

        ofLogNotice("FILE IS AN IMAGE");

        currentAssetIsMovie = false;



        // Clear Image ?

        if(image.bAllocated() == true) {

            ofLog(OF_LOG_NOTICE, "Clearing Image Pixels...");

            image.clear();

        }

        else {

            ofLog(OF_LOG_NOTICE, "Image Pixels Already Empty...");

        }



        // Load Image

        image.loadImage(artistMedia[_currentIndex]);

    }



    // Console Padding

    cout << "" << endl;

}



void testApp::setColourThumbnailImage(int width, int height) {



    // Clear Thumbnail ?

    if(thumbnail.bAllocated() == true) {

        ofLog(OF_LOG_NOTICE, "Clearing Thumbnail Pixels...");

        thumbnail.clear();

    }

    else {

        ofLog(OF_LOG_NOTICE, "Thumbnail Pixels Already Empty...");

    }



    // Set From ofVideoPlayer

    if(currentAssetIsMovie == true) {

        ofLog(OF_LOG_NOTICE, "Setting Thumbnail Pixels From Video");

        thumbnail.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);

        thumbnail.resize(width, height);

    }

    // Set From ofImage

    else {

        ofLog(OF_LOG_NOTICE, "Setting Thumbnail Pixels From Image");

        thumbnail.setFromPixels(image.getPixels(), image.getWidth(), image.getHeight(), OF_IMAGE_COLOR);

        thumbnail.resize(width, height);

    }





}



void testApp::setBlackAndWhiteThumbnailImage(ofImage img) {



    foreground = img;

    foreground.setImageType(OF_IMAGE_GRAYSCALE);



}



void testApp::updateCurrentIndex() {



    // Index

    setAssets(currentIndex);

    // Set Colour Thumbnail

    setColourThumbnailImage(width, height);

    // Convert To Grayscale

    setBlackAndWhiteThumbnailImage(thumbnail);

	

	

	// Clear FBOs

    closePoints.begin();

        ofClear(0,0,0,255);

    closePoints.end();

    maskFbo.begin();

        ofClear(0,0,0,255);

    maskFbo.end();

	currentBrightness = 0;



}





//--------------------------------------------------------------

// CUSTOM GL FUNCTIONS



void testApp::setupGL(int width, int height) {



    // FBOs

    maskFbo.allocate(width, height, GL_RGBA);

    fbo.allocate(width, height, GL_RGBA);



    maskFbo.begin();

        ofClear(0,0,0,255);

    maskFbo.end();



    fbo.begin();

        ofClear(0,0,0,255);

    fbo.end();



    // SHADER

    string shaderProgram = "#version 120\n \

    #extension GL_ARB_texture_rectangle : enable\n \

    \

    uniform sampler2DRect tex0;\

    uniform sampler2DRect maskTex;\

    \

    void main (void){\

    vec2 pos = gl_TexCoord[0].st;\

    \

    vec3 src = texture2DRect(tex0, pos).rgb;\

    float mask = texture2DRect(maskTex, pos).r;\

    \

    gl_FragColor = vec4( src , mask);\

    }";



    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);

    shader.linkProgram();





}



int testApp::getCurrentBrightness() {



    // Counters

    int alpha = 0;

    int count = 0;



    // Convert to Pixels

    ofPixels pixels;

    maskFbo.readToPixels(pixels, 0);



    // Loop Through And Add All The Alpha Values

    for(int x = 0; x < pixels.getWidth(); x += 4) {

        for(int y = 0; y < pixels.getHeight(); y += 4) {

            ofColor c = pixels.getColor(x, y);

            alpha += c.r;

            count++;

        }

    }



    // Average Over the Total Number Of Pixels

    alpha = alpha / count;

    //cout << "ALPHA IS " << alpha << endl;



    return alpha;

}

void testApp::learnBackground() {



}


//--------------------------------------------------------------

// CUSTOM UTILITY FUNCTIONS



void testApp::checkMemory() {



    // Check  Memory

    MEMORYSTATUS memInfo;

    memInfo.dwLength = sizeof(MEMORYSTATUS);

    GlobalMemoryStatus(&memInfo);



    // Virtual Memory

    DWORDLONG totalVirtualMem = memInfo.dwTotalVirtual;

    DWORDLONG totalVirtualMemMB = totalVirtualMem / DIV;

    DWORDLONG virtualMemUsed = memInfo.dwTotalVirtual - memInfo.dwAvailVirtual;

    DWORDLONG virtualMemUsedMB = virtualMemUsed / DIV;

    cout << "Total Virtual Memory Is " << totalVirtualMemMB << " MB (" << (totalVirtualMemMB / 1000) / 1000 << " GB)." << endl;

    cout << "We Are Using " << virtualMemUsedMB  << " MB (" << (virtualMemUsedMB / 1000) / 1000 << " GB) Of That Amount. " << endl;



    // Physical Memory

    DWORDLONG totalPhysMem = memInfo.dwTotalPhys;

    DWORDLONG totalPhysMemMB = totalPhysMem / DIV;

    DWORDLONG physMemUsed = memInfo.dwTotalPhys - memInfo.dwAvailPhys;

    DWORDLONG physMemUsedMB = physMemUsed / DIV;

    cout << "Total Physical Memory Is " << totalPhysMemMB << " MB (" << (totalPhysMemMB / 1000) / 1000 << " GB)." << endl;

    cout << "We Are Using " << physMemUsedMB  << " MB (" << (physMemUsedMB / 1000) / 1000 << " GB) Of That Amount. " << endl;



}



void testApp::getFilesFromFTP() {

   /*

	// Connect

    try {

        client.setup("ftp.memelab.ca", "SITC_APP", "SITC_6");

        client.setVerbose(true);

        cout << "Connection Success! \n" << endl;

    }

    catch (int e) {

        cout << "The Exception #" << e << " Occured." << endl;

    }



    // List Files

    try {

        fileNames = client.list("/");

        cout << "Listing Success! \n" << endl;



        for(int i = 0; i < fileNames.size(); i++) {

            cout << "Item #" << i << " is " << fileNames[i] << "\n" << endl;

        }

    }

    catch(int e) {

        cout << "The Exception #" << e << " Occured." << endl;

    }



    // Get Files

    try {

        client.get("BOXIcon.png", ofToDataPath(""), "/");

        cout << "Downloading Success!" << endl;

    }

    catch(int e) {

        cout << "The Exception #" << e << " Occured." << endl;

    }

	*/



}


//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();

	// stop the thread

    //thread.stopThread();
	
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
		case ' ':
			bThreshWithOpenCV = !bThreshWithOpenCV;
			break;
			
		case '>':
		case '.':
			farThreshold ++;
			if (farThreshold > 255) farThreshold = 255;
			break;
			
		case '<':
		case ',':
			farThreshold --;
			if (farThreshold < 0) farThreshold = 0;
			break;
			
		case '+':
		case '=':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
			break;
			
		case '-':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
			
		case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
			
		case 'o':
			kinect.setCameraTiltAngle(angle); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
			break;
			
		case '1':
			targetAlpha = 50;
			kinect.setLed(ofxKinect::LED_GREEN);
			break;
			
		case '2':
			targetAlpha = 125;
			kinect.setLed(ofxKinect::LED_YELLOW);
			break;
			
		case '3':
			targetAlpha = 200;
			kinect.setLed(ofxKinect::LED_RED);
			break;
			
		case '4':
			kinect.setLed(ofxKinect::LED_BLINK_GREEN);
			break;
			
		case '5':
			kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
			break;
			
		case '0':
			kinect.setLed(ofxKinect::LED_OFF);
			break;
			
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle = 30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle =- 30;
			kinect.setCameraTiltAngle(angle);
			break;

		case 'g':
			minBlob--;
			break;
		
		case 'h':
			minBlob++;
			break;
	
		case 'e':
			closePoints.begin();
				ofFill(); 
				ofSetColor(ofColor::white);
				ofRect(0, 0, closePoints.getWidth(), closePoints.getHeight());
			closePoints.end();
			break;

		case 'd':
			presenting = !presenting;
			playState = presenting;
			break;

		case 'n':
			// Increase Play

			currentIndex++;

    

			// Check Limit

			if(currentIndex >= maxIndex) {

				currentIndex = 0;

			}

    

			// Update Assets

			updateCurrentIndex();

			break;

		case 's':
			tooSunny = !tooSunny;
			break;

		case 'm':
			showDemo = !showDemo;
			if(showDemo) {
				playState = 4;
				demo.play();
				demo.setLoopState(OF_LOOP_NONE);
			}
	
			break;

		case 'b':
			bLearnBakground = true;
			break;

		
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
bBrushDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
bBrushDown = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{}
