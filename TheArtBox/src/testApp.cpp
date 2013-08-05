#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

    ofEnableAlphaBlending();
    ofBackground(100);

    // Video
    video.loadMovie("movies/fingers.mov");
    video.firstFrame();
    video.setPaused(true);

    // Resize
    int width = ofGetWindowWidth();
    int height = ofGetWindowHeight();
    ofSetWindowShape(width, height);

    // Background
    thumbnail.setFromPixels(video.getPixels(), video.getWidth(), video.getHeight(), OF_IMAGE_COLOR); // A
    thumbnail.resize(width, height);

    // Convert To Grayscale
    foreground = thumbnail;
    foreground.setImageType(OF_IMAGE_GRAYSCALE); // B

    // Brush
    brush.loadImage("images/brush.png");

    // FBOs
    maskFbo.allocate(width,height);
    fbo.allocate(width,height);

    maskFbo.begin();
        ofClear(0,0,0,255);
    maskFbo.end();

    fbo.begin();
        ofClear(0,0,0,255);
    fbo.end();

    // Shader
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
