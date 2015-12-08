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

class Postman {
    
    public:
        void setup();
    
        void fetchDataByClass(string className);
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    
        void getRequestToURL();
        void loadURL(string _request);
        void urlResponse(ofHttpResponse &response);
        void callSystem(string _request);
        void curlIt(string _request);
    
};
