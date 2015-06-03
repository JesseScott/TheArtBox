//
//  tabPromoManager.h
//  TheArtBosx
//
//  Created by P Daggitt on 2015-06-03.
//
//

#ifndef __TheArtBosx__tabPromoManager__
#define __TheArtBosx__tabPromoManager__

#include "ofMain.h"
#include "tabPromoCell.h"

class tabPromoManager {
    
public:
    
    // methods
    void update();
    void draw();
    
    // variables
    //graphics context
    ofFbo promoFBO; 
    vector<tabPromoCell> cellArray;
    int width, height; 
    
    // constructor
    tabPromoManager(vector<string> media_url_array, vector<bool> media_type_array, vector<string> cell_text_array, int _width, int _height);
    tabPromoManager();
    
private:
    
};
#endif