//
//  Writer.hpp
//  tabParse
//
//  Created by Jesse Scott on 2015-12-06.
//
//

#ifndef Writer_hpp
#define Writer_hpp

#include <stdio.h>

#endif /* Writer_hpp */

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class Writer {
    
public:
    void setup();
    void update();
    void write();
    
    
    // Variables
    ofxXmlSettings xml;
    string PATH;
    
};
