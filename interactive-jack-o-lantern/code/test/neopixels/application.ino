#include "application.h"
#include "neopixel.h"

#define NEOPIXEL_PIN D2
#define N_PIXELS 16
#define PIXEL_TYPE WS2812B
#define BRIGHTNESS 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, NEOPIXEL_PIN, PIXEL_TYPE);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  rainbow(20);
}


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
