#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    
    // Variables
    ofxXmlSettings xml;
    string PATH;
		
};
