#Instructions

##Objective

To create a platform that allows users to draw a circuit with hand gestures
Tools used: Unity Game Engine, Leap Motion

## Framework

Leap Motion can recognize four gestures:

..1. Circle — A single finger tracing a circle.
..2. Swipe — A long, linear movement of a finger.
..3. Key Tap — A tapping movement by a finger as if tapping a keyboard key.
..4. Screen Tap — A tapping movement by the finger as if tapping a vertical computer screen

In our project, we wanted to allow users to draw a circuit in midair. We start with four basic circuit elements, including:

1. Voltage source -- which is recognized by swipe gesture
2. Inductor -- which is recognized by circle gesture
3. Capacitor -- which is recognized by key tap
4. Resistor -- which is recognized by screen tap

The software can be broken down into multiple parts

1. Receive hand motion from user through Leap Motion to acquire:
.. The position of the hand in air, and
.. The gesture of the hand

By knowing the position of the hand, the software would know **WHERE to place a certain component