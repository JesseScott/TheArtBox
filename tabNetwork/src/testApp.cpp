#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Connect
    
    try {
        //client.connect("ftp.memelab.ca", 21, "SITC_APP", "SITC_6");
        client.setup("ftp.memelab.ca", "SITC_APP", "SITC_6", 21);
        client.setVerbose(true);
        cout << "Connection Success! \n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    // List Files
    try {
        fileNames = client.list("/");
        cout << "Listing Success! \n" << endl;
        for(int i = 0; i < fileNames.size(); i++) {
            cout << "Item #" << i << " is " << fileNames[i] << "\n" << endl;
        }
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    // Get Files
    try {
        client.get("BOXIcon.png", ofToDataPath(""), "/");
        for(int i = 0; i < fileNames.size(); i++) {
            //client.get(fileNames[i], ofToDataPath(""), "/");
        }
        cout << "Downloading Success!" << endl;
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
