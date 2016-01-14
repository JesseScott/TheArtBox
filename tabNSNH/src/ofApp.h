#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "Article.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    bool readJSON();
    void writeJSONToArticleArray();
    
    vector<Article> mArticles;

    ofxJSONElement json;
    string BASEPATH = "../../../MEDIA/json/";
    string FILENAME = "article.json";
		
};
