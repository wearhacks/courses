#include "application.h"
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
  Serial.begin(9600);
}

void loop() {
  static int nextTime = 0;

  if (millis()>nextTime) {
    int distanceCm = distanceSensor.getDistanceCM();
    int distanceInch = distanceSensor.getDistanceInch();
    Serial.println("Distance in cm: " + String(distanceCm));
    Serial.println("Distance in inches: " + String(distanceInch));

    nextTime += 1000;
  }
}
