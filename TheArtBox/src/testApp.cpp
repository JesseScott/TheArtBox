#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    // Screen
    ofEnableAlphaBlending();
    ofBackground(100);
    width = ofGetWindowWidth();
    height = ofGetWindowHeight();

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

    // Set Index
    currentIndex = 0;
    // Update Assets
    updateCurrentIndex();

    // Brush
    brush.loadImage("images/brush.png");

    // FBO & GLSL SHADER
    setupGL(width, height);

    // Paint
    bBrushDown = false;


    cout << "Setup Is Done \n" << endl;
}

//--------------------------------------------------------------
void testApp::update(){

    //
    maskFbo.begin();
        if (bBrushDown){
            ofSetColor(ofColor::aliceBlue);
            brush.draw(mouseX-25, mouseY-25, 50, 50);
        }
    maskFbo.end();

    //
    fbo.begin();
        ofClear(0, 0, 0, 0);
        shader.begin();
            shader.setUniformTexture("maskTex", maskFbo.getTextureReference(), 1);
            thumbnail.draw(0, 0);
        shader.end();
    fbo.end();

    // Idle Video
    video.update();

}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(255,255);

    // Draw Video
    //video.draw(0, 0);

    // Draw Color Thumbnail
    //thumbnail.draw(0, 0);

    // Draw B+W Foreground
    foreground.draw(0, 0);

    // Draw FBO
    fbo.draw(0, 0);

    // Caption
    font.drawString(artistNames[currentIndex], 200, 200);

    //cout << ofGetFrameRate() << endl;
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

}


//--------------------------------------------------------------
// CUSTOM GL FUNCTIONS

void testApp::setupGL(int width, int height) {
    // FBOs
    maskFbo.allocate(width, height);
    fbo.allocate(width, height);

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

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    // Increase PlayCount
    currentIndex++;
    // Check Limit
    if(currentIndex >= maxIndex) {
        currentIndex = 0;
    }
    // Update Assets
    updateCurrentIndex();

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    bBrushDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bBrushDown = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
