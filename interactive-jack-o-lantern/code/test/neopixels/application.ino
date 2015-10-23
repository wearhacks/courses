#include "application.h"
// Comment the following line if uplading from the online IDE
// and add the libraries manually
#include "neopixel.h"

// Define neopixel ring variables
#define NEOPIXEL_PIN D2
#define N_PIXELS 16
#define PIXEL_TYPE WS2812B
#define BRIGHTNESS 10 // available range : [0;50]

// Instanciate neopixel library
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, NEOPIXEL_PIN, PIXEL_TYPE);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // initialize all pixels to 'off'
}

void loop() {
  rainbow(20); // display rainbow animations
}

// This is a slight variation from the rainbow example from the library in that
// it works without blocking the main loop
void rainbow(unsigned long wait) {
    static unsigned long lastMillis = 0;
    static int j = 0;

    if (millis() - lastMillis >= wait) {
        int i = 0;
            for(i=0; i<strip.numPixels(); i++) {
                strip.setPixelColor(i, Wheel((i+j) & 255));
            }
            j++;

            strip.show();
            lastMillis = millis();
            if (j==256) j=0;
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
