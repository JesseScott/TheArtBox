#include "ofMain.h"
//#include "testApp.h"

class WorkerThread : public ofThread {

public:
	WorkerThread();
	~WorkerThread();




	void WorkerThread :: threadedFunction() {
	

		currentBrightness = 7; 
		count = 0; 

		while(isThreadRunning()) {

			// Convert to Pixels
			ofPixels wtPixels;
			lock();
				maskFbo.readToPixels(wtPixels, 0);
			unlock();

			//cout << "WTP HT " << wtPixels.getHeight() << endl;
		
			// Loop Through And Add All The Alpha Values
			for(int x = 0; x < wtPixels.getWidth(); x++) {
				for(int y = 0; y < wtPixels.getHeight(); y++) {
					ofColor c = wtPixels.getColor(x, y);
					currentBrightness += c.r;
					count++;
					cout << "CB: " << currentBrightness << "\t C.r " << c.r << endl;
				}
			}

			// Average Over the Total Number Of Pixels
			currentBrightness = currentBrightness / (count+1);
			cout << "WT::ALPHA IS " << currentBrightness << endl;
		}
	}
	/*
	void draw() {
		lock();
			maskFbo.draw(420, 630, 400, 300);
		unlock();
	}
	*/
	ofFbo maskFbo;
	int currentBrightness;
	int count;

};

