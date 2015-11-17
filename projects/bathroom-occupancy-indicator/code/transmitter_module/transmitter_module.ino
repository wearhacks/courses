#include <Manchester.h>

#define TX_PIN 0  //pin where your transmitter is connected
#define LED_PIN 4 //pin for blinking LED

uint8_t moo = 1; //last led status
uint16_t transmit_data = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, moo);
  man.setupTransmit(TX_PIN, MAN_4800);
}

void loop() {
  transmit_data = analogRead(3);
  man.transmit(transmit_data);
  moo = ++moo % 2;
  digitalWrite(LED_PIN, moo);
}
