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

void Article::logData()
{
    ofLog(OF_LOG_VERBOSE) << "ARTCILE: " << "\n" << "TITLE: " << title << "\n" << "SUBTITLE: " << subtitle << "\n" << "BODY: " << body << "\n" << "DATE: " << date << endl;
}