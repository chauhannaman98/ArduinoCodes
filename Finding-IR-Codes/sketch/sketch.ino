/*
 * https://github.com/chauhannaman98
 *
 * sketch.ino
 *
 * July 25, 2018 © GPL3+
 * Author : Naman Chauhan
 * /

#include <IRremote.h>      //including infrared remote header file

int RECV_PIN = 11;        // the pin where you connect the output pin of IR sensor 
IRrecv irrecv(RECV_PIN);
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}
 
void loop() 
{
  if (irrecv.decode(&results)) 
  	{
    int value = results.value;
    Serial.println(" ");
    Serial.print("Code: ");
    Serial.println(results.value); //prints the value a a button press
    Serial.println(" ");
    irrecv.resume();       				// Receive the next value
    Serial.println("*****************");
  		}
}
