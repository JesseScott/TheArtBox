//
//  Article.cpp
//  tabNSNH
//
//  Created by Jesse Scott on 2016-01-13.
//
//

#include "Article.h"


// Getters

string Article::getTitle()
{
    return title;
}

string Article::getSubtitle()
{
    return subtitle;
}

string Article::getBody()
{
    return body;
}

string Article::getDate()
{
    return date;
}

// Log

void Article::logData()
{
    ofLog(OF_LOG_VERBOSE) << "\n" << "ARTCILE: " << "\n" << "TITLE:\t" << title << "\n" << "SUB:\t\t" << subtitle << "\n" << "BODY:\t" << body << "\n" << "DATE:\t" << date << endl;
}

// Present

void Article::setup()
{
    ofTrueTypeFont::setGlobalDpi(72);
    mTitleFont.loadFont("fonts/Open Sans.ttf", 30, true, true);
    mTitleFont.setLineHeight(37.5f);
    mTitleFont.setLetterSpacing(1.0f);
    
    mSubtitleFont.loadFont("fonts/Open Sans.ttf", 24, true, true);
    mSubtitleFont.setLineHeight(30.0f);
    mSubtitleFont.setLetterSpacing(1.0f);
    
    mBodyFont.loadFont("fonts/Open Sans.ttf", 14, true, true);
    mBodyFont.setLineHeight(17.5f);
    mBodyFont.setLetterSpacing(1.0f);
}

void Article::update()
{
    
}


void Article::draw()
{
    ofSetColor(50);
    
    mTitleFont.drawString("TITLE", width/2 - (mTitleFont.stringWidth(title)/2), 96);
    ofLine(54, 104, width - 54, 104);
    
    mSubtitleFont.drawString("subtitle subtitle", width/2 - (mTitleFont.stringWidth(title)), 144);

    string b = "asdsadsads asdsadsadj  asdsa dsadsa  asd sdjl kask asdlsajd   \nlasjdsalj dasld  lsjdslajddas lsa ";
    mBodyFont.drawString(b, 54, 192);

    
    
}







