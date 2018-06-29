# Using-4-4-Keypad-With-Arduino

Click **[here](https://www.hackster.io/techmirtz/using-4x4-keypad-with-arduino-2d22e9)** to open the hackster.io projects.
For further help, you can go to this **[link](https://www.tinkercad.com/things/8iDg0ZuguN8-epic-jofo-inari)** which will run the simulator made by me on Tinkercad.com for more easy understanding.

## Introduction

Keypads are used in all types of devices, including cell phones, fax machines, microwaves, ovens, door locks, etc. Learn how to use them with Arduinos.

So know how to connect a keypad to a microcontroller such as an Arduino is very valuable for building many different types of commercial products.

At the end, when all is connected properly and programmed, when a key is pressed, it shows up at the Serial Monitor on your computer. Whenever you press a key, it shows up on the Serial Monitor. But for now, for simplicity purposes, we start at simply showing the key pressed on the computer.

For this project, the type of keypad we will use is a matrix keypad. This is a keypad that follows an encoding scheme that allows it to have much less output pins than there are keys. For example, the matrix keypad we are using has **16 keys (0-9, A-D, *, #), yet only 8 output pins.** With a linear keypad, there would have to be 17 output pins (one for each key and a ground pin) in order to work. The matrix encoding scheme allows for less output pins and thus much less connections that have to be made for the keypad to work. In this way, they are more efficient than linear keypads, being that they have less wiring.

