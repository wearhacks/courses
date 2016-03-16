#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
const int SERVO = 3;
 
// variables to store our basic servo positions : up, stirring high, stirring low
const int STIR_UP = 160;    // when the tea is lifted out of the cup
const int STIR_HIGH = 130; // high position for stirring
const int STIR_LOW = 90; // low position for stirring

// Delay between each servo position adjustment during stirring
// A lower value is associated with a quicker stirring
int STIR_SMOOTH = 50;

const int STATUS_LED = 5; // Used to indicate that stirring is in progress
const int POWER_LED = 4; // Always on when the Arduino is powered

const int BUTTON = 6; // Starts stirring when pressed

const int TIME_POT = A5; // Potentiometer pin

const int BUZZER = 8; // Used to indicate end of stirring. Needs to be a PWM pin.
 
void setup() 
{ 
	// Set up LED pins
	pinMode(STATUS_LED, OUTPUT);
	pinMode(POWER_LED, OUTPUT);
  
	digitalWrite(POWER_LED, HIGH); // Turn on power led
	digitalWrite(STATUS_LED, LOW); // Turn off status led
  
	myservo.attach(SERVO);  // attaches the servo on pin 3 to the servo object
	myservo.write(STIR_UP); // put servo to up position, ready to receive tea bag
  
	pinMode(BUZZER, OUTPUT); // Set up buzzer pin 
	digitalWrite(BUZZER, LOW); 
	Serial.begin(9600); // uncomment to print duration value to Serial
} 
 
void loop() 
{ 
	// Get stirring time from potentiometer value
	long duration = getStirringTime();

	if (isButtonPressed()) {
		startStirring(duration);
	}
} 

void startStirring(long duration) {
/*
Moves servo from 'high' to stirring position and begin process. We keep track of the time 
that each stirring cycle took and subtract it to the duration passed as argument. 
When duration<0, we move the servo to 'high' position agin so that the tea bag is taken out from the cup. 
Two beeps are played by the buzzer and the status led is shut to indicate end of stirring. 
*/
	unsigned long referenceTime;
	
	moveServo(STIR_UP, STIR_HIGH);
	digitalWrite(STATUS_LED, HIGH);
	
	while(duration>0) {
		referenceTime = millis();
		stir();
		duration-= millis() - referenceTime;
	}
	
	moveServo(STIR_HIGH, STIR_UP);
	beepBuzzer();
	
	digitalWrite(STATUS_LED, LOW);
}

void stir() {
/*
We tell the servo to go from the STIR_HIGH to the STIR_LOW position, 
with a delay between each adjustment of position so that the movement is smooth.
*/ 
	moveServo(STIR_HIGH, STIR_LOW);
	moveServo(STIR_LOW, STIR_HIGH);
}


void moveServo(int startPosition, int stopPosition) {
	int pos;
	
	if (startPosition > stopPosition) {
		for(pos = startPosition; pos >= stopPosition; pos -= 1)     // goes from STIR_HIGH to UP since it's the last position atteigned in stir()
		{
			myservo.write(pos);              // tell servo to go to position in variable 'pos'
			delay(STIR_SMOOTH);                       // waits x ms for the servo to reach the position
		}		
	} else {
		for(pos = startPosition; pos <= stopPosition; pos += 1)     // goes from STIR_HIGH to UP since it's the last position atteigned in stir()
		{
			myservo.write(pos);              // tell servo to go to position in variable 'pos'
			delay(STIR_SMOOTH);                       // waits x ms for the servo to reach the position
		}		
	}
}

bool isButtonPressed() {
/*
When the button is pressed, the TIMER_BUTTON pin is connected to ground and thus reads LOW.
Alternatively, when the button is not pressed the pin is connected to 5v through the resistor and reads HIGH
*/
	return (digitalRead(BUTTON) ? false : true);
}

void beepBuzzer() {
/*
To indicate the end of stirring, we play a G	7(sol) twice for 1 second with a 2 second intermission.
*/
	tone(BUZZER, 3136, 1000);
	delay(2000);
	tone(BUZZER, 3136, 1000);
}

long getStirringTime() {
/*
Get analog value from potentiometer (range 0-1023), re-base between 0 and 10 and multiply by 60*1000 to get the time in milliseconds.
*/
	float time = mapFloat(analogRead(TIME_POT), 0, 1023, 0, 10);
	Serial.println(time); 
	long millisTime = (long)(time*60*1000);
	return millisTime;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
/*
Helper function used to re-map an number from one range to another. We don't use the native 'map' because it only returns integers. 
*/
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
