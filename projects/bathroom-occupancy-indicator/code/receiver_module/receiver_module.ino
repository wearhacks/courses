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
int closedReflectivity = 920;
int openReflectivity = 905;
uint16_t m = 0; // door open on start
long lastUpdate = 0;
long timeout = 3000000;

void setup() {

	man.setupReceive(RX_PIN, MAN_4800); // Set-up transmissions with baud rate = 4800bps
	man.beginReceive(); // Start receiving data
  
	#if defined (__AVR_ATtiny85__)
		if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	#endif

  pixel.begin(); // This initializes the NeoPixel library.
      		pixel.setPixelColor(0, pixel.Color(0,0,200)); // orange
		pixel.show();

}

void loop() {
	
	// If a message has been decoded, proceed with processing it
	if (man.receiveComplete()) {
		m = man.getMessage();
		man.beginReceive(); //start listening for next message right after you retrieve the message
                lastUpdate = millis();

	}
  
	// Light up every in red or green depending on the IR sensor's value
        if ((millis()-lastUpdate) > timeout) {
    		pixel.setPixelColor(0, pixel.Color(204,102,0)); // orange
		pixel.show();
        }
	else if (m>closedReflectivity) {
		pixel.setPixelColor(0, pixel.Color(250,0,0)); // red
		pixel.show();
	} else if (m<openReflectivity) {
		pixel.setPixelColor(0, pixel.Color(0,250,0)); // green
		pixel.show();
	} 
  
}





