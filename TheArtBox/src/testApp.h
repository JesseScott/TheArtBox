#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxXmlSettings.h"
#include "WorkerThread.h"

// MEMORY USAGE
#define WINVER 0x0601
#define DIV 1024
#include <windows.h>
#include "psapi.h"


class testApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void drawPointCloud();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	ofxKinect kinect;
	
	ofxCvColorImage colorImg;
	
	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	ofxCvGrayscaleImage grayBg;
	ofxCvGrayscaleImage grayDiff;

	ofxCvContourFinder contourFinder;

	ofFbo closePoints; 

	int minBlob; 
	int maxBlob; 
	
	bool bThreshWithOpenCV;
	bool bDrawPointCloud;
	bool tooSunny;
	int  threshold;
	bool bLearnBakground;
	
	int nearThreshold;
	int farThreshold;
	
	int angle;

	ofImage stamp; 
	
	// used for viewing the point cloud
	ofEasyCam easyCam;

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
		ofVideoPlayer demo;
        ofVideoPlayer video;
        ofImage image;
		int imageTimer; 
		int playState;
        int width, height;
        int maxIndex;
        int currentIndex;
        bool currentAssetIsMovie;
		bool presenting;
		bool showDemo;

        // GL / GPU
        ofShader shader;
        ofFbo maskFbo;
        ofFbo fbo;
        int currentBrightness;
		int fboAge; 
		int targetAlpha;

        // Painting
        ofImage brush;
        bool bBrushDown;

        // Assets
        ofxXmlSettings assets;
        ofTrueTypeFont font;
        vector<string> artistNames;
        vector<string> artistMedia;

		// Thread
		WorkerThread thread;

};