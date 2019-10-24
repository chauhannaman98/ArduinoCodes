#define BLYNK_PRINT Serial
#include<BlynkSimpleEsp8266.h>
#include<ESP8266WiFi.h>
#include<Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels  = Adafruit_NeoPixel(10, 12);
char auth[]="oiQp3l6Zloh2NWSMmsHSvw-hJvEbTcG_";
char ssid[]="G Family";
char pass[]="fourgees";
void red()
{
   for(int i=0;i<10;i++)
{
  pixels.setPixelColor(i, pixels.Color(75,0,0));
  pixels.show();
}
}

void pink()
{
   for(int i=0;i<10;i++)
{
  pixels.setPixelColor(i, pixels.Color(100,0,50));
  pixels.show();
}
}
void blue()
{
  for(int i=0;i<10;i++)
    {
      
         pixels.setPixelColor(i, pixels.Color(0,0,75));
        pixels.show();
       // delay(500);
       delay(10);
    }
}
void green()
{
   for(int i=0;i<10;i++)
    {
      
         pixels.setPixelColor(i, pixels.Color(0,75,0));
        pixels.show();
        delay(10);
    }
    
}
void yellow()
{
  for(int i=0;i<10;i++)
    {
      
         pixels.setPixelColor(i, pixels.Color(75,75,0));
        pixels.show();
        delay(10);
    }
}
void purple()
{
   for(int i=0;i<10;i++)
    {
      
         pixels.setPixelColor(i, pixels.Color(50,25,75));
        pixels.show();
        //delay(5);
        delay(10);
    }
}
void party()
{
  for(int i=0;i<50;i++)
  {
     pink();
        blue();
     yellow();
       green();
      purple();
    }
  }
void off()
{
  for(int i=0;i<10;i++)
  {
    pixels.setPixelColor(i,pixels.Color(0,0,0));
  
pixels.show();  }
  
}
void clockwise()
{
  for(int i=0;i<10;i++)
  {
    pixels.setPixelColor(i,0,100,0);
    delay(500);
  }
  pixels.show();
}
void anticlockwise()
{
  for(int i=10;i>0;i--)
  {
    pixels.setPixelColor(i,100,0,0);
    delay(500);
  }
  pixels.show();
}

BLYNK_WRITE(V2)
{
  String recieved_value=param.asStr();

  Serial.print("Recieved value:");
  Serial.println(recieved_value);
  if(recieved_value=="blue")
  {
    blue();
  }
  
  else if(recieved_value=="red"){
    red();
  }
  else if(recieved_value=="green"){
    green();
  }
  else if(recieved_value=="yellow"){
    yellow();
  }
  else if(recieved_value=="pink"){
    pink();
  }
  else if(recieved_value=="purple"){
    purple();
  }
  else if(recieved_value=="dark"){
    off();
  }
  else if(recieved_value=="party")
  {
    party();
}
 else if(recieved_value=="clockwise")
  {
    clockwise();
}
 else if(recieved_value=="anticlockwise")
  {
    anticlockwise();
}
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);  
  pixels.begin();
   Serial.begin(115200);
   //pinMode(LDR,INPUT);
 

}

void loop() {
  // put your main code here, to un repeatedly:
  Blynk.run();
}
  
