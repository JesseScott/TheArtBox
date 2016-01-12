#pragma once

#include "ofMain.h"
#include "ofxJSON.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

    ofxJSONElement json;
    string BASEPATH = "../../../MEDIA/json/";
    string FILENAME = "article.json";
		
};
