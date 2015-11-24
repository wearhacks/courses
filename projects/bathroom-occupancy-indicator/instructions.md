# The bathroom occupancy indicator
This project was born from a very common problem: our office's floor is equiped with one bathroom that can't be seen from every desk. Ensues uncessary back and forth when someone walks to the bathroom only to find it occupied. 

The solution ? A simple bathroom monitoring system composed of two devices: 
- An **emitter** placed on the inside of the door of the bathroom to monitor. An **infrared sensor** is directed toward the deadbold knob. A piece of black tape is applied on the knob. The idea is the following: when the door is unlocked, the knob's metallic surface is facing the sensor and reflecting a fair amount of IR light. When the door is locked, the taped part of the knob is now facing the sensor. Since the tape is black, the amount of IR light reflected decreases: we know that the door is locked. We use a **radio emitter** module to send the value read from the sensor to the receptor. A small Atmel microcontroller (the **ATtiny85**) acts as the brain of the system. The device runs on 4 AAA batteries and is put to sleep 5 seconds every time a reading is sent in order to save power. 
- The **receptor** is used to display the status of occupancy of the bathroom remotely. It is built around the same microcontroller as the emitter. A RF receptor picks up the readings from the emitter. Depending on the value received, we light up an RGB LED in green or red. This device runs on a wall wart since the LED is constantly turned on. 

Both devices are equiped of an ON/OFF switch. 



<img width="50%" height="50%" align="right" src="https://github.com/wearhacks/courses/tree/master/projects/bathroom-occupancy-indicator/img/"/>
<img width="50%" height="50%" align="right" src="https://github.com/wearhacks/courses/tree/master/projects/bathroom-occupancy-indicator/img/"/>

## Table of content


## Components list

- 2x Arduino Uno (possible to work with only one, doesn't need to be a Uno)
- 2x [ATtiny85](http://www.digikey.ca/product-detail/en/ATTINY85-20PU/ATTINY85-20PU-ND/735469) 
- 1x [RF Link Receiver](https://www.sparkfun.com/products/10533) (4800bps, 315/434Mhz)
- 1x [RF Link Emitter](https://www.sparkfun.com/products/10535) (4800bps, same as receiver)
- 1x [Reflective IR sensor](https://www.adafruit.com/products/2349) 
- 1x [Neopixel mini PCB](http://www.adafruit.com/products/1612)
- 1x [L7805 Voltage regulator](https://www.sparkfun.com/products/107)
- 1x 5mm LED 
- 1x 330μF capacitor
- 1x 1N4001 diode
- 2x 100Ohms resistors
- 1x 10kOhms resistor
- 1x 2.1mm power jack
- 2x ON/OFF switches
- 1x [12v wall adapter power supply](https://www.sparkfun.com/products/9442)
- 1x [4 AAA battery holder](https://abra-electronics.com/batteries-holders/battery-holders-aaa-cell/150-442-4-x-aaa-cell-piggyback-battery-holder-150-442.html)
- 4x AAA batteries
- 2x [project enclosures](https://abra-electronics.com/enclosures-boxes/plastic-box-generic/gpb321-plastic-box-30l-x-20w-x-10h-gpb321.html)
- 2x [perfboards](https://abra-electronics.com/boards/busboard/sb4-snappable-pc-breadboard.html)<br />
\+ breadboard<br />
\+ jumper wires <br />
\+ soldering equipment<br />
\+ hot glue gun<br />
\+ rotary tool<br />


# Walkthrough

## Testing the circuit 
The first thing we need to do is to test our components individually in order to make sure that everything is working properly. 

### Initial set-up 

### RF emitter/receptor + Arduino
#### Basic communication

#### Adding the IR sensor

### Switching to the ATtiny85
#### ATtiny + Neopixel
#### Emitter circuit 
#### Receptor circuit 


## Soldering the circuit 
### Emitter circuit 

### Receptor circuit

## Final assembly 
### Enclosure carving 
### Making the light diffuser
### Wrapping it up

# Sources