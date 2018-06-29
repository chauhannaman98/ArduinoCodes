/*
 * https://github.com/chauhannaman98/Heart-Rate-Monitor-on-ThingSpeak-IoT-Platform
 *
 * Testing_Code.ino
 *
 * Created: October 5,2017
 * Author : Naman Chauhan
 */ 

int heartPin = A1;//for analog input
//remember you put the switch towards 'A' not 'D' for analog input

void setup()  {
  Serial.begin(115200);
  //default is 9600, change after opening the serial plotter
 }

void loop()  {
  int heartValue = analogRead(heartPin);    //reading the analog value
  Serial.println(heartValue);   //printing the value tot the serial plotter
  delay(5);
  }
