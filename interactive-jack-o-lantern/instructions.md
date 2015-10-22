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
* 1x jst connector (depending on your charger module 
* jumper wires
* wires
* soldering equipment
* 1x hinge
* 2x wooden sticks 
* glue gun


![BOM](https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/components_list.JPG "Components needed")

# Walkthrough 
We will start by testing every module of the circuit individually. In each case, a schematic of the circuit is provided, along with the corresponding code. 

The instructions explaining **how to upload the code** to your device are available [here](). 

## Building the circuit 
#### Battery set-up
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/bb_battery_module.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/battery_module_00.JPG"/>
The circuit is powered by a 3.7v 2500mAh lipo battery. However, some of our components need 5v to function correctly (the servo motor, the range sensor and the LEDs). 
This is where the battery charger/booster comes in. Addionnally to providing a way to charge the battery through a usb connection, it also transforms 
the 3.7 input voltage into a nice 5v that we need. 
The core is equipped with a voltage regulator that allows it to be powered through usb which delivers 5v. The voltage regulator is doing the exact inverse of our 
battery booster : it steps a 5v voltage down to the 3.3v that the core needs. By connecting the 5v output of our battery booster to the **Vin** and **GND** pin, 
we use the same voltage regulator to provide the appriopriate voltage to the spark. 

We also add a **decoupling capacitor**. Why ? Some of the components that we will be using sometimes experience spikes of current consumption (example: when the LEDs are turned on at full brightness, they can briefly sink in a lot of current).
Microcontrollers don't like variations in their input voltage. It tends to provoke unwanted resets and other instabilities. 
This is where the decoupling capacitor comes in handy: it's basically a very small and temporary battery. As long as the circuit is stable, it will stay charged and basically just sit here. 
But if a massive current consumption occurs, the capacitor will release its energy back into the circuit, exactly countering the drop in current. Think of it like a jar 
full of water turned upside down inside a bigger bowl also filled with water. If the level of the water in the bowl is higher than the opening of the jar, the water will stay quietly in the jar. 
The if the level drops underneath, the water of the jar will fall down back into the bowl, restoring the initial level. 

Keep your circuit set-up as it is, we will use it as-is for the next steps. 


#### LED ring
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/neopixel_module_00.JPG"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/neopixel_module_01.JPG"/>
These LEDs are very popular because of their low power consumption as well as their ability to be controled with just one pin. If you don't understand why this is 
such a nice feature, have a look at **multiplexing** on google and you'll quickly see that using only 1 pin to control 16 rgb LEDs is awesome.

Start by soldering the wires to your ring. 4 holes are available. You only want to solder **Vin**, **Gnd** and **Data IN**. 

###### Schematics
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/bb_neopixel_module.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/neopixel_module_02.JPG"/>
The circuit is very simple : Vin goes to the 5v power rail, GND to...you guessed it, the GND rail. And finally Data IN is connected to D2 on the spark. 
This is the pin that will send the instructions to the LEDs (which color and brightness to use. It's worth to mention that every LED on the ring can 
be controlled individually). 

Once again, don't unplug your components. We will use the LED ring to test the audio sensor's output in the next step. 

###### Code

#### Sound Sensor
A sound sensor works by detecting differences in air pressure and converting it into an electrical signal, much like your ear does! The key element of the mechanism 
is a piezzoelectric device. Piezzoelectric means that it converts a mechanical phenomenon (such as the vibration of the membrane caused by the difference in 
air pressure) into electricity. 
The current generated is so tiny that it needs to be amplified so that we can be fed to an microcontroller's input pin. 
###### Schematics
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/bb_neopixel_sound_module.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/sound_sensor_module_00.JPG"/>
The sound sensor is a 2.4->5v device, meaning that it can be fed any voltage that falls in that range. The output will be constrained by this value:
if say 3v are fed to the device, the output range will be [0;3v]. To simplify, if the device output equals 0v then ne sound is detected. If it is 3v, 
the maximal sound level is detected (the sensitivity can be adjusted by tweaking the potentiometer in the back, but the default value will do in our case).

Since our spark core is a 3.3v device, it expects inputs <= 3.3v. **Never more** (you could -and eventually will- damage your microcontroller). This is why
we will connect the sensor to the 3.3~v power line of the spark. You may notice that two 3.3v pins are available. We use this one because it is said to be *filtered*, 
meaning that it is especially made to provide a steady and reliable voltage for sensitive measurement devices such as our sound sensor. 

The output pin goes to the analog input pin A0. An analog input pin works by measuring the voltage being applyied to it.
It then returns the corresponding value to the microcontroller, mapped between 0 and 4096. 0 corresponds to 0v being applied to the pin, 4096 to 3.3v. 
We will use this value to determine the current sound level. 

The sound level is then used to light up the LED ring (the louder, the more LEDs will be turned on). 
###### Code

####Range Finder
The ultrasonic range finder is a pretty nifty device. It works very much like those radars you see in submarines, or like the system bats use to direct themselves. It sends an ultrasonic wave on one side and wait for it to bounce back on a surface placed in front of the sensor. 
The wave is picked up by the other side of the device on its way back. The time it took for the wave to make its round-way trip is passed through a simple formula which 
gives the corresponding distance between the sensor and the opposing surface.  

###### Schematics
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/bb_rangeSensor_module.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/range_sensor_module_00.JPG"/>
Unlike the sound sensor, the range finder is a strictly 5v device. So start by connecting the Vin pin to the 5v power rail 
(and as always, GND goes to GND. **Don't** plug it the other way around by mistake. You will burn your sensor). 
The **Trig** pin is to be connected to D4 on the spark. This pin is used to control when a sound wave is being sent. The result will come through the 
**Echo** pin. But wait, if the sensor outputs a 5v signal and the spark can only accept something <= 3.3v, how can we connect the two ?
We have to use a **voltage divider**. It's a simple circuit composed of two resistors that will sink part of the current to the GND so that
the output voltage is reduced. 
 

###### Code

####Servo motor
Unlike a DC motor that rotates perpetually when powered on, a servo motor works by receiving an angle option, and rotating its shaft to the following angle. 

###### Schematics
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/bb_servo_module.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/servo_module_00.JPG"/>
Use the male header to plug the servo to the breadboard. One side of the header may be a bit short to plug-in correctly, so don't hesitate to switch 
it for 3 jumper cables if you want. 
Connect the Vin cable to the 5v power rail and the GND to the GND rail. The control line (yellow cable) connects to D1 on the spark. 
Did you notice the new component ? It's a diode. We connect it in parrallel between Vin and the GND, as close as possible to the header. It is used to 
In this configuration, it is called a **flyback diode**. Let's come back to the water analogy we used earlier. Forget the bowl and imagine a stream of water. 
Sometimes when a device like a motor is being powered down (or for the servo, when the rotation has been executed), a reverse spike of voltage is being discharged
on the power line. Back to the stream: the reverse spike is like a wave that would travel through the stream in the opposite direction (you can experience 
this in a delta near the sea when the tide is rising). Well once again, the microcontroller wouldn't like that. So the diode will block any current stream going
in the wrong direction. 
 
###### Code

####Sound Effect module
This is where we put the "hack" in hacking. Playing sound with a microcontroller is not a trivial task, so we will cheat and steal a sound module from 
one of those "press me to play a sound" toys. This one was found in a local dollar store. 

After extracting the mechanism from the toy comes the fun part : figuring out how to use it with our circuit. In this case, a push-button was triggering 
the sound routine. A quick test of the PCB traces with a multimeter was enough to understand the mechanism : a pushbutton is used to trigger the sound
sequence by closing the circuit. We don't want to mechanically push a button to trigger the sound, so we have to find a way to trigger it remotly with 
an electrical signal. 
Fortunately, a **transistor** just does that (and much more but that's not on topic today): by providing a current to the **base** (the middle pin), 
we open the gate of the transistor, letting current flow from the **collector** (left pin) to the **emitter** (right pin). 
After a few trial and errors, it appeared that the most reliable way to control the sound module with a transistor was to permanently solder the 
connection that used to be controlled by the switch, and to let the transistor control the power line of the device. 
We thus take out the batteries and solder two wires to Vin and GND. 
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/soundEffect_module_00.JPG"/>
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/soundEffect_module_01.JPG"/>
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/soundEffect_module_02.JPG"/>
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/soundEffect_module_03.JPG"/>

###### Schematics
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/bb_soundEffect_module.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/soundEffect_module_04.JPG"/>
What happens is that now the module will play its sound effect as long as it is being powered. We connect the red wire (Vin) to the 5v power rail
of the breadboard. This time, the GND is not connected directly but through the transistor. The GND of the device is connected to the collector, 
the GND of the breadboard to the emitter. The base of the transistor is connected to pin D6 through a 470ohms resistor which is used to protect the transistor
from receiving too much current. 
If we set D6 to **LOW** (0v), the gate of the transistor is closed, no current can flow from Vin to GND on our device : it is turned off. 
If we set D6 to **HIGH** (3.3v), the gate of the transistor opens, current can flow and the device is on, playing its sound effect. 

###### Code

#### Complete circuit
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/circuit_schematic.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/bb_complete_circuit.png"/>
Time to put everything together. The image you see on the left is the **circuit schematic**, an abstract model of the circuit that allow a trained eye to 
quickly understand the different elements and their relations. Use it in addition with the right image in order to make the full circuit. 

![Circuit final](https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/complete_circuit_00.JPG "Final circuit")


#### Soldering the circuit

## Connect to twitter
Create a new twitter account if you don't already have one. 

### Registering a new application on twitter
You then need to create a new application on twitter. Note that you will need to have registered a phone number to your account in order to do that. 
By creating a new application, you're telling twitter that you want to use their services remotly and providing informations about the usage you intend to make. 
In return, they will deliver you credentials in order to do so. 
that you want to use their services externally. 
### Configuring IoTDataProvider

## Writing the code
#### Getting data from twitter
#### Defining our system's states
#### The main loop()

## Final assembly
#### Carving the pumpkin
<img width="33.15%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/pumpkin_module_00.JPG"/>
<img width="33.15%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/pumpkin_module_01.JPG"/>
<img width="33.15%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/pumpkin_module_02.JPG"/>
#### The opening mechanism
###### A hinge for the pumpkin
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/pumpkin_module_03.JPG"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/pumpkin_module_04.JPG"/>
###### Making the lever
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/hinge_module_00.JPG"/>
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/hinge_module_01.JPG"/>
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/hinge_module_02.JPG"/>
<img width="24.25%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/hinge_module_03.JPG"/>

<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/hinge_module_04.JPG"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/interactive-jack-o-lantern/img/hinge_module_05.JPG"/>


#### Putting it all together 

#The result
[![Watch]()]()
