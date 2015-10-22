# The project 
The goal of this project is to introduce basic concepts of IoT embedded programming through a seasonal and rather amusing angle. 

The idea is to make a jack-o-lantern controlled via twitter. Commands sent to a specific twitter account allow to change the color
of the light inside the pumpkin or perform a pre-defined animation such as opening the pumpkin or playing a spooky sound effect. 
A range sensor allows to trigger an action sequence if someone gets close to the jack-o-lantern. Finally a sound sensor can be used
to modulate the light according the the surrounding sound level. 

#### Components list
* 1x Spark core
* 1x [16 LEDs NeoPixel ring] (http://www.adafruit.com/products/1463) 
* 1x [2500mAh lipo battery] (http://www.adafruit.com/products/328)
* 1x [lipo usb charger/booster] (https://www.adafruit.com/products/259) or [similar](https://www.sparkfun.com/products/11231)
* 1x [HS-311 servo motor](https://www.servocity.com/html/hs-311_standard.html#.Vih94WvX2Iw)
* 1x [HC-SR04 ultrasonic range sensor](http://www.sainsmart.com/ultrasonic-ranging-detector-mod-hc-sr04-distance-sensor.html) 
* 1x [audio sensor breakout](http://www.adafruit.com/products/1063)
* 3x 470ohms resistors
* 1x S9013 npn transistor
* 1x diode (1N4001)
* 1x 1000uf capacitor
* 1x breadboard
* 1x perfboard
* 5x female headers
* 1x male header(1x3)
* jumper wires
* wires
* soldering equipment
* 1x hinge
* 2x wooden sticks 
* glue gun


# Walkthrough 
## Building the circuit 
#### LED ring
###### Schematics
###### Code

#### Sound Sensor
###### Schematics
###### Code

####Range Finder
###### Schematics
###### Code

####Servo motor
###### Schematics
###### Code

####Sound Effect module
###### Schematics
###### Code

#### Soldering the circuit


## Writing the code
#### Getting data from twitter
#### Defining our system's states
#### The main loop()

## Connect to twitter
### Registering a new application on twitter
### Configuring IoTDataProvider

## Final assembly
#### Carving the pumpkin
#### The opening mechanism
#### Putting it all together 

#The result
[![Watch]()]()
