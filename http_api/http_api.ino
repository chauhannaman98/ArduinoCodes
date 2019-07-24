#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Techmirtz";
const char* password = "srmmmmmm";
const String URL = "http://jsonplaceholder.typicode.com/users/1";

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   WiFi.begin(ssid, password);
   
   Serial.print("Connecting. . .");
   while(WiFi.status() != WL_CONNECTED)   {
      delay(1000);
      Serial.print(" . ");
   }
   Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
   if(WiFi.status() == WL_CONNECTED)   {
       HTTPClient http;

       http.begin(URL);

       if(http.GET() > 0)   {
           String payload = http.getString();
           Serial.println(payload);
       }
       http.end();
   }
   delay(5000);
}
