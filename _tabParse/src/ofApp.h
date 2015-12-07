#pragma once

#include "ofMain.h"
#include "Writer.h"
#include "Postman.h"

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

    Writer writer;
    Postman postman;
    
    string kClassArticle = "Article";
		
};
