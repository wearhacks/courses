// Import libraries
#include <Manchester.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
	#include <avr/power.h>
#endif

// Define pins
#define LED_PIN 3
#define RX_PIN 1

// Instanciate neopixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);


// Parameters used to detect a locked/unlocked door
// Make your own tests and set your own values since it will depend on
// the reflectivity of your knob/the distance of the sensor from it etc. 
int closedReflectivity = 980;
int openReflectivity = 930;
uint16_t m = 0; // door open on start

void setup() {
	man.setupReceive(RX_PIN, MAN_4800); // Set-up transmissions with baud rate = 4800bps
	man.beginReceive(); // Start receiving data
  
	#if defined (__AVR_ATtiny85__)
		if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	#endif

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
	
	// If a message has been decoded, proceed with processing it
	if (man.receiveComplete()) {
		m = man.getMessage()
		man.beginReceive(); //start listening for next message right after you retrieve the message
	}
  
	// Light up every in red or green depending on the IR sensor's value
	if (m>closedReflectivity) {
		pixels.setPixelColor(0, pixels.Color(250,0,0)); // red
		pixels.show();
	} else if (m<openReflectivity) {
		pixels.setPixelColor(0, pixels.Color(0,250,0)); // green
		pixels.show();
	} 
  
}





