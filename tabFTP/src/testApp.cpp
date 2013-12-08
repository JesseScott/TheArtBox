#include "testApp.h"
#include <stdlib.h>

//--------------------------------------------------------------
void testApp::setup() {
    
    
    /*  INTRO   */
    
    // Preamble
    cout << "Starting Program " << endl;
    cout << " ----- \n" << endl;
    
    // Set Log Level (To Ensure Serial Debug Info Prints)
    ofSetLogLevel(OF_LOG_NOTICE);
    
    // Read Credentials File
    credentials = ofBufferFromFile("settings/credentials.txt");
    host = credentials.getFirstLine();
    username = credentials.getNextLine();
    password = credentials.getNextLine();
    port = credentials.getNextLine();
    
    // Set Paths
    pathToDataDirectory = "../../../MEDIA";
    pathToLogsDirectory = "../../../LOGS";
    pathToUploadsDirectory = "/filefrontend/data/files/uploads/";
    
    
    /*  READ EXISTING FILES */
    
    // Set Path To Root Data Folder
    string mediaPath = pathToDataDirectory;
    mediaDirectory = ofDirectory(mediaPath);
    
    //Allow Media Types
    mediaDirectory.allowExt("jpg");
    mediaDirectory.allowExt("png");
    mediaDirectory.allowExt("mp4");
    mediaDirectory.allowExt("zip");
    
    // List
    mediaDirectory.sort();
    mediaDirectory.listDir();
    cout << "Media Directory Has " << mediaDirectory.size() << " Valid Files \n" << endl;
    existingFileNames.resize(mediaDirectory.size());
    for (int i = 0; i < mediaDirectory.size(); i++) {
        existingFileNames[i] = mediaDirectory.getName(i);
        cout << "Existing File Name #" << i << " is " << existingFileNames[i] << endl;
    }
    
    cout << "Existing Parse Success! \n" << endl;
    
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
    
    
    /*  LIST REMOTE FILES */
    
    // List Files
    try {
        cout << "Attempting To List All Files:" << endl;

        // Assign List Of Directory To Base String Vector
        fileNames = client.list(pathToUploadsDirectory);
        
        // Resize Trimmed Vector To Match
        trimmedFileNames.resize(fileNames.size());
        existingFileNames.resize(trimmedFileNames.size());

        // Loop Through File Names, Trim At Path, And Assign To New Vector
        for(int i = 0; i < fileNames.size(); i++) {
            cout << "Original Item #" << i << " is " << fileNames[i] << endl;
            vector<string> trimmedName = ofSplitString(fileNames[i], "uploads/");
            trimmedFileNames[i] = trimmedName[1];
        }
        
        cout << "" << endl;
        
        // Loop Through New Vector To Make Sure
        for(int i = 0; i < trimmedFileNames.size(); i++) {
            cout << "Trimmed Item #" << i << " is " << trimmedFileNames[i] << endl;
        }
        
        cout << "Listing Success!\n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    
    /*  COMPARE EXISTING AND REMOTE FILES */
    
    // Compare Files
    cout << "Attempting To Compare All Files:" << endl;
    
    for(int i = 0; i < trimmedFileNames.size(); i++) {
        Boolean match = false; // Set Boolean To Test Matches
        for(int j = 0; j < existingFileNames.size(); j++) {
            // If The Current File Matches Any File In The Existing List
            if(trimmedFileNames[i].compare(existingFileNames[j]) == 0 ) {
                match = true;
                break;
            }
            // Otherwise Mark It As New
            else {
                match = false;
            }
        }
        
        // Test
        if(match) {
            cout << "The File " << trimmedFileNames[i] << " Has Previously Been Downloaded" << endl;
        }
        else {
            cout << "The File " << trimmedFileNames[i] << " Seems To Be New" << endl;
            newFileNames.push_back(trimmedFileNames[i]); // Add To New List
        }
    }
    
    cout << "Comparing Success!\n" << endl;
    
    
    /*  DOWNLOAD NEW FILES */
    
    // Get Files
    try {
        cout << "Attempting To Download " << newFileNames.size() << " Files:" << endl;
        
        // Download All Files From Uploads Directory To Data Directory
        for(int i = 0; i < newFileNames.size(); i++) {
            cout << "Downloading The File " << newFileNames[i] << endl;
            client.get(newFileNames[i], ofToDataPath(""), pathToUploadsDirectory);
        }
        
        cout << "Downloading Success!\n" << endl;
    }
    catch(int e) {
        cout << "The Exception #" << e << " Occured." << endl;
    }
    
    
    /*  MOVE FILES */
    
    cout << "Listing Files In Data Directory" << endl;
    
    // Set Path To Root Data Folder
    string dataPath = "";
    dataDirectory = ofDirectory(dataPath);
    
    //Allow Media Types
    dataDirectory.allowExt("jpg");
    dataDirectory.allowExt("png");
    dataDirectory.allowExt("mp4");
    dataDirectory.allowExt("zip");
    
    // List
    dataDirectory.sort();
    dataDirectory.listDir();
    cout << "Data Directory Has " << dataDirectory.size() << " Valid Files" << endl;
    
    // Move To Data Directory
    cout << "Moving To Data Directory" << endl;
    for (int i = 0; i < dataDirectory.size(); i++) {
        ofFile file = dataDirectory.getFile(i);
        cout << "Moving File #" << i << endl;
        file.moveTo(pathToDataDirectory, true, false);
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
