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
    mFont.loadFont("fonts/verdana.ttf", 30, true, true);
    mFont.setLineHeight(34.0f);
    mFont.setLetterSpacing(1.035);
}

void Article::update()
{
    
}


void Article::draw()
{
    ofSetColor(245, 58, 135);
    mFont.drawString(title, 155, 92);
}







