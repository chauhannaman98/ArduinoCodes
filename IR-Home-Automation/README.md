# IR-Home-Automation

Click **[here](https://www.hackster.io/techmirtz/ir-home-automation-on-dfrobot-s-relay-shield-7b9e34)** to view full project on hackster.io

## Introduction

Everyone wants a remote to control all the appliances in your home. Some companies are introducing wireless controllers for various appliances but they are costly and you have to upgrade the existing for additional cost. So, what about making your own home automation system to control up to 4 appliances.

## Story

### High Voltage VS Low Voltage
We all know that the appliances work on 110 V (USA) and 220 V (Asia) depending upon the region. But, the Arduino we are using is working on just 5 V. If we connect it directly to the mains supply to control the appliances just like controlling the LEDs, the board or the microcontroller will get burned. So, we use 5 V relay which works as an interface between the two voltage supplies. A signal is sent to relay by Arduino and relay switches on the circuit of the appliance.

### Wireless Transmission of Data

We know that how will we switch the supply on but we need to send the signal from an IR remote to the receiver with Arduino. So, we can use any generic IR remote controller available in market. But, every remote controller comes with different codes for their buttons which they send it through IR LED. So, we need to find those codes for a random IR remote controller we are using.

For that, please click **[here](https://www.hackster.io/techduino/finding-the-ir-codes-of-any-ir-remote-using-arduino-c7a852)** for another project of mine on Hackster.io.
