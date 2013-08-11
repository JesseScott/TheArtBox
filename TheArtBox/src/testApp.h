#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

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
        void getIdealBrightness();
        void getCurrentBrightness();

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
        int idealBrightness;
        int currentBrightness;

        // Painting
        ofImage brush;
        bool bBrushDown;

        // Assets
        ofxXmlSettings assets;
        ofTrueTypeFont font;
        vector<string> artistNames;
        vector<string> artistMedia;

};
