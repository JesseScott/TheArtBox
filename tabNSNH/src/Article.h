//
//  Article.h
//  tabNSNH
//
//  Created by Jesse Scott on 2016-01-13.
//
//

#include "ofMain.h"
#include "ofxCurl.h"
#include "ofxJSON.h"

#ifndef Article_hpp
#define Article_hpp
#endif
#pragma once


class Article {
    
public:
    
    
    Article()
    {
        
    }
    
    Article(string _title, string _subtitle, string _body, string _date)
    {
        title = _title;
        subtitle = _subtitle;
        body = _body;
        date = _date;
        
        setup();
    }

    void setup();
    void update();
    void draw();
    
    string getTitle();
    string getSubtitle();
    string getBody();
    string getDate();
    
    void logData();


    int yOffset;
    ofTrueTypeFont	mFont;

private:
    
    string title;
    string subtitle;
    string body;
    string date;
    
    
};