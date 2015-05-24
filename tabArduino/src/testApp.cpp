#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // Preanble
    cout << "Starting Program " << endl;
    cout << " --- " << endl;

    // Set Log Level (To Ensure Serial Debug Info Prints)
    ofSetLogLevel(OF_LOG_NOTICE);
    
    // Arduino
	ard.connect("/dev/tty.usbmodemfd141", 57600);
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;
    
    // Fonts
    font.loadFont("franklinGothic.otf", 20);
    smallFont.loadFont("franklinGothic.otf", 14);

}

void testApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
	
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
}

//--------------------------------------------------------------
void testApp::digitalPinChanged(const int & pinNum) {
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
}

//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
}

//--------------------------------------------------------------
void testApp::update(){

    	updateArduino();

}

void testApp::updateArduino(){
    
	// update the arduino, get any data or messages.
    // the call to ard.update() is required
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {
        // fade the led connected to pin D11
		ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
	}
    
}


//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(255, 255, 255);
	if (!bSetupArduino){
		font.drawString("arduino not ready...\n", 515, 40);
	} else {
		font.drawString(potValue + "\n" + buttonState +
						"\nsending pwm: " + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);
        
        ofSetColor(64, 64, 64);
        smallFont.drawString("If a servo is attached, use the left arrow key to rotate "
                             "\ncounterclockwise and the right arrow key to rotate clockwise.", 200, 550);
        ofSetColor(255, 255, 255);
        
	}

    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
