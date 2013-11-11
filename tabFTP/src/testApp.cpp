#include "testApp.h"
#include <stdlib.h>

//--------------------------------------------------------------
void testApp::setup() {
    
    // Read Credentials File
    credentials = ofBufferFromFile("credentials.txt");
    host = credentials.getFirstLine();
    username = credentials.getNextLine();
    password = credentials.getNextLine();
    port = credentials.getNextLine();
   
    // Connect
    try {
        cout << "Attempting To Connect To FTP:" << endl;
        client.setup(host, username, password, 21);
        client.setVerbose(true);
        cout << "Connection Success! \n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    // List Files
    try {
        cout << "Attempting To List All Files:" << endl;
        fileNames = client.list("/");
        for(int i = 0; i < fileNames.size(); i++) {
            cout << "Item #" << i << " is " << fileNames[i] << endl;
        }
        cout << "Listing Success!\n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    // Get Files
    try {
        cout << "Attempting To Download All Files:" << endl;
        //client.get("BOXIcon.png", ofToDataPath(""), "/");
        for(int i = 0; i < fileNames.size(); i++) {
            //client.get(fileNames[i], ofToDataPath(""), "/");
        }
        cout << "Downloading Success!\n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }

    
}

//--------------------------------------------------------------
void testApp::update(){

    
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
