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

		// Added
		void loadFonts();
		void loadAssets();
		void loadArtists();

        // Variables
        ofImage foreground;
        ofImage thumbnail;
        ofVideoPlayer video;
        ofImage brush;

        ofShader shader;
        ofFbo maskFbo;
        ofFbo fbo;
        bool bBrushDown;

        ofxXmlSettings assets;
        ofTrueTypeFont font;

        vector<string> artistNames;
        vector<string> artistMedia;

};
