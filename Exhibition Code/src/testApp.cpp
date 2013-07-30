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
    int width = 800;
    int height = 600;
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
    
    maskFbo.begin();
        ofClear(0,0,0,255);
    maskFbo.end();
    
    fbo.begin();
        ofClear(0,0,0,255);
    fbo.end();

    bBrushDown = false;

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
    
    // Dra FBO
    fbo.draw(0, 0);
    
    cout << ofGetFrameRate() << endl;
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
    
    /*
    cout << "BG COLOR: " << thumbnail.getColor(x, y) << endl;
    cout << "FG COLOR: " << foreground.getColor(x, y) << endl;
    cout << endl;
    */
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