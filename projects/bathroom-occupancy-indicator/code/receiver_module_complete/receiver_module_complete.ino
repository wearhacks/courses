#include <Manchester.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif



#define LED_PIN            3
#define RX_PIN 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

  uint16_t m;






void setup() {
  man.setupReceive(RX_PIN, MAN_4800);
  man.beginReceive();
  //Serial.begin(9600);
  
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50);
  

}

void loop() {


    
  if (man.receiveComplete()) {
    m = man.getMessage();
     //Serial.println(m);
    man.beginReceive(); //start listening for next message right after you retrieve the message
  }
  
  if (m<700) {
    pixels.setPixelColor(0, pixels.Color(250,0,0));
    pixels.show();
    //Serial.println("A");
  } else if (m>1000) {
      pixels.setPixelColor(0, pixels.Color(0,250,0));
      pixels.show();
     // Serial.println("B");
  } 

  
}





