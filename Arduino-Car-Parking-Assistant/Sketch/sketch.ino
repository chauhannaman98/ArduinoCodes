/*
 * https://github.com/chauhannaman98/Arduino-Car-Parking-Assistant
 *
 * Source_Code.ino
 *
 * August 18, 2017 © GPL3+
 * Author : Naman Chauhan
 * 
 ********************************************************************************
 *  
 * This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
 * distance to the closest object in range. To do this, it sends a pulse
 * to the sensor to initiate a reading, then listens for a pulse 
 * to return.  The length of the returning pulse is proportional to 
 * the distance of the object from the sensor.
 *   
 * The circuit:
 * * VCC connection of the sensor attached to +5V
 * * GND connection of the sensor attached to ground
 * * TRIG connection of the sensor attached to digital pin 13
 * * ECHO connection of the sensor attached to digital pin 11
    
********************************************************************************/

#include <OneSheeld.h>

#define CUSTOM_SETTINGS
#define INCLUDE_TEXT_TO_SPEECH_SHIELD

char charValue[4];  //charVal variable stores the words which are to be spoken


void setup() 
{
  OneSheeld.begin();    //starts the 1Sheeld
}

void loop() 
{
  int trigPin = 13;     //trigger pin connected to 
  int echoPin = 11;
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  long duration, cm;
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
  
  // convert the time into a distance
  cm = duration / 29 / 2;

  dtostrf(cm, 4, 1, charValue);
  if (cm < 70)
    {
      TextToSpeech.say("Stop! Your are too close! Distance is ");
      delay(3500);
      TextToSpeech.say(charValue);
      delay(1300);
    }
  else if (cm > 70 && cm < 170)
    {
      TextToSpeech.say("Keep it slow! Distance is ");
      delay(3500);
      TextToSpeech.say(charValue);
      delay(1300);
    }
  else if (cm > 170)
    {
      TextToSpeech.say("Distance is ");
      delay(1500);
      TextToSpeech.say(charValue);
      delay(1300);
    }
}
