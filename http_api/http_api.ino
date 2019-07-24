#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>        // install v5.13.5

const char* ssid = "Techmirtz";
const char* password = "srmmmmmm";

/*Web server address to read/wite from*/
const char* URL = "http://arduinojson.org/example.json";

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
              const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
              DynamicJsonBuffer jsonBuffer(capacity);
            
             // Parse JSON object
              JsonObject& root = jsonBuffer.parseObject(payload);
              if (!root.success()) {
                    Serial.println(F("Parsing failed!"));
                    return;
              }
            
      // Decode JSON/Extract values
      Serial.println("");
      Serial.println(F("Response: "));
      Serial.println(root["sensor"].as<char*>());
      Serial.println(root["time"].as<char*>());
      Serial.println(root["data"][0].as<char*>());
      Serial.println(root["data"][1].as<char*>());
      }
      else      {
        Serial.println("Error in response");
      }
    
      http.end();  //Close connection
      
      delay(5000);  //GET Data at every 5 seconds
}
