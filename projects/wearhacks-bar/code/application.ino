#include "application.h"
#include "neopixel.h"

#define PUMP1_PIN D1
#define PUMP2_PIN D2
#define PUMP3_PIN D3
#define PUMP4_PIN D4

#define SERVING_TIME 20000

#define PIXEL_PIN A0
#define PIXEL_COUNT 17
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(40);

  pinMode(PUMP1_PIN, OUTPUT);
  pinMode(PUMP2_PIN, OUTPUT);
  pinMode(PUMP3_PIN, OUTPUT);
  pinMode(PUMP4_PIN, OUTPUT);

  Particle.function("pump1", pump1);
  Particle.function("pump2", pump2);
  Particle.function("pump3", pump3);
  Particle.function("pump4", pump4);
}

void loop() {
  rainbow(20);
}

int pump1(String arg) {
  digitalWrite(PUMP1_PIN, HIGH);
  delay(SERVING_TIME);
  digitalWrite(PUMP1_PIN, LOW);

  return 1;
}

int pump2(String arg) {
  digitalWrite(PUMP2_PIN, HIGH);
  delay(SERVING_TIME);
  digitalWrite(PUMP2_PIN, LOW);

  return 1;
}

int pump3(String arg) {
  digitalWrite(PUMP3_PIN, HIGH);
  delay(SERVING_TIME);
  digitalWrite(PUMP3_PIN, LOW);

  return 1;
}

int pump4(String arg) {
  digitalWrite(PUMP4_PIN, HIGH);
  delay(SERVING_TIME);
  digitalWrite(PUMP4_PIN, LOW);

  return 1;
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
