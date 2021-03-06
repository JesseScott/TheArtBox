#pragma once

#include "ofMain.h"
#include "ofxFTP.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxFTPClient client;
        vector<string> fileNames;
        vector<string> trimmedFileNames;
        vector<string> existingFileNames;
        vector<string> newFileNames;
    
        ofDirectory dataDirectory;
        ofDirectory mediaDirectory;
        ofDirectory ftpDirectory;
    
        string pathToDataDirectory;
        string pathToLogsDirectory;
        string pathToUploadsDirectory;
    
        ofBuffer    credentials;
        string      host, username, password, port;
};
