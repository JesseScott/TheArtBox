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
        ofLogNotice("ofApp::setup") << "Parsed JSON!" << endl;
    }
    else
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::update()
{

    
    
}

//--------------------------------------------------------------
void ofApp::draw()
{

    ofBackground(0);
    ofSetColor(255);
    
    for (Json::ArrayIndex i = 0; i < json["results"].size(); ++i)
    {
        std::string title  = json["results"][i]["title"].asString();
        std::string subtitle = json["results"][i]["subtitle"].asString();
        std::string body = json["results"][i]["body"].asString();
        std::string date   = json["results"][i]["createdAt"].asString();
        std::string text   = title + " - " + subtitle + " " + body + " (" + date + ")";
        ofDrawBitmapString(text, 20, i * 24 + 40);
    }
}

