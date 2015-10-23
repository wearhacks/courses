# Getting started with the Particle Spark Core
Start by having a look at the [official getting started guide](https://docs.particle.io/guide/getting-started/start/core/). 

## 1. Create a new particle account. 
Navigate to this url to create a new account : [https://build.particle.io/signup](https://build.particle.io/signup).

## 2. Claim your device
The best way to set-up your device is to go through the mobile application. Between [iOS](https://itunes.apple.com/us/app/particle-build-photon-electron/id991459054?ls=1&mt=8) or [Android](https://play.google.com/store/apps/details?id=io.particle.android.app), you choose your flavor. 
Install the app on your smartphone, launch it and log in.
Press the **mode** pushbutton of the core for about 10 seconds. The light will starting blinking in blue. Keep the button pressed until the led start to blink 
wildly. You can then release it. The led should come back to a stable blue blink. Your device is now in setup mode. 
Press **add new device** on the app and select your spark core from the list. You'll then be asked to provide wifi credentials so that 
your core can get online. 
If the core you are using has already been claimed by another account, repeat the process described here. You'll be prompted with a question
asking you if you wish to transfer ownership. The answer is yes. 

## 3. Choose your IDE
In order to program the Spark core, two options are available. 
*** Online IDE
The online IDE is accessible at the the following address: [https://build.particle.io/](https://build.particle.io/). It allows you to program the core through your browser. It's the quickest way to get started, 
but it doesn't allow you to use a version control system on your files which can be a big drawback depending on your project. Plus the IDE is not as complete 
as a desktop version (no auto-completion, no custom shortcuts etc.).  

*** Particle dev
The Particle dev IDE is based on the open source project [Atom](). It is a full-blown IDE tweaked to work with the Particle's compiling and uploading system. You can download it at [this address](https://docs.particle.io/guide/tools-and-features/dev).

## 4. Importing libraries
The process is slightly different depending on the IDE you chose. 
*** Online IDE
Assuming that your have a sketch open, importing a library starts by clicking on the **Libraries** link. A list of every available library will appear in the side pannel. 
Use to search box to search for the library you want to import by providing its name (or part of it). 
Select the library that you need and click on **add to this sketch**. The import statement will be automatically added to your sketch. The format of the import statement 
is: *include "libraryName/libraryName.h"*.

*** Particle dev
In that case, you need to find the github repository corresponding to your library. It can be found through the online IDE: their's a small github icon next to the name of the library 
selected in the libraries view. Download the github repository and copy the content of the **firmware** folder at the root of your sketch directory. To import the library onto your 
sketch, use the following syntax: *include "libraryName.h"*. 

## 5. Uploading your code 
The process is similar on both IDEs. First navigate to your list of devices and select the one to which to send the code. Next click on the **flash** button. The code
is then sent to the cloud where it is compiled and sent back to your device through wiFi. The status led should start to blink pink, meaning that it is receiving the 
the new code (also called firmware). It will then reboot, blink green (meaning that it is reconnecting to the wiFi network) and start "breathing" a whitish glow (this is
when your code is starting to be executed). 

## Troubleshooting
In theory, everything should run well if you follow these guidelines. The reality can be quite different. Here are the most common problem encountered:
* The spark won't connect to the network, but I did enter the right credentials. It happens. The best thing to do is to reflash the device from the mobile app. 
Put your device in setup mode, select it on the app and press **re-flash tinker**. 
* The spark is connected but doesn't execute the new code I just flashed. In that case, try to reboot the spark by pressing the reset button. If it still doesn't work, 
proceed to a re-flash of tinker. But don't forget to check your code twice before going to such extents. Errors sometimes slide through the compiler. 
* The Particle dev IDE stays stuck on **compiling in the cloud** after flashing. Again, it happens. Just close the IDE, re-open it and try again. 
* The spark connect to the wiFi, starts running my code but quickly blinks red and tries to reconnect to the wiFi. This usually happens when the main loop is being blocked by a delay. 
Contrarly to an Arduino, the main loop must not be blocked because the core continously checks its connection to the network. If the loop is blocked, the background tasks of the 
core are also halted which can cause this kind of issues.

Finally, remember that the Spark core is before all an IoT device. It needs a stable connection to function correctly so if everything else fails it's worth to try to connect it to
a network for which the stability can be reliably assessed (like a smartphone access point with a good network coverage). 
