#include "application.h"
// Comment the following line if uplading from the online IDE
// and add the libraries manually
#include "HC_SR04.h" // distance sensor library

#define TRIG_PIN D4
#define ECHO_PIN D5 // pins used by the range sensor

/**
* Instanciate distance sensor lib
* the two last options are the min and max distance at which
* the sensor will react (in cm). If the distance measured falls
* outside that range, the result will be -1
*/
HC_SR04 distanceSensor = HC_SR04(TRIG_PIN, ECHO_PIN, 2, 100);

void setup() {
  Serial.begin(9600); // Begin serial communications at 9600 bits/s
}

void loop() {
  static int nextTime = 0; // this structure is used instead of a delay() so that the main loop is never blocked

  if (millis()>nextTime) {
    // get distances from sensor
    int distanceCm = distanceSensor.getDistanceCM();
    int distanceInch = distanceSensor.getDistanceInch();
    // print distances to serial console
    Serial.println("Distance in cm: " + String(distanceCm));
    Serial.println("Distance in inches: " + String(distanceInch));

    nextTime += 1000;
  }
}
