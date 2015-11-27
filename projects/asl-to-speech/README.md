# Asl-to-Speech

Asl-to-Speech is a wearable technology that translates American Sign Language (ASL) into speech. The goal of this project is to help people to facilitate communication using sign language. This project is able to translate numbers from 1 to 5. The code offers flexibility to add more numbers and letters if the user wishes to.

## How it works

The [Leap Motion Controller](https://www.leapmotion.com/) uses infrared cameras to track the movement of your hands and fingers. In this project, hand gestures are picked up by the Leap Motion and are translated into text. The text is then translated into speech by Nuance's speech platform.

This project also has the option to use the [Myo gesture control armband](https://myo.com) to translate arm gestures into speech. This hardware reads the muscle activity in your forearm and gives you touch-free control of technology with hand gestures and motion.

## Demo

Click to watch a short video demo:

[![Demo video](https://i.ytimg.com/vi_webp/cIiL2D15OzA/mqdefault.webp)](https://www.youtube.com/watch?v=cIiL2D15OzA)

## Components

### Windows Machine (For now)

#### Hardware Requirements

* [Leap Motion Controller](https://www.leapmotion.com/)
* [Myo gesture control armband](https://myo.com)

#### Software Requirements

* [Python 2.7.10](https://www.python.org/downloads/)
* [Python 3.5.0](https://www.python.org/downloads/)
* [Leap Motion Installer & SDK](https://developer.leapmotion.com/downloads/skeletal-beta?platform=windows&version=2.3.1.31549)
* [Myo Client and SDK](https://developer.thalmic.com/downloads)
* [Nuance's Text-to-Speech API](https://developer.nuance.com/public/index.php?task=account)

#### Walkthrough

1. Installing Python 2.7.10 and Python 3.5.10
2. Set up Nuance's Text-to-Speech API
3. Installing Leap Motion Installer & SDK
4. Installing Myo Client and SDK
5. Set up our project

#### Python 2.7.10 and Python 3.5.1

* Go to the link https://www.python.org/downloads/ 
* Download Python **2.7.10** installer and install
* Download Python **3.5.0** installer and install
* Press *Start** and click on **Control Panel**
* Click on **System and Security** then **System**
* Click on **Advanced system settings**
* Click on **Environment Variables** in the **Advanced** tab
You should see this at this point
![Alt](http://github.com/imbaky/Asl-to-Speech/blob/tutorial/img/env-var.png)
* Click on the variable **Path** then click on **Edit**
* Add at the end of the **Variable value** a **;** if it does not have one
* Add **C:\Python27;C:\Python27\Scripts;C:\Python35;C:\Python35\Scripts;** after the **;**
![Alt](http://github.com/imbaky/Asl-to-Speech/blob/tutorial/img/edit-env-var.png)

Make sure the paths **C:\Python27**, **C:\Python27\Scripts**, **C:\Python35**, **C:\Python35\Scripts** exist on your computer

At this point, you should be able to run **py**, **py -3**, **pip2** and **pip3** on command prompt (click on **Start**, search for **cmd** and click on it)

```
  py -V
```

```
  py -3 -V
```

```
  pip2 -V
```

```
  pip3 -V
```

#### Nuance's Text-to-Speech API

* Sign up a developper account on https://developer.nuance.com/public/index.php?task=home
* Click on **my account**
* Click on **Sandbox Credentials**
* Copy the ID from the **ANDROID section** and save it somewhere on your computer. We will need it later. The ID look something like this: "ABCDEFG_youremail_email_com_20151111002244"
* Copy the **HTTP Client Applications** key from the same page also save it somewhere on your computer. The app key looks something like this: c7db49a73431f7b33kf408abc4eba7062c339f37bd66ee2d7a3a3109fede0dc6b9566ded8865a0ba4b396510240d165040b688fd1c762b96b15c9faf3aac75f3

#### Leap Motion Installer & SDK

* Go to [Leap Motion](https://developer.leapmotion.com/downloads/skeletal-beta?platform=windows&version=2.3.1.31549)'s website and install the **SDK**.
* Connect Leap Motion on your computer
* You will be able to use the program **Leap Motion Visualizer** to visualize your hand(s) on the computer
You can now start to practice **American Sign Language** and see it on your computer screen

![Alt](https://camo.githubusercontent.com/d9b0397d4b086b39ca1e528495359f3f4a4a164d/687474703a2f2f7777772e6c6966657072696e742e636f6d2f61736c3130312f66696e6765727370656c6c696e672f696d616765732f61626331323830783936302e706e67)

At this point, you should be able to play with the Leap Motion on your computer

![Alt](http://github.com/imbaky/Asl-to-Speech/blob/tutorial/img/visualizer-five.jpg)

#### Myo Client and SDK

* Go to [Myo](https://developer.thalmic.com/downloads)'s website and install the **Myo Connect** and **SDK**.
* Extract the **Myo SDK** on your the same location where the folder of both versions of Python are located  (usually looks like **C:\**)
* Add the path of the **Myo SDK** in your environment variables the same way you did for setting up python (check above)
The path of the **Myo SDK** should look similar to **C:\myo-sdk-win-0.9.0\bin**
* Download the [myo-python](https://github.com/NiklasRosenstein/myo-python/archive/master.zip) 
* Extract the **master.zip** on your desktop
* In the command prompt, go in the directory of myo-python/

  ```
    cd myo-python
  ```
* Add the path of the myo-python in your environment variables
* Run setup.py

  ```
    py setup.py install
  ```
* Install requirements.txt 

  ```
    pip install -r requirements.txt
  ```

At this point your myo should work and you will be able to run the sample code in the examples folder

* From myo-python, you can go to the examples directory and run the sample code

  ```
    cd examples
  ```
  
  ```
    py hello_myo.py
  ```
  
  ```
    py feed_myo.py
  ```

#### Setting Up the project 

* Download this [project](https://github.com/imbaky/Asl-to-Speech/archive/master.zip)
* Extract on **Desktop**
* Open command prompt (Click on **Start**, search for "**cmd**" and click on it)
* Write this command on command prompt

  ```
    cd Desktop\Asl-to-Speech
  ```
* Write this command on command prompt

  ```
    pip install -r pip_requirements.txt
  ```
  
  It is normal if you get the following error: 
  ```
    Command "python setup.py egg_info" failed with error code 1 in c:\users\[username]\appdata\local\temp\pip-build-syvzsr\aiohttp"
  ```
  
* Write this command on command prompt

  ```
    pip3 install -r pip_requirements.txt
  ```

* Write this command on command prompt to open notepad

  ```
    notepad
  ```

* Paste the following inside notepad 

  ```
    {
       "app_id": "",
       "app_key": ""
    }  
  ```

* Add the app **ID** and **key** inside the double quotes ("") that you saved before

* Press **ctrl** + **s**

* Change the **File name** "\*.txt" to **creds.json** in the Asl-to-Speech/src directory (src folder)

* Change the **Save as type** "Text Document(\*.txt)" to **All Files**

* In the command prompt, go into the src folder by writing 

  ```
    cd src
  ```

* You can now test the speech module (Make sure your speaker is turned on)

  ```
    py -3 tts.py creds.json "Hello, how are you?" output.pcm
  ```

If you hear "Hello, how are you?" then it is working

At this point, you should be able to run **tts.py** without a problem

With the **Leap Motion SDK** and the speech module all set up, you will be able to try our **SignListener.py**

* In the command prompt, write

  ```
    py SignListener.py
  ```
  
You should see 

  ![Alt](http://github.com/imbaky/Asl-to-Speech/blob/tutorial/img/cmd-signlistener.jpg)

The **SignListener.py** includes the sign detection of the numbers from 0 to 9. The user should put the **Leap Motion** on a flat surface, then perform sign gestures in front of the computer screen. It is recommended to use the **Leap Motion Diagnostic Visualizer** to see how the computer detects the user's hand.

  ![Alt](http://github.com/imbaky/Asl-to-Speech/blob/tutorial/img/cmd-visualizer-signlistener.jpg)
  
With the **Leap Motion SDK**, the **Myo SDK** and the speech module set up, you will be able to try our **LeapMyo.py**

* In the command prompt, write

  ```
    py LeapMyo.py
  ```

To enable **Myo** sign detection, the user has to make a fist gesture as such

  ![Alt](http://github.com/imbaky/Asl-to-Speech/blob/tutorial/img/cmd-visualizer-leapmyo.jpg)
  
