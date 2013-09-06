
#include "DIMager.h"

DIMager::DIMager() {
	motionSensor = IMotionSensor::createCameraSensor();	
	if (!motionSensor) cout << "Camera not found." << endl;

	sensor = motionSensor->getSensor();
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

	motionSensor->run();
}

void DIMager::update() {
	updateDepth();
	updateMask();
}

void DIMager::updateDepth() {
	int widthStep = 0;
	char *tmpDepth = (char *)malloc(imageBufferSize * sizeof(char*));

	if (motionSensor->hasNewFrameData(0)) {
		if (motionSensor->copyRawImage(tmpDepth, imageBufferSize, widthStep, true) == Omek::OMK_SUCCESS) {
			depth.loadData((const float *)tmpDepth, width, height, GL_LUMINANCE);
		}
	}

	delete tmpDepth;
}

void DIMager::updateMask() {
	int numPlayers = motionSensor->getNumOfPlayers();
	if (numPlayers > 0) {
		char *tmpMask = (char *)malloc(imageBufferSize * sizeof(char*));
		
		int w, h;
		float cen3D[] = {0, 0, 0};
		float cen2D[] = {0, 0};
		
		if (motionSensor->copyPlayerMask(tmpMask, imageBufferSize, 0, w, h, cen3D, cen2D) == OMK_SUCCESS) {
			mask.loadData((const float *)tmpMask, width, height, GL_LUMINANCE);
		}

		delete tmpMask;
	}
}

ofTexture DIMager::getTexture(int view) {
	if (view == MASK) {
		return mask;
	} else {
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