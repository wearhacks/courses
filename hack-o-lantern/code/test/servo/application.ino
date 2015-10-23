// Instanciate servo library.
// No need to import it since it is included in Spark's default libraries
Servo servo;

void setup() {
  servo.attach(D1); // Set pin that will control the servo
}

void loop() {
  for(int pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(int pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
  {
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
