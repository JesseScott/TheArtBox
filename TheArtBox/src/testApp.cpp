#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    // Screen
    ofEnableAlphaBlending();
    ofBackground(100);
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();

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

    // Index
    currentIndex = 0;
    setAssets(currentIndex);

    // Video
    video.loadMovie("movies/fingers.mov");
    video.firstFrame();
    video.setPaused(true);

    // Background
    thumbnail.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
    thumbnail.resize(width, height);

    // Convert To Grayscale
    foreground = thumbnail;
    foreground.setImageType(OF_IMAGE_GRAYSCALE);

    // Brush
    brush.loadImage("images/brush.png");

    // FBO & GLSL SHADER
    setupGL(width, height);

    // Paint
    bBrushDown = false;


    cout << "Setup Is Done" << endl;
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
    font.drawString("HELLO", 200, 200);

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

void testApp::setAssets(int _currentIndex) {

    // Cast to String
    //string file( ofToString(dragInfo.files[0]) );
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
    }
    // Image
    else if (fileExtension == "JPG" || fileExtension == "PNG") {
        ofLogNotice("FILE IS AN IMAGE");
    }


}

//--------------------------------------------------------------
// CUSTOM GL FUNCTIONS

void testApp::setupGL(int _width, int _height) {
    // FBOs
    maskFbo.allocate(_width, _height);
    fbo.allocate(_width, _height);

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
