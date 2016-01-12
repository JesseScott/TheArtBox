//
//  Postman.h
//  tabParse
//
//  Created by Jesse Scott on 2015-12-06.
//
//

#ifndef Postman_hpp
#define Postman_hpp
#endif
#pragma once

#include "ofMain.h"
#include "ofxCurl.h"
#include "ofxJSON.h"

class Postman {
    
    public:
        void setup();
    
        void fetchDataByClass(string className);
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        void passToJSON(string _stream);

    
    ofxJSONElement result;
    string BASEPATH = "../../../MEDIA/json/";
    string FILENAME = "article.json";

    
};
