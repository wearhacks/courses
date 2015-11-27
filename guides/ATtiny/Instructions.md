# Flashing the ATtiny85 with an Arduino Uno

## 1. Upload the Arduino ISP sketch to the Uno 
The sketch is included in the default examples of the Arduino IDE. It allows the Arduino to be used as a bridging device between the USB of the computer and the ATtiny chip.

To quote the [Arduino website on the subject](https://www.arduino.cc/en/Reference/SPI):
> Serial Peripheral Interface (SPI) is a synchronous serial data protocol used by microcontrollers for communicating with one or more peripheral devices quickly over short distances. It can also be used for communication between two microcontrollers. 

Navigate to **File**->**Examples**->**ArduinoISP**. 

<img width="100%" height="100%"  src="https://github.com/wearhacks/courses/blob/master/guides/ATtiny/img/ArduinoISP.png"/>

Upload the sketch to the Arduino Uno. It is now ready to be used as a bridge in order to **flash** the **firmware** to the ATtiny.

## 2. Download and install the ATtiny cores package
Theses files contain the parameters used by the IDE to compile and upload the sketches to the various chips or microcontrollers compatible. 

Several are already included, you can find them under **Tools**->**Board**. The ATtiny was unfortunately left out so we need to add it manually. 

### Install on Arduino IDE >= 1.6.4
The new version of the Arduino IDE introduces an easier method to add cores packages. 

- Navigate to **File**->**Preferences**. 
- Copy and paste this into the **Additional Boards Manager URLs** field: 
*https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json*
- Click ok
- Navigate to **Tools**->**Board**->**Boards Manager**. 
- Find the **attiny** in the list and click **install**. 

You can check in the boards tab if the ATtiny is listed. 

### Install on Arduino IDE 1.6, 1.5 and 1.0
Several versions of the cores are available. 

[Link for 1.6](https://github.com/damellis/attiny/archive/ide-1.6.x.zip)
[Link for 1.0](https://github.com/damellis/attiny/archive/ide-1.0.x.zip)
[Link for 1.5 and 1.0](https://code.google.com/p/arduino-tiny/)

In order to manually install a cores library, follow these steps:

- Download the version of your code that suits your IDE/requirements.
- Uncompress the zip file and locate the **attiny** folder. 
- Find the Arduino IDE **sketchbook folder** (the one that also contains the libraries). 
- Create a new subfolder called **/hardware** in the sketchbook folder in which you will copy the **attiny**.
- Restart the IDE. 

Once again, you can check in the boards tab if the ATtiny is listed (there should be a bunch of them). 

## 3. Connect the Uno to the ATtiny
The circuit connects the Arduino ISP pins (MISO, MOSI, SCK, SS) to their ATtiny counterparts. 


<img width="49.5%" height="50%"  src="https://cdn.sparkfun.com/assets/f/8/f/d/9/52713d5b757b7fc0658b4567.png"/>
<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/guides/ATtiny/img/ATtiny85-flash0_bb.png"/>


The connections go as follow: 

Arduino | ATtiny85
------------- | -------------
10  | RESET
11  | 0
12  | 1
13  | 2
GND  | GND
5V  | Vin

## 4. Set-up the clock rate at 8Mhz
The clock rate of the ATtiny out of the factory is 1Mhz but the internal oscillator can go up to 8Mhz (you'll need to add a crystal for more). 

- Select the **ATtiny85 board** with a frequency of **8Mhz** on the internal oscillator in the **board** tab.
- Select **Arduino as ISP** in **Tools**->**Programmer**.
- In the same **Tools** menu, click on **Burn bootloader**.

There you go. Your chip is now running 8 times faster!

## 4. Upload the famouse Blink sketch
It's always good to perform a very simple test. And what could be easier than blinking an LED?

<img width="49.5%" height="50%"  src="https://github.com/wearhacks/courses/blob/master/guides/ATtiny/img/ATtiny85-flash_bb.png"/>

- Grap any LED in your parts bin and connect it to pin 4 on the ATtiny through a resistor in serie. Choose a common value between 270Ohms to 1k. 
- Open the Blink sketch found in **Files**->**Examples**->**1.0 Basics**
- Change the LED pin number from **13** to **4**
- Watch amazed as the LED starts blinking
