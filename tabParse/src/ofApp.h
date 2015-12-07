#pragma once

#include "ofMain.h"
#include "Writer.h"
#include "Postman.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

    
    // Variables
    ofxXmlSettings xml;
    string PATH;
		
};
