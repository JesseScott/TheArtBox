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

    cout << "Attempting to Fetch Class " << className << endl;
    
    CURL *curl;
    CURLcode res;
    
    struct curl_slist *headerlist=NULL;
    headerlist = curl_slist_append( headerlist, "X-Parse-Application-Id: jipZruxdWwERhPzDTQkE8lffqh47aI5wv89QKgps");
    headerlist = curl_slist_append( headerlist, "X-Parse-REST-API-Key: XlNPX5LyS5w8X3HsVQ9OkikfvDvgijr004O63G6R");
    headerlist = curl_slist_append( headerlist, "Content-Type: application/json");
    
    curl = curl_easy_init();
    if(curl)
    {
        string readBuffer;
        readBuffer.clear();
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.parse.com/1/classes/Article");
        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            cout << "Result: " << res << endl;
        }
    
        curl_easy_cleanup(curl);

        cout << "RB: \n" << readBuffer << endl;
    }

    
}

size_t Postman::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


//--------------------------------------------------------------

void Postman::callSystem(string _request)
{
    ofSystem(_request);
}

void Postman::loadURL(string _request)
{
    //int id = ofLoadURLAsync(request, "state");
    ofLoadURL(_request);
}

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
    //ofxCurl curl;
    
    
    CURL *curl;
    CURLcode res;
    struct curl_slist *headerlist=NULL;
    headerlist = curl_slist_append( headerlist, "X-Parse-Application-Id: jipZruxdWwERhPzDTQkE8lffqh47aI5wv89QKgps");
    headerlist = curl_slist_append( headerlist, "X-Parse-REST-API-Key: XlNPX5LyS5w8X3HsVQ9OkikfvDvgijr004O63G6R");
    headerlist = curl_slist_append( headerlist, "Content-Type: application/json");
    
    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.parse.com/1/classes/Article");
        //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"direction\" : \"south\"}");
        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            cout << "Result: " << res << endl;
        }
    }
    
    /*
    
    ofxCurlForm* form = curl.createForm(_request);
    
    
    //form->addInput("X-Parse-Application-Id", "jipZruxdWwERhPzDTQkE8lffqh47aI5wv89QKgps");
    //form->addInput("X-Parse-REST-API-Key","XlNPX5LyS5w8X3HsVQ9OkikfvDvgijr004O63G6R");
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
     */
}


