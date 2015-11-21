#include <Servo.h>

Servo servo;     
int angle;   
int newangle;
// state of the serial protocol: 0 =  waiting for intial 'D'. 
// 1 = initial 'D' received, 2 = digit 1 received, 3 = digit 2
// received, 4 = digit 3 received
char state = 0;

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(115200);
  servo.attach(9);
  angle = 90;
}

void loop() {
  servo.write(angle);
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'D') {
      state = 1;
      newangle = 0;
    } else if (c >= '0' && c <= '9' && state > 0) {
      newangle = newangle * 10 + (c - '0');
      state++;
      if (state == 4) {
        // if all three digits received, update the angle
        angle = newangle;
        state = 0;
      }
    }
  }
}
