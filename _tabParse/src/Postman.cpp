//
//  Postman.cpp
//  tabParse
//
//  Created by Jesse Scott on 2015-12-06.
//
//

#include "Postman.h"

//--------------------------------------------------------------

void Postman::setup()
{
    
    cout << "Postman Setup Is Done \n" << endl;
}

//--------------------------------------------------------------

void Postman::fetchDataByClass(string className)
{

        cout << "Attempting to Fetch Class "<<className<<endl;
    
        string cmd =
        "curl -X GET \
        -H \"X-Parse-Application-Id: jipZruxdWwERhPzDTQkE8lffqh47aI5wv89QKgps\" \
        -H \"X-Parse-REST-API-Key: XlNPX5LyS5w8X3HsVQ9OkikfvDvgijr004O63G6R\" \
        https://api.parse.com/1/classes/Article";

        ofSystem( cmd );
    
}