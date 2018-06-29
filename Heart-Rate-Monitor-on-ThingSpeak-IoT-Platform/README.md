# Heart-Rate-Monitor-on-ThingSpeak-IoT-Platform

Click [here](https://www.hackster.io/techmirtz/heart-rate-monitor-on-thingspeak-iot-platform-4977a8) to open the hackster.io project

## Inroduction

Heart beat monitoring system using Arduino that will detect the heart beat using the DFRobot's heart rate sensor.

## Story

In this project we are going to make a **heart beat detection and monitoring system** using Arduino that will detect the heart beat using the pulse sensor and will show the readings in **BPM** (Beats Per Minute). It will also send the readings to **ThingSpeak server** using the **WiFi Bee module ESP8266**, so that heart beats can be monitored from anywhere in the world over the internet. ThingSpeak is a great source for displaying the data online and you can access the data from ThingSpeak at any time and at any place.

ThingSpeak provides very good tool for IoT based projects. By using ThingSpeak site, we can monitor our data and control our system over the Internet, using the Channels and webpages provided by ThingSpeak. ThingSpeak **‘Collects’** the data from the sensors, **‘Analyze and Visualize’** the data and **‘Acts’** by triggering a reaction. We have previously used ThingSpeak in Weather station project using Raspberry Pi and using Arduino, check them to learn more about ThingSpeak. Here we are briefly explaining to use ThingSpeak for this beat detection and monitoring system. The ThingSpeak service is operated by **MathWorks.**

## Note:

1. This product is NOT a professional medical device and should not be used to diagnose or treat medical conditions.

2. This sensor is designed to work when the user is not moving. If used while moving it will give inaccurate results.

- Upload the main code to the Arduino.
- Remember to change the API key, SSID (WiFi name) and PASS (Password) for your project.
- Use the heart rate sensor on your self again.
The ESP8266 will then communicate with the Arduino and will send the data to ThingSpeak. The ESP8266 will connect the network of your router that you will provide in the code and will send the data of the sensor online. This data on the ThingSpeak will be shown in a graph form showing the past readings too and can be accessed from anywhere over internet.
