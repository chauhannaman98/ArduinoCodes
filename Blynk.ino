#define BLYNK_PRINT Serial
#include<BlynkSimpleEsp8266.h>
#include<ESP8266WiFi.h>

char auth[] = "xxxxxxxxxxxxxxxxxxxxxxxxxx"; //blynk auth id

char ssid[] = "xxxxxxxxxx"; 		    //wifi ssid
char pass[] = "xxxxxxxxxx";		    //wifi password


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}
  

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
