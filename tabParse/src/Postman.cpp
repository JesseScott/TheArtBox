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
        passToJSON(readBuffer);
    }

    
}

size_t Postman::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


//--------------------------------------------------------------

void Postman::passToJSON(string _stream)
{
    
    // Now parse the JSON
    bool parsingSuccessful = result.parse(_stream);
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << result.getRawString();
        
        // now write pretty print
        if (!result.save("example_output_pretty.json", true))
        {
            ofLogNotice("ofApp::setup") << "example_output_pretty.json written unsuccessfully.";
        }
        else
        {
            ofLogNotice("ofApp::setup") << "example_output_pretty.json written successfully.";
        }
    }
    else
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
}
