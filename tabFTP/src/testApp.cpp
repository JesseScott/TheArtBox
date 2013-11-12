#include "testApp.h"
#include <stdlib.h>

//--------------------------------------------------------------
void testApp::setup() {
    
    // Read Credentials File
    credentials = ofBufferFromFile("settings/credentials.txt");
    host = credentials.getFirstLine();
    username = credentials.getNextLine();
    password = credentials.getNextLine();
    port = credentials.getNextLine();
    
    // Set Paths
    pathToDataDirectory = "../../../DATA";
    pathToLogsDirectory = "../../../LOGS";
    pathToUploadsDirectory = "/filefrontend/data/files/uploads/";
    
    // Connect
    try {
        cout << "Attempting To Connect To FTP:" << endl;
        
        // Log In To FTP
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

        // Assign List Of Directory To Base String Vector
        fileNames = client.list(pathToUploadsDirectory);
        
        // Resize Trimmed Vector To Match
        trimmedFileNames.resize(fileNames.size());

        // Loop Through File Names, Trim At Path, And Assign To New Vector
        for(int i = 0; i < fileNames.size(); i++) {
            cout << "Item #" << i << " is " << fileNames[i] << endl;
            vector<string> trimmedName = ofSplitString(fileNames[i], "uploads/");
            trimmedFileNames[i] = trimmedName[1];
        }
        
        // Loop Through New Vector To Make Sure
        for(int i = 0; i < trimmedFileNames.size(); i++) {
            cout << "Trimmed Item #" << i << " is " << trimmedFileNames[i] << endl;
        }
        
        cout << "Listing Success!\n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    // Get Files
    try {
        cout << "Attempting To Download All Files:" << endl;
        
        // Download All Files From Uploads Directory To Data Directory
        for(int i = 0; i < trimmedFileNames.size(); i++) {
            client.get(trimmedFileNames[i], ofToDataPath(""), pathToUploadsDirectory);
        }
        
        cout << "Downloading Success!\n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    // Move Files
    cout << "Listing Files In Data Directory" << endl;
    
    // Set Path To Root Data Folder
    string path = "";
    ofDirectory dir(path);
    
    //Allow Media Types
    dir.allowExt("jpg");
    dir.allowExt("png");
    dir.allowExt("mp4");
    dir.allowExt("zip");
    
    // List
    dir.listDir();
    cout << "Directory Has " << dir.size() << " Valid Files" << endl;
    
    // Move To Data Directory
    cout << "Moving To Data Directory" << endl;
    for (int i = 0; i < dir.size(); i++) {
        ofFile file = dir.getFile(i);
        cout << "Moving File #" << i << endl;
        file.moveTo(pathToDataDirectory);
    }
    
    cout << "Moving Success!\n" << endl;
    
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
