#include "ofApp.h"

//#define DEBUG

int main() {
    #ifdef BIG
        ofSetupOpenGL(1920, 1080, OF_WINDOW);
    #else
        ofSetupOpenGL(3240, 1920, OF_WINDOW);
    #endif
		//ofSetupOpenGL(3240, 1920, OF_WINDOW);
	ofSetWindowPosition(0, 0);
	ofRunApp(new ofApp());
}
