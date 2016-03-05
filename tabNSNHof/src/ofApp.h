#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "Article.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    void setupFBOs();
    bool readJSON();
    void writeJSONToArticleArray();
    
    vector<Article> mArticles;
    int current_article = 0;

    ofxJSONElement json;
    string BASEPATH = "../../../MEDIA/json/";
    string FILENAME = "article.json";
    
    ofFbo image_screen;
    ofFbo meta_screen;
    ofFbo news_screen;
    int FBO_WIDTH = 540;
    int FBO_HEIGHT = 960;
		
};
