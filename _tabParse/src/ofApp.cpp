#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup()
{
    // SYSTEM
    ofSetLogLevel(OF_LOG_VERBOSE);

    // REST
    postman = *new Postman();
    postman.fetchDataByClass(kClassArticle);
    
    
    
    
    cout << "Setup Is Done \n" << endl;
    
}

//--------------------------------------------------------------

void ofApp::update()
{

}

//--------------------------------------------------------------

void ofApp::draw()
{

}
