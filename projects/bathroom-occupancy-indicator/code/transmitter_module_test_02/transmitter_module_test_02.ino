// Import library
#include <Manchester.h>

// Define pins for each chip version
#if defined (__AVR_ATtiny85__)
	#define TX_PIN 1  //pin where your transmitter is connected
	#define LED_PIN 4 //pin for blinking LED
	#define SENSOR_PIN 3 //pin for the IR sensor
#else
	#define TX_PIN 4  //pin where your transmitter is connected
	#define LED_PIN 13 //pin for blinking LED
	#define SENSOR_PIN A0 //pin for the IR sensor
#endif


// Global variables
uint8_t moo = 1; //last led status

void setup() {
	//Set-up status LED
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, moo);
	
	pinMode(SENSOR_PIN, INPUT); // Set-up sensor analog pin
  
	man.setupTransmit(TX_PIN, MAN_4800); // Set-up transmissions with baud rate = 4800bps 
}

void loop() {
	uint16_t sensorReading = analogRead(SENSOR_PIN); // used to keep track of the number of cycles

	man.transmit(sensorReading); // transmit current number of cycles 
	
	// Trigger status LED 
	moo = ++moo % 2;
	digitalWrite(LED_PIN, moo);
}
