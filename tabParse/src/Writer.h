//
//  Writer.h
//  tabParse
//
//  Created by Jesse Scott on 2015-12-06.
//
//

#ifndef Writer_hpp
#define Writer_hpp
#endif

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class Writer {
    
public:
    void setup();
    void write();
    
    // Variables
    ofxXmlSettings xml;
    string PATH;
    
};
