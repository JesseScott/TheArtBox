#pragma once

// IMPORTS
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxXmlSettings.h"
//#include <windows.h>
//#include "psapi.h"

// DEFINES
#define WINVER 0x0601
#define DIV 1024
//#define INTERACTIVE
//#define KINECT

class ofApp : public ofBaseApp {
    
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
    void updateKinect();
    void updateWebcam();
    
    void updateBlobs();
    void updateMovies();
    void updateFBOs();
    void updateBrightness();
    void writeDiagnostics();
    
    void drawDebugView();
    void drawFBOView();
    void drawMediaView();
    void drawTrailerView();
	
    void loadFonts();
	void loadArtists();
    void setAssets(int index);
	void loadAssets();
    void updateCurrentIndex();
	
    void setColourThumbnailImage(int _width, int _height);
	void setBlackAndWhiteThumbnailImage(ofImage img);
	
    void setupGL(int _width, int _height);
    int getCurrentBrightness();
    
    void checkMemory();
    void getFilesFromFTP();
	
    void autoPlay();
	void learnBackground();
	
	// KINECT & OPENCV	
	ofxKinect kinect;
    ofVideoGrabber camera;
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
