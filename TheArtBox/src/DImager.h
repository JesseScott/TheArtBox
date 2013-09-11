

#pragma once

#include "ofMain.h"
#include "Shadow/ISensor.h"
#include "Shadow/IMotionSensor.h"
#include "Shadow/ShadowDefines.h"

using namespace Omek;

class DIMager {
	public:
		enum VIEW {
			DEPTH,
			MASK
		};

		DIMager();

		void update();
		ofTexture getTexture(int view);
		ofPixels getPixels(int view);
		int getWidth();
		int getHeight();

	private:
		IMotionSensor *motionSensor;
		ISensor *sensor;

		int width, height, channels, bpp;
		unsigned int imageBufferSize;

		ofTexture depth, mask;

		void updateDepth();
		void updateMask();
};
