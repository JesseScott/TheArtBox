//
//  Writer.cpp
//  tabParse
//
//  Created by Jesse Scott on 2015-12-06.
//
//

#include "Writer.h"


//--------------------------------------------------------------

void Writer::setup()
{
    // SYSTEM
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // XML ASSETS
    PATH = "../../../MEDIA/";
    xml.loadFile("xml/assets.xml");
    

    
    
    
    
    cout << "Writer Setup Is Done \n" << endl;    
}

//--------------------------------------------------------------

void Writer::write()
{
    
}