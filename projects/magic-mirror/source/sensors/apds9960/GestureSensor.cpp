#include <iostream>
#include "APDS9960_RPi.h"

using namespace std;

// Pins
#define APDS9960_INT 7 // Needs to be an interrupt pin

// Constants

// Global Variables
APDS9960_RPi apds = APDS9960_RPi();
int isr_flag = 0;

// function declarations
void interruptRoutine();
void handleGesture();

int main() {

	// init wiringPi
	wiringPiSetup();

	// Initialize Serial port
	cout << "{\"info\": \"SparkFun APDS-9960 - GestureSensor\"}" << endl;

	// Initialize interrupt service routine
	wiringPiISR(APDS9960_INT, INT_EDGE_FALLING,  interruptRoutine);

	// Initialize APDS-9960 (configure I2C and initial values)
	if ( apds.init() ) {
		cout << "{\"info\": \"APDS-9960 initialization complete\"}" << endl;
	} else {
		cout << "{\"info\": \"Something went wrong during APDS-9960 init!\"}" << endl;
	}

	// Start running the APDS-9960 gesture sensor engine
	if ( apds.enableGestureSensor(true) ) {
		cout << "{\"info\": \"Gesture sensor is now running\"}" << endl;
	} else {
		cout << "{\"info\": \"Something went wrong during gesture sensor init!\"}" << endl;
	}

	while(1) {
		if( isr_flag == 1 ) {
			handleGesture();
			isr_flag = 0;
		}
	}
	return 0;
}

void interruptRoutine() {
	isr_flag = 1;
}

void handleGesture() {
	if ( apds.isGestureAvailable() ) {
		switch ( apds.readGesture() ) {
		case DIR_UP:
			cout << "{\"swipe\": \"up\"}" << endl;
			break;
		case DIR_DOWN:
			cout << "{\"swipe\": \"down\"}" << endl;
			break;
		case DIR_LEFT:
			cout << "{\"swipe\": \"left\"}" << endl;
			break;
		case DIR_RIGHT:
			cout << "{\"swipe\": \"right\"}" << endl;
			break;
		case DIR_NEAR:
			cout << "{\"swipe\": \"near\"}" << endl;
			break;
		case DIR_FAR:
			cout << "{\"swipe\": \"far\"}" << endl;
			break;
		default:
			cout << "{\"swipe\": \"none\"}" << endl;
		}
	}
	else {
		cout << "{\"error\": \"No gesture available\"}" << endl;
	}
}
