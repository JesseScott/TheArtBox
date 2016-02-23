#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

    // SYSTEM
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofHideCursor();
    ofSetFrameRate(60);
    
    // SCREEN
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(0);
    
    setupFBOs();
    

    
    // JSON
    if(readJSON())
    {
        writeJSONToArticleArray();
    }
    
}

void ofApp::setupFBOs()
{
    image_screen.allocate(FBO_WIDTH, FBO_HEIGHT, GL_RGB);
    image_screen.begin();
        ofClear(255,255);
    image_screen.end();

    meta_screen.allocate(FBO_WIDTH, FBO_HEIGHT, GL_RGB);
    meta_screen.begin();
        ofClear(255,255);
    meta_screen.end();
    
    news_screen.allocate(FBO_WIDTH, FBO_HEIGHT, GL_RGB);
    news_screen.begin();
        ofClear(255,255);
    news_screen.end();
    
    ////
    
    image_screen.begin();
        ofSetColor(0, 0, 255);
        ofRect(0, 0, image_screen.getWidth(), image_screen.getHeight());
    image_screen.end();
    
    meta_screen.begin();
        ofSetColor(0, 0, 255);
        ofRect(0, 0, meta_screen.getWidth(), meta_screen.getHeight());
    meta_screen.end();
    
    news_screen.begin();
        ofSetColor(255, 0, 0);
        ofRect(0, 0, news_screen.getWidth(), news_screen.getHeight());
    news_screen.end();
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
        //mArticles[i].logData();
    }
    
}


//--------------------------------------------------------------
void ofApp::update()
{

    
    // NEWS
    
    news_screen.begin();
        ofSetColor(255, 0, 0);
        ofRect(0, 0, news_screen.getWidth(), news_screen.getHeight());
        mArticles[current_article].draw();
    news_screen.end();

    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(155);
    ofSetColor(255,255,255);
 

    image_screen.draw(0, 0);
    meta_screen.draw(FBO_WIDTH, 0);
    news_screen.draw(FBO_WIDTH * 2, 0);
    
    //mArticles[current_article].draw();
    
    
}

