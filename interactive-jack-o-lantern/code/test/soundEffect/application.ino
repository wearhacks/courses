/**
 * Global variables involved with the soundEffect module
*/
#define SOUND_PIN D6
bool isRunning = false;
unsigned long scheduledShutDown;

void setup() {
  Serial.begin(9600);
  pinMode(SOUND_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    int c = Serial.parseInt();

    if (c == 1) {
      triggerSound();
    }
  }

  soundWatcher();
}

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
