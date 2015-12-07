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

    string request =
    "curl -X GET \
    -H \"X-Parse-Application-Id: jipZruxdWwERhPzDTQkE8lffqh47aI5wv89QKgps\" \
    -H \"X-Parse-REST-API-Key: XlNPX5LyS5w8X3HsVQ9OkikfvDvgijr004O63G6R\" \
    https://api.parse.com/1/classes/Article";

    curlIt("https://api.parse.com/1/classes/Article");
    
    //ofSystem(request);
    
    //int id = ofLoadURLAsync(request, "state");
    //ofLoadURL(request);
    
}


//--------------------------------------------------------------

void Postman::urlResponse(ofHttpResponse &response)
{
    if (response.status == 200 && response.request.name == "state") {
        cout << response.status <<  " " << response.data << endl;
    }
    else {
        cout << response.status <<  " - FAILURE - " << response.data << endl;
    }
}

void Postman::curlIt(string _request)
{
    ofxCurl curl;
    ofxCurlForm* form = curl.createForm("https://api.parse.com/1/classes/Article");
    
    
    form->addInput("X-Parse-Application-Id", "jipZruxdWwERhPzDTQkE8lffqh47aI5wv89QKgps");
    form->addInput("X-Parse-REST-API-Key","XlNPX5LyS5w8X3HsVQ9OkikfvDvgijr004O63G6R");
    //form->addInput("secret", "call me roxlu");
    //form->addFile("photo",ofToDataPath("image_to_upload.png",true));
    
    // Perform the post.
    try {
        form->post();
    }
    catch(...) {
        cout << "OOPS.. something went wrong while posting" << endl;
    }
    
    // Do something with the response from the post.
    vector<char> response_buf = form->getPostResponseAsBuffer();
    string response_str = form->getPostResponseAsString();
    cout << "Size of response buffer: " << response_buf.size() << endl << endl;
    cout << "Response string:" << endl;
    cout << "-----------------" << endl;
    cout << response_str <<endl;
    
    // Cleanup
    delete form;
}


