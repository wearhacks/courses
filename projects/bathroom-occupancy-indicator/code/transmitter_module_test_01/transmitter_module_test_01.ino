// Import library
#include <Manchester.h>

// Define pins
#define TX_PIN 4  //pin where your transmitter is connected
#define LED_PIN 13 //pin for blinking LED

// Global variables
uint8_t moo = 1; //last led status

void setup() {
	//Set-up status LED
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, moo);
  
	man.setupTransmit(TX_PIN, MAN_4800); // Set-up transmissions with baud rate = 4800bps 
}

void loop() {
	static uint16_t counter = 0; // used to keep track of the number of cycles

	man.transmit(counter); // transmit current number of cycles 
	
	// Trigger status LED 
	moo = ++moo % 2;
	digitalWrite(LED_PIN, moo);
	
	counter++;
}
