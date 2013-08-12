#pragma once

// OF
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxFTP.h"

// MEMORY USAGE
#define WINVER 0x0601
#define DIV 1024
#include <windows.h>
#include "psapi.h"

// CPU USAGE
//#include "TCHAR.h"
//#include "pdh.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Added Methods
		void loadFonts();
		void loadArtists();
        void setAssets(int index);
		void loadAssets();

		void setColourThumbnailImage(int _width, int _height);
		void setBlackAndWhiteThumbnailImage(ofImage img);
		void updateCurrentIndex();

        void setupGL(int _width, int _height);
        int getCurrentBrightness();

        void checkMemory();
        void getFilesFromFTP();

        // Canvas
        ofImage foreground;
        ofImage thumbnail;
        ofVideoPlayer video;
        ofImage image;
        int width, height;
        int maxIndex;
        int currentIndex;
        bool currentAssetIsMovie;

        // GL / GPU
        ofShader shader;
        ofFbo maskFbo;
        ofFbo fbo;
        int currentBrightness;

        // Painting
        ofImage brush;
        bool bBrushDown;

        // Assets
        ofxXmlSettings assets;
        ofTrueTypeFont font;
        vector<string> artistNames;
        vector<string> artistMedia;

        // FTP
        ofxFTPClient client;

};
