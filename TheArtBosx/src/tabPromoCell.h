//
//  tabPromoCell.h
//  TheArtBosx
//
//  Created by P Daggitt on 2015-06-03.
//
//

#ifndef __TheArtBosx__tabPromoCell__
#define __TheArtBosx__tabPromoCell__

#include "ofMain.h"

class tabPromoCell {
    
public:
    
    // methods
    void update();
    void draw();
    
    // variables
    ofTrueTypeFont font;
    string text;
    ofVideoPlayer video;
    ofImage image;
    ofColor backgroundColor;
    int xpos,ypos;
    int width, height;
    float normalizedRatio;
    
    // constructor
    tabPromoCell(int _xPos, int _yPos, int _width, int _height, string media_text,  string _mediaPath, bool _isMediaVideo);
    tabPromoCell();
    
private:
    
};
#endif