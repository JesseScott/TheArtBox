#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxXmlSettings.h"

// MEMORY USAGE
#define WINVER 0x0601
#define DIV 1024
#include <windows.h>
#include "psapi.h"


class testApp : public ofBaseApp {
public:
	
	// BASE METHODS
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	// CUSTOM METHODS
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
	void autoPlay();
	
	// KINECT & OPENCV	
	ofxKinect kinect;
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage grayThreshNear;
	ofxCvGrayscaleImage grayThreshFar; 
	ofxCvGrayscaleImage grayBg;
	ofxCvGrayscaleImage grayDiff;
	ofxCvContourFinder contourFinder;
	ofFbo closePoints; 
	int minBlob; 
	int maxBlob; 
	bool bThreshWithOpenCV;
	bool tooSunny;
	int  threshold;
	bool bLearnBakground;
	int nearThreshold;
	int farThreshold;
	int angle;
	ofEasyCam easyCam;

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
	ofImage stamp; 

	// Painting
	ofImage brush;
	bool bBrushDown;

	// Assets
	ofxXmlSettings assets;
	ofTrueTypeFont font;
	vector<string> artistNames;
	vector<string> artistMedia;


};