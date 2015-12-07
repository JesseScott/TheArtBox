//
//  Writer.cpp
//  tabParse
//
//  Created by Jesse Scott on 2015-12-06.
//
//

#include "Writer.hpp"


//--------------------------------------------------------------

void Writer::setup()
{
    // SYSTEM
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // XML ASSETS
    PATH = "../../../MEDIA/";
    xml.loadFile("xml/assets.xml");
    
    //    if( assets.loadFile("xml/assets.xml") ) {
    //        ofLog(OF_LOG_NOTICE, "Loaded xml file !!! \n");
    //        loadFonts();
    //        loadArtists();
    //        loadAssets();
    //    }
    //    else {
    //        ofLog(OF_LOG_ERROR, "UNABLE to load xml file :( \n");
    //    }
    
    
    
    
    
    cout << "Writer Setup Is Done \n" << endl;
    
}

//--------------------------------------------------------------

void Writer::update()
{
    
}

//--------------------------------------------------------------

void Writer::write()
{
    
}