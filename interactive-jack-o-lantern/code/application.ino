// This #include statement was automatically added by the Particle IDE.
#include "SparkIntervalTimer/SparkIntervalTimer.h"

#include "application.h"
#include "HttpClient/HttpClient.h" // http client library used to make GET request to data provider
#include "neopixel/neopixel.h" // library for the neopixel ring
#include "HC_SR04/HC_SR04.h" // distance sensor library
#include <math.h>


IntervalTimer Timer1;
IntervalTimer Timer2;

/**
 * Pins definition
*/
#define SOUND_PIN D6 // used to trigger the sound module
#define TRIG_PIN D4
#define ECHO_PIN D5 // pins used by the range sensor
#define MIC_PIN A0
#define NEOPIXEL_PIN D2

/**
* Vu-meter constants and variables definition
*/
#define N_PIXELS 16
#define PIXEL_BRIGHTNESS 10 // define brightness of the ring here (0->50)
#define PIXEL_TYPE WS2812B
#define SAMPLE_WINDOW   20  // Sample window for average level
#define PEAK_HANG 24 //Time of pause before peak dot falls
#define PEAK_FALL 4 //Rate of falling peak dot
#define INPUT_FLOOR 768 //Lower range of analogRead input
#define INPUT_CEILING 4096 //Max range of analogRead input, the lower the value the more sensitive (1023 = max)
byte peak = 16;      // Peak level of column; used for falling dots
unsigned int sample;
byte dotCount = 0;  //Frame counter for peak dot
byte dotHangCount = 0; //Frame counter for holding peak dot

Adafruit_NeoPixel pixRing = Adafruit_NeoPixel(N_PIXELS, NEOPIXEL_PIN, PIXEL_TYPE); // Instanciate Neopixel lib


/**
* HTTP Client variables
*/
#define WAIT 30000 // delay between requests in ms
#define HOST "digitaljunky.io"
#define PORT 3000
String API_KEY = "51f02abbbf241e498b8819bbb141af12";
String PATH = "/clients/payload?key=";
unsigned int nextTime = 0;    // Next time to contact the server
HttpClient http; // instanciate HttpClient lib

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;


/**
* Instanciate distance sensor lib
* the two last options are the min and max distance at which
* the sensor will react (in cm). If the distance measured falls
* outside that range, the result will be -1
*/
#define TRIGGER_DISTANCE 5
HC_SR04 distanceSensor = HC_SR04(TRIG_PIN, ECHO_PIN, 2, 100);


/**
 * Initialise our state variables to 0
 * They will store the values sent from twitter
 * later on
*/
int mode = 0;
int action = 0;
int last_action = 0;
int ledMode = 0;
int r = 0;
int g = 0;
int b =0;

/**
 * Global variables involved with the sound module
*/
bool isRunning = false;
unsigned long scheduledShutDown;


void setup() {
    // Set up sound trigger pin
    pinMode(SOUND_PIN, OUTPUT);
    digitalWrite(SOUND_PIN, LOW);

    // Setup neopixel ring
    pixRing.begin();
    pixRing.setBrightness(PIXEL_BRIGHTNESS);
    pixRing.show(); // initialize all pixels to 'off'

    Serial.begin(9600);
}

void loop() {
    //Serial.println(distanceSensor.getDistanceCM());
    // If it's time to make the request, JUST DO IT!!
    if (nextTime<millis()) {
        // Set up http request
        request.hostname = HOST;
        request.port = PORT;
        request.path = PATH + API_KEY;

        http.get(request, response, headers); // DO IT NOW!!!

        // if the response is not an error code,
        // proceed with interpretation
        if (response.body.toInt() != -1) {
            String mode_str = response.body.substring(1, 2);
            String action_str = response.body.substring(3, 4);
            String ledMode_str = response.body.substring(5, 6);
            // convert string values as int
            mode = mode_str.toInt();
            action = action_str.toInt();
            ledMode = ledMode_str.toInt();

            // If ledMode is 'color', extract rgb value as well
            if (ledMode == 3) {
                String r_str = response.body.substring(7,10);
                String g_str = response.body.substring(11,14);
                String b_str = response.body.substring(15,18);

                r = r_str.toInt();
                g = g_str.toInt();
                b = b_str.toInt();
            }
        }

        nextTime = millis() + WAIT;
    }

    /**
     * Global modes :
     * 1 -> automatic
     * 2 -> manual
    */
    switch (mode) {
        case 1:
            autoRoutine();
            break;
        case 2:
            if (action!=last_action) {
                last_action = processAction(action);
            }
            break;
        default:
            autoRoutine();
            break;
    }

    /**
     * Neopixel ring modes :
     * 1 -> sound reactive
     * 2 -> rainbow animation
     * 3 -> single color
    */
    switch (ledMode) {
        case 1:
            updateVuMeter();
            break;
        case 2:
            rainbow(20);
            break;
        case 3:
            setColor(r, g, b);
            break;
        default:
            rainbow(20);
            break;
    }

    soundWatcher();

}

void autoRoutine() {
    double distance = distanceSensor.getDistanceCM();     // get distance from sensor in cm
    //Serial.println(distance);
    if (distance != -1 && distance < TRIGGER_DISTANCE) {

        Serial.println("YES");
        triggerSound();
        //openPumpkin();
        //Timer1.begin(closePumpkin, 20000, hmSec);
    }
}

int processAction(int code) {
    switch(code) {
        case 1:
            triggerSound();
            openPumpkin();
            Timer1.begin(closePumpkin, 20000, hmSec);
            break;
        case 2:
            openPumpkin();
            break;
        case 3:
            closePumpkin();
            break;
        case 4:
            triggerSound();
            break;
    }
    return code;
}

void triggerSound() {
    if (!isRunning) {
        digitalWrite(SOUND_PIN, HIGH);
        scheduledShutDown = millis() + 4000;
        isRunning=true;

    }
}

void soundWatcher() {
    if (isRunning&&millis()>scheduledShutDown) {
        digitalWrite(SOUND_PIN, LOW);
        isRunning=false;
    }
}

void openPumpkin() {

}

void closePumpkin() {
    Timer1.end();
}


void setColor(int r, int g, int b) {
    for (int i=0; i<N_PIXELS; i++) {
        pixRing.setPixelColor(i, r, g, b);
    }
    pixRing.show();
}

void rainbow(unsigned long wait) {
    static unsigned long lastMillis = 0;
    static int j = 0;
    //Serial.println("rainbow :");
    //Serial.println(lastMillis);
    //Serial.println(j);

    if (millis() - lastMillis >= wait) {
        int i = 0;
        // for(j; j<256; j++) {
            for(i=0; i<pixRing.numPixels(); i++) {
                pixRing.setPixelColor(i, Wheel((i+j) & 255));
            }
            j++;
            //Serial.println("rainbow j: ");
            //Serial.print(j);
            pixRing.show();
            lastMillis = millis();
            if (j==256) j=0;
            // break;
        // }
    }
}

/**
 * Vue-meter related functions
*/
void updateVuMeter() {
  unsigned long startMillis= millis();  // Start of sample window
  float peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 4096;
  unsigned int c, y;


  // collect data for length of sample window (in mS)
  while (millis() - startMillis < SAMPLE_WINDOW)
  {
    sample = analogRead(MIC_PIN);
    if (sample < 4096)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude

  //Fill the strip with rainbow gradient
  for (int i=0;i<=pixRing.numPixels()-1;i++){
    pixRing.setPixelColor(i,Wheel(map(i,0,pixRing.numPixels()-1,30,150)));
  }


  //Scale the input logarithmically instead of linearly
  c = fscale(INPUT_FLOOR, INPUT_CEILING, pixRing.numPixels(), 0, peakToPeak, 2);

  if(c < peak) {
    peak = c;        // Keep dot on top
    dotHangCount = 0;    // make the dot hang before falling
  }
  if (c <= pixRing.numPixels()) { // Fill partial column with off pixels
    drawLine(pixRing.numPixels(), pixRing.numPixels()-c, pixRing.Color(0, 0, 0));
  }

  // Set the peak dot to match the rainbow gradient
  y = pixRing.numPixels() - peak;

  pixRing.setPixelColor(y-1,Wheel(map(y,0,pixRing.numPixels()-1,30,150)));

  pixRing.show();

  // Frame based peak dot animation
  if(dotHangCount > PEAK_HANG) { //Peak pause length
    if(++dotCount >= PEAK_FALL) { //Fall rate
      peak++;
      dotCount = 0;
    }
  }
  else {
    dotHangCount++;
  }
}



//Used to draw a line between two points of a given color
void drawLine(uint8_t from, uint8_t to, uint32_t c) {
  uint8_t fromTemp;
  if (from > to) {
    fromTemp = from;
    from = to;
    to = fromTemp;
  }
  for(int i=from; i<=to; i++){
    pixRing.setPixelColor(i, c);
  }
}


float fscale( float originalMin, float originalMax, float newBegin, float
newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range
  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float

  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  return rangedValue;
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return pixRing.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return pixRing.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return pixRing.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
