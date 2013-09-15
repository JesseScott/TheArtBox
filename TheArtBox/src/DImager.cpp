
#include "DIMager.h"

DIMager::DIMager() {
	motionSensor = IMotionSensor::createCameraSensor();	
	if (!motionSensor) cout << "Camera not found." << endl;

	sensor = motionSensor->getSensor();
	motionSensor->setCameraSetup(6, 0);
	if(!sensor->isAlive()) cout << "Failed to initialize." << endl;

	motionSensor->setVerbosityLevel(3, "log4cxx.cfg");

	cout << "Flip Image " << sensor->setCameraParameter("flipped", 1) << endl;
	cout << "Set Max Players (2) " << motionSensor->setMaxCandidates(2) << endl;

	width = sensor->getImageWidth(IMAGE_TYPE_COLOR);
	height = sensor->getImageHeight(IMAGE_TYPE_COLOR);
	channels = sensor->getImageChannels(IMAGE_TYPE_COLOR);
	bpp = sensor->getImageBpp(IMAGE_TYPE_COLOR) / 8; // Bits Per Pixel

	imageBufferSize = width * height * channels * bpp;

	depth.allocate(width, height, GL_LUMINANCE);
	mask.allocate(width, height, GL_LUMINANCE);

	if (motionSensor->run() == OMK_SUCCESS) cout << "DImager Running" << endl;

}

void DIMager::update() {
	//cout << "Updating..." << sensor->getFramenum() << endl;
	updateMask();
	updateDepth();
	
	//
	cout << "Candiates " << motionSensor->getNumOfCandidates() << endl;
	//motionSensor->startTracking(1);

}

void DIMager::updateDepth() {
	int widthStep = 0;
	char *tmpDepth = (char *)malloc(imageBufferSize * sizeof(char*));
	unsigned char *ucDepth = (unsigned char *)tmpDepth;

	ofPixels pix;
	pix.allocate(width, height, OF_IMAGE_GRAYSCALE);
	pix.setFromExternalPixels(ucDepth, width, height, 2);

	if (motionSensor->hasNewFrameData(0)) {
		//cout << "hAS dATA " << endl;
		if (motionSensor->copyRawImage(tmpDepth, imageBufferSize, widthStep, true) == Omek::OMK_SUCCESS) {
			//cout << "cOPY Success " << endl;
			//depth.loadData((const float *)tmpDepth, width, height, GL_LUMINANCE);
			depth.loadData(pix);
		}
	}

	delete tmpDepth;
}

void DIMager::updateMask() {
	int numPlayers = motionSensor->getNumOfPlayers();

	if (numPlayers > 0) {
		char *cMask = (char *)malloc(imageBufferSize * sizeof(char*));
		unsigned char *ucMask = (unsigned char *)cMask;
		
		int w, h;
		float cen3D[] = {0, 0, 0};
		float cen2D[] = {0, 0};

		ofPixels pix;
		pix.allocate(width, height, OF_IMAGE_GRAYSCALE);
		pix.setFromExternalPixels(ucMask, width, height, 1);

		if (motionSensor->copyPlayerMask(cMask, imageBufferSize, 0, w, h, cen3D, cen2D) == OMK_SUCCESS) {
			mask.loadData(pix);
		}

		delete cMask;
	}
}

ofTexture DIMager::getTexture(int view) {
	
	if (view == MASK) {
		//cout << "MASK" << endl;
		return mask;
	} else if(view == DEPTH) {
		//cout << "DEPTH" << endl;
		return depth;
	}
	else {
		//cout << "ELSE" << endl;
		return depth;
	}
}

ofPixels DIMager::getPixels(int view) {
	if (view == MASK) {
		ofPixels p;
		mask.readToPixels(p);
		return p;
	}
}

int DIMager::getWidth() {
	return width;
}

int DIMager::getHeight() {
	return height;
}