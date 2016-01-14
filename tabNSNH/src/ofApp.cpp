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

    
    // JSON
    if(readJSON())
    {
        writeJSONToArticleArray();
    }
    
}


bool ofApp::readJSON()
{
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
    return parsingSuccessful;
}

void ofApp::writeJSONToArticleArray()
{
    for (Json::ArrayIndex i = 0; i < json["results"].size(); ++i)
    {
        
        // Read Vars From JSON
        string title  = json["results"][i]["title"].asString();
        string subtitle = json["results"][i]["subtitle"].asString();
        string body = json["results"][i]["body"].asString();
        string date   = json["results"][i]["createdAt"].asString();
        
        // Instantiate New Article
        Article article = *new Article(title, subtitle, body, date);
        
        // Add To Vector
        mArticles.push_back(article);
    }
    
    for (int i = 0; i < mArticles.size(); i++) {
        mArticles[i].logData();
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

