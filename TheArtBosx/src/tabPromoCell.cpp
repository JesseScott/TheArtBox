//
//  tabPromoCell.cpp
//  TheArtBosx
//
//  Created by P Daggitt on 2015-06-03.
//
//

#include "tabPromoCell.h"

tabPromoCell::tabPromoCell(int _xPos, int _yPos, int _width, int _height, string media_text, string _mediaPath, bool _isMediaVideo)
{
    font.loadFont("fonts/Futura-Bold.ttf", 10);
    text = "THIS IS TEST COPY";
    
    if (_isMediaVideo) {
       video.loadMovie(_mediaPath);
    }
    else {
      image.loadImage(_mediaPath);
    }
   
    backgroundColor.r = 255;
    backgroundColor.g = 0;
    backgroundColor.b = 0;
    ofSetBackgroundColor(backgroundColor);
    
    xpos = _xPos;
    ypos = _yPos;
    width = _width;
    height = _height;
    
    if (height > width) {
        normalizedRatio = width/height;
    }
    else {
        normalizedRatio = height/width;
    }
    
}

tabPromoCell::tabPromoCell() {
    font.loadFont("fonts/Futura-Bold.ttf", 10);
    text = "THIS IS TEST COPY";
    //video;
    //image;
    
    backgroundColor.r = 255;
    backgroundColor.g = 0;
    backgroundColor.b = 0;
    ofSetBackgroundColor(backgroundColor);
    
    xpos = 0;
    ypos = 0;
    width = 16 * 5;
    height = 9 * 5;
    
    if (height > width) {
        normalizedRatio = width/height;
    }
    else {
        normalizedRatio = height/width;

    }
}

void tabPromoCell::update(){
    if (video.isLoaded()) {
        video.update();
    }
}

void tabPromoCell::draw(){
    if (video.isLoaded()) {
        video.draw(xpos, ypos, width, height);
    }
    
    font.drawString(text, 0, 0);
}
