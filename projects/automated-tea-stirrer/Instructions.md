# The automated tea stirrer

This document provides instructions and explanations for completing the first workshop.
The goal is to make an **automated tea stirrer** using an **Arduino Uno** as microcontroller. 
This project provides a good way to introduce basics concepts of embedded programming, from lighting up an LED
to dealing with an analog input, controlling a servo motor and keeping track of time. 

Basics soldering skills are required to complete the project, although jumper wires and a small breadboard 
can be used instead of the perfboard. 

###Parts list :
* 1x frame kit
* 1x Arduino Uno
* 1x 9g servo motor
* 1x Piezo buzzer
* 1x 9v battery holder
* 1x 9v battery
* 1x potentiometer
* 1x pushbutton 
* 1x On/Off button
* 2x 270ohms resistors
* 1x 330ohms resistor
* 1x 10kohms resistor 
* 1x green 5mm LED
* 1x red 5mm LED

![BOM](https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/00_components.JPG "Components needed")

**Features** : the servo is used to lift the tea bag in or out of the cup. A potentiometer allows to set the time of stirring. 
The pushbutton controls the beggining of the stirring cycle .When it stops the buzzer emits a beep. Each led is protected by a resistor. 
The whole circuit is powered by a 9v battery through the Vin pin (a power jack can be used as well). 

###Circuit : breadboard 
Start by testing your circuit on a breadboard in order to be sure that every component is working as it should be. 

<img width="49.5%" height="50%" src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/circuit_fritzing_bb.jpg"/>
<img width="49.5%" height="50%" src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/circuit_schematic.png"/>

Here's how the circuit works : 
* **Potentiometer**(RV1) : depending on the position of the axe, 0->5v is fed to the analog pin A5 of the Arduino. 
The pin will thus read a value between 0 and 1023 that we will programatically rebase on a [0 - 10] range corresponding 
to our 'stirring spectrum'. 
* **Servo motor**: used to lift the tea bag up and down. Servos are controlled by sending them a pulse of variable width. The control wire is used to send this pulse. The parameters for this pulse are that it has a minimum pulse, a maximum pulse, and a repetition rate.
The angle of the shaft is determined by the duration of a pulse that is applied to the control wire. This is why the 
servo must be connected to a pin that allows Pulse Width Modulation (PWM). 
* **Piezo buzzer**: indicates end of cycle. You're invited to mess with the code and add a nicer melody. Must be connected to a digital pin.
* **Pushbutton**: a **pull-up** design is used so that the input pin is always in a clear logical condition (ie: never floating). 
When the circuit is opened (button unpressed), D6 is low impedance and current flows from 5v to the input pin which thus reads HIGH. 
Inversely when the circuit is closed (button pressed), the current flows directly to the ground and d6 reads LOW. 

###Assemble frame
<img width="32%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/02_frame_parts.JPG"/>
<img width="32%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/frame_assembled.png"/>
<img width="32%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/frame_plans.png"/>

Assemble the frame and screw in the different components (buttons, servo and leds).

<img width="49.5%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/031_frame_add_components.JPG"/>
<img width="49.5%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/032_frame_add_components.JPG"/>

###Solder circuit
Next solder the different components. 

![Soldering](https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/040_solder_components.JPG "Solder components")

You'll probably want to start by soldering the passive elements and the wires on
the perfboard. Then solder the wires to the buttons, the led and the potentiometer already embedded to the frame. 


<img width="32%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/051_plug_arduino.JPG"/>
<img width="32%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/041_solder_components.JPG"/>
<img width="32%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/042_solder_components.JPG"/>

###Upload code
Finally you just need to plug in the Arduino and the servo. Connect the Arduino to a computer with the USB cable and upload the code found in the folder *arduino_code*.
Here is what happens inside that file : 
* We first define every relevant variables : the pin of the LEDs, servo, pushbutton and buzzer. We define some parameters like the relevant angles for our 'stirrer'.
* Setup() is the first function called when the Arduin boots up. We put the pins on the desired mode, turn on the power led to indicate that systems are up and running and 
we put the servo at the right position. 
* Loop() will be called undefinitly as long as the board doesn't reboot. It continously listens for the value coming from the potentiometer and transforms that value into milliseconds. 
The state of the pushbutton is also monitored. If it is pressed, the startStirring() function is invoked and the stirring process starts. The duration is taken from the last value taken from the 
potentiometer. Durring the stirring process, the green LED will be turned on as soon as the servo has reached its working position. Once the stirring cycle ends, the LED is turned off, 
the buzzer is triggered to play two identical notes and the servo comes back to a high position. Control comes back to the main loop. 


<img width="49.5%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/052_upload_code.JPG"/>
<img width="49.5%" height="50%"  src="https://raw.githubusercontent.com/wearhacks/courses/master/projects/automated-tea-stirrer/src/img/06_final_project.JPG"/>
Try and play with the potentiometer and the Serial console in order to match the angles with the corresponding time. Your project is ready, congratulations !


###Video of the completed project :
[![Watch](http://img.youtube.com/vi/GEQ1YadsMo0/0.jpg)](http://www.youtube.com/watch?v=GEQ1YadsMo0)
 	
