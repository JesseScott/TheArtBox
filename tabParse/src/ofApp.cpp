#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup()
{
    // SYSTEM
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofLogNotice("ofApp::setup") << "Setup Is Starting \n";

    
    // REST
    postman = *new Postman();
    postman.fetchDataByClass(kClassArticle);
    
    
    ofLogNotice("ofApp::setup") << "Setup Is Done \n";
}

//--------------------------------------------------------------

void ofApp::update()
{

}

//--------------------------------------------------------------

void ofApp::draw()
{

}
