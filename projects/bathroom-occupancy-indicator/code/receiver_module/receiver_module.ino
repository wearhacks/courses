#include <Manchester.h>

#define RX_PIN 4
#define LED_PIN 13

uint8_t moo = 1;

void setup() {
  pinMode(LED_PIN, OUTPUT);  
  sdigitalWrite(LED_PIN, moo);
  man.setupReceive(RX_PIN, MAN_4800);
  man.beginReceive();
  Serial.begin(9600);
}

void loop() {
  if (man.receiveComplete()) {
    uint16_t m = man.getMessage();
    Serial.println(m);
    man.beginReceive(); //start listening for next message right after you retrieve the message
    moo = ++moo % 2;
    digitalWrite(LED_PIN, moo);
  }
}


