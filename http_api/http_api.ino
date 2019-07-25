#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>        // install v5.13.5

const char* ssid = "Techmirtz";
const char* password = "srmmmmmm";

/*Web server address to read/wite from*/
const char* URL = "https://api.jsonbin.io/b/5d39f39ecf54f14fc94df8dc";

void setup() {
      Serial.begin(115200);
      delay(10);
      Serial.println();
      
      Serial.print("Connecting to ");
      Serial.println(ssid);
    
      WiFi.begin(ssid, password);
    
      while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
      }
    
      Serial.println("");
      Serial.print("WiFi connected to: ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());          //You can get IP address assigned to ESP
}

void loop() {
      HTTPClient http;    //Declare object of class HTTPClient
    
      Serial.print("API URL: ");
      Serial.println(URL);
      
      http.begin(URL);     //Specify request destination
      
      int httpCode = http.GET();            //Send the request
      String payload = http.getString();    //Get the response payload from server
    
      Serial.print("Response Code:"); //200 is OK
      Serial.println(httpCode);   //Print HTTP return code
    
      Serial.print("Data from Server:");
      Serial.println(payload);    //Print request response payload
      
      if(httpCode == 200)      {
              // Allocate JsonBuffer
              // Use https://www.arduinojson.org/assistant to compute the capacity.
              const size_t capacity = JSON_OBJECT_SIZE(4) + 71;
              DynamicJsonBuffer jsonBuffer(capacity);
            
             // Parse JSON object
              JsonObject& root = jsonBuffer.parseObject(payload);
              if (!root.success()) {
                    Serial.println(F("Parsing failed!"));
                    return;
              }
     
      // Decode JSON/Extract values
      const boolean State1 = root["Appln1_State"];
      const boolean State2 = root["Appln2_State"];
      unsigned long D1_ON = root["D1_ON"];
      unsigned long D2_ON = root["D2_ON"];

      // Print extracted values to serial monitor
      Serial.println("");
      Serial.println("Response: ");
      Serial.print("Appln1_State = ");
      Serial.println(State1);
      Serial.print("Appln2_State = ");
      Serial.println(State2);
      Serial.print("D1_ON = ");
      Serial.println(D1_ON);
      Serial.print("D2_ON = ");
      Serial.println(D2_ON);
      }
      else      {
        Serial.println("Error in response");
      }
    
      http.end();  //Close connection
      
      delay(30000);  //GET Data at every 5 seconds
}
