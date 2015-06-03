//
//  tabPromoManager.cpp
//  TheArtBosx
//
//  Created by P Daggitt on 2015-06-03.
//
//

#include "tabPromoManager.h"

tabPromoManager::tabPromoManager(vector<string> media_url_array, vector<bool> media_type_array, vector<string> cell_text_array, int _width, int _height)
{
    cellArray.reserve(cell_text_array.size());
    
    for (int i =0; i < cell_text_array.size(); i++) {
        tabPromoCell *tempCell = new tabPromoCell(0, 0, 100, 30, cell_text_array[i], media_url_array[i], media_type_array[i]);
        cellArray.push_back(*tempCell);
    }
    
    width = _width;
    height = _height;
    
}

tabPromoManager::tabPromoManager() {

}

void tabPromoManager::update(){

    for (int i = 0; i < cellArray.size(); i++) {
        cellArray[i].update();
    }
}

void tabPromoManager::draw(){
    
    promoFBO.begin();
        for (int i = 0; i < cellArray.size(); i++) {
            cellArray[i].draw();
        }
    promoFBO.end();
    
    promoFBO.draw(0,0,width,height);
    
}
