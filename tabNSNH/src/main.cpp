#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    /*  
     1080 / 1920 = 1.777
     
     */
    
	ofSetupOpenGL(540, 960, OF_WINDOW);
	ofRunApp(new ofApp());

}
