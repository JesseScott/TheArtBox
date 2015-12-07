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
        void getRequestToURL();
        void urlResponse(ofHttpResponse &response);
        void curlIt(string _request);
    
};
