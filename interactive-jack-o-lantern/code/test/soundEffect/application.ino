/**
 * Global variables involved with the soundEffect module
*/
#define SOUND_PIN D6
bool isRunning = false;
unsigned long scheduledShutDown;

void setup() {
  Serial.begin(9600); // Start serial communications at 9600 bits/s
  pinMode(SOUND_PIN, OUTPUT); // Set-up sound module control pin
}

void loop() {
  // If something was sent on the serial console, read Serial
  if (Serial.available()) {
    int c = Serial.parseInt();

    // if 1 was sent, trigger sound for 4 seconds
    if (c == 1) {
      triggerSound();
    }
  }

  soundWatcher(); // checks if a sound shutdown was scheduled
}

// start sound effect sequence by setting the control pin to HIGH
// program a shutdown 4 seconds later
void triggerSound() {
    if (!isRunning) {
        digitalWrite(SOUND_PIN, HIGH);
        Serial.println("Sound started");
        scheduledShutDown = millis() + 4000;
        isRunning=true;
    }
}

void soundWatcher() {
    if (isRunning&&millis()>scheduledShutDown) {
        digitalWrite(SOUND_PIN, LOW);
        Serial.println("Sound stopped");
        isRunning=false;
    }
}
