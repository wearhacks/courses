#include <Wire.h>
#include "ZX_Sensor.h"

// Constants
const int ZX_ADDR = 0x10;    // ZX Sensor I2C address
const int INTERRUPT_NUM = 0; // Pin 2 on the UNO

// Global Variables
ZX_Sensor zx_sensor = ZX_Sensor(ZX_ADDR);
volatile GestureType gesture;
volatile bool interrupt_flag;
uint8_t gesture_speed;

void setup() {
  
  uint8_t ver;
  
  // Initialize gesture to no gesture
  gesture = NO_GESTURE;

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println("---------------------------------------------");
  Serial.println("SparkFun/GestureSense - I2C Gesture Interrupt");
  Serial.println("Note: higher 'speed' numbers mean slower");
  Serial.println("---------------------------------------------");
  
  // Initialize ZX Sensor (configure I2C and read model ID)
  if ( zx_sensor.init(GESTURE_INTERRUPTS) ) {
    Serial.println("ZX Sensor initialization complete");
  } else {
    Serial.println("Something went wrong during ZX Sensor init!");
  }
  
  // Read the model version number and ensure the library will work
  ver = zx_sensor.getModelVersion();
  if ( ver == ZX_ERROR ) {
    Serial.println("Error reading model version number");
  } else {
    Serial.print("Model version: ");
    Serial.println(ver);
  }
  if ( ver != ZX_MODEL_VER ) {
    Serial.print("Model version needs to be ");
    Serial.print(ZX_MODEL_VER);
    Serial.print(" to work with this library. Stopping.");
    while(1);
  }
  
  // Read the register map version and ensure the library will work
  ver = zx_sensor.getRegMapVersion();
  if ( ver == ZX_ERROR ) {
    Serial.println("Error reading register map version number");
  } else {
    Serial.print("Register Map Version: ");
    Serial.println(ver);
  }
  if ( ver != ZX_REG_MAP_VER ) {
    Serial.print("Register map version needs to be ");
    Serial.print(ZX_REG_MAP_VER);
    Serial.print(" to work with this library. Stopping.");
    while(1);
  }
  
  // Initialize interrupt service routine
  interrupt_flag = false;
  zx_sensor.clearInterrupt();
  attachInterrupt(INTERRUPT_NUM, interruptRoutine, RISING);
  Serial.println("Interrupts now configured. Gesture away!");
}

void loop() {
  
  // If we have an interrupt, read and print the gesture
  if ( interrupt_flag ) {
    
    // Clear the interrupt flag
    interrupt_flag = false;
    
    // You MUST read the STATUS register to clear interrupt!
    zx_sensor.clearInterrupt();
    
    // Read last gesture
    gesture = zx_sensor.readGesture();
    gesture_speed = zx_sensor.readGestureSpeed();
    switch ( gesture ) {
      case NO_GESTURE:
        Serial.println("{\"swipe\": \"missed\"}");
        break;       
      case RIGHT_SWIPE:
        Serial.print("{\"swipe\": \"right\", \"speed\": ");
        Serial.print(gesture_speed, DEC);
        Serial.println("}");
        break;
      case LEFT_SWIPE:
        Serial.print("{\"swipe\": \"left\", \"speed\": ");
        Serial.print(gesture_speed, DEC);
        Serial.println("}");
        break;
      case UP_SWIPE:
        Serial.print("{\"swipe\": \"up\", \"speed\": ");
        Serial.print(gesture_speed, DEC);
        Serial.println("}");
        break;
      default:
        break;
    }
  }
}

void interruptRoutine() {
  interrupt_flag = true;
}
