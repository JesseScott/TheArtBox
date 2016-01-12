#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

    // SYSTEM
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofHideCursor();
    ofSetFrameRate(60);
    
    // SCREEN
    ofEnableAlphaBlending();
    ofBackground(100);

    
    // PATH
    string path = BASEPATH + FILENAME;
    bool parsingSuccessful = json.open(path);
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << json.getRawString();
    }
    else
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

