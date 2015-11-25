// Import library
#include <Manchester.h>

// Define pins
#define RX_PIN 4
#define LED_PIN 13

// Define global variable
uint8_t moo = 1;

void setup() {
	// Set-up status LED
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, moo);
	
	man.setupReceive(RX_PIN, MAN_4800); // Set-up transmissions with baud rate = 4800bps 
	man.beginReceive(); // Start receiving data
	
	Serial.begin(9600); // Start serial coms
}

void loop() {
	// If a message has been decoded, proceed with processing it
	if (man.receiveComplete()) {
		Serial.println("Message received: ")
		
		uint16_t m = man.getMessage(); // retrieve message
	
		Serial.print(m); // print to console
		
		man.beginReceive(); //start listening for next message right after you retrieve the message
		
		// Trigger status LED 
		moo = ++moo % 2;
		digitalWrite(LED_PIN, moo);
	}
}
