# Arduino-Car-Parking-Assintant

Click **[here](https://www.hackster.io/techmirtz/arduinomated-car-parking-with-voice-assistance-in-smartphone-c4d677)** to open the full project published on hackster.io

## Introduction

Make an assistant which tells you about how much to drive backwards without any collision through your smartphone by Arduino and 1Sheeld.

It's a problem to take the car in reverse and many time people bump it into other cars or garage wall. My dad often ask me to assist him while parking car. But, what if you are driving alone and there is no one to assist you? There comes the Arduinomated car parking assistant which will work on **1Sheeld+** and **Ultrasonic** distance sensor which will tell you about how much distance is there between your car and obstacle without seeing backwards with a **voice assistant**; means you don't have to look backward nor into a screen.

## What is OneSheeld?

1sheeld is a stackable Arduino UNO shield used by in projects which can substitute and many components and make the work easy for wireless connections between an smartphone and the Arduino using a single App available for Android and iOS both.

### Tech Specs:

- 1Sheeld+ uses a standard HM-10 Bluetooth low energy adapter (BLE 4.0)
- 7.37 MHz operating frequency
- Range up to 30 feet
- Communicates with Arduino using UART
- Supports iOS versions starting 9.0 and up.
- Supports Android versions starting 4.3 and up.

> Sketch uses 27104 bytes (10%) of program storage space. Maximum is 253952 bytes. Global variables use 2063 bytes (25%) of dynamic memory, leaving 6129 bytes for local variables. I would suggest you to use Mega or higher board. UNO don't have much memory! It can create problem in processing and execution even if you fill the memory of UNO up to the brink by reducing the code size.

> I am assuming that almost all the people know about the Ultrasonic Distance sensor.
