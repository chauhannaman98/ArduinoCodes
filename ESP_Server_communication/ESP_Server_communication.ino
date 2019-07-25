#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>        // install v5.13.5

const char* ssid = "******";
const char* password = "*****";

/*Web server address to read/wite from*/
const char* URL = "http://arduinojson.org/example.json";

const int n = 2;    //number of variables
const int pin[2] = {3, 4};    //pins connected to relay

boolean Appln_State[2] = {true, true};

//15 sec for 1 & 10 second for 2
unsigned long Dx_ON[2] = {15000, 10000};    //duration time
unsigned long Ex_ON[2] = {0, 0};                    //elapsed time
//variables for elapsed time trigger
unsigned long Ex_Start[2] = {0, 0};   //stores time when variable is triggered

//flags
boolean rFlag[2] = {false, false};       //flag to  record of Ex_ON
boolean trigFlag[2] = {true, true};     //flag to trigger  Ex_ON

int address;
unsigned long start_time=0;
int min_count=0;

void setup() {
  
      Serial.begin(115200);
      EEPROM.begin(64);   // Initialising array of size 64 bytes in RAM to represent the 64 bytes in Flash as EEPROM

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
      
      //Reading saved data from EEPROM
      for(int i = 0; i<n; i++)  {
        pinMode(pin[i], OUTPUT);
        
         if(i==0)
            address = 0;
         if(i==1)
            address = 5;
        Ex_ON[i] = EEPROMRead(address);               //Reading elapsed time from EEPROM
        Dx_ON[i] = EEPROMRead(address+10);        //Reading duration time from EEPROM
        Appln_State[i] = EEPROMRead(address+20);       //Reading state from EEPROM
        Ex_Start[i] = EEPROMRead(address+30);       //Reading start time from EEPROM
      }
}

void loop() {
      
      for(int i = 0; i<n; i++)  {
          if(i==0)
            address = 0;
          if(i==1)
            address = 5;

          if(trigFlag[i]) {
            trigger(i);
          }

          //checking for starting appliances
          if(Ex_ON[i] < Dx_ON[i] && rFlag[i])  {
            record_Ex_ON(i);
          }

         //checking for stoping any appliance
         if(Ex_ON[i] >= Dx_ON[i]) {
              Serial.print("\n*****Calling stop function for ");
              Serial.print(i+1);
              Serial.println("*****");
              stop_Ex_ON(i);
         }
     }
} //loop


            /****------user-defined functions here-----****/
//function for recording elapsed time
void record_Ex_ON(int i) {

      unsigned long currentMillis = millis();
      Ex_ON[i] = currentMillis - Ex_Start[i];
      if(i==0)
        address = 0;        //saving Ex_ON of 1 on 0 location
      if(i==1)
        address = 5;     //saving Ex_ON of 2 on 5 location
      Appln_State[i] = true;
      EEPROMWrite(address, Ex_ON[i]);
      EEPROMWrite(address+20, Appln_State[i]);
      
      // Serial for debugging only
      Serial.print(" | Calling record function for ");
      Serial.print(i+1);
      Serial.print(" | E");
      Serial.print(i+1);
      Serial.print("_ON = ");
      Serial.println(Ex_ON[i]);
}

//function for stopping elapsed time
void stop_Ex_ON(int i)  {

      digitalWrite(pin[i], LOW);      // switch OFF the pin
      Appln_State[i] = false;
      EEPROMWrite(address+20, Appln_State[i]);
      Ex_ON[i] = 0;
      if(i==0)
          address = 0;        //saving Ex_ON of 1 on 0 location
      if(i==1)
          address = 5;     //saving Ex_ON of 2 on 5 location
      EEPROMWrite(address, Ex_ON[i]);
      Ex_Start[i] = 0;
      rFlag[i] = false;
      Serial.print("   STOPPED E");
      Serial.print(i+1);
      Serial.print("_ON = ");
      Serial.println(Ex_ON[i]);
}

//function to trigger
void trigger(int i) {

        Ex_Start[i] = millis();
        Appln_State[i] = true;
        if(Appln_State[i])  {
            digitalWrite(pin[i], HIGH);       //switch ON the pin
        }
        rFlag[i] = true;
        trigFlag[i] = false;
}

//function to write unsigned long value to EEPROM
void EEPROMWrite(int address, unsigned long value) {

    /* size of unsigned long is 32 bytes but each memory location in EEPROM
     * takes only 8 bytes and then rolls over. Thus, it is taken into 4 individual bytes
     * and then stored in consecutive memory locations.
     */
    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);       // using bitwise operator here for shifting through bits
    byte two = ((value >> 16) & 0xFF);
    byte one = ((value >> 24) & 0xFF);
    
    EEPROM.put(address, four);
    EEPROM.put(address + 1, three);
    EEPROM.put(address + 2, two);
    EEPROM.put(address + 3, one);
    EEPROM.commit();
}

//overidden function to write boolean value to EEPROM
void EEPROMWrite(int address, boolean value) {
    EEPROM.put(address, value);
    EEPROM.commit();
}

//function to read from EEPROM
unsigned long EEPROMRead(int address) {

      /* Reading individual bytes here from each memory location into 
       * different variables.
       */
      unsigned long four = EEPROM.read(address);
      unsigned long three = EEPROM.read(address + 1);
      unsigned long two = EEPROM.read(address + 2);
      unsigned long one = EEPROM.read(address + 3);
  
      return (
          /*Combining all the four read outputs for retrieving the saved value from EEPROM
          * It's reverse procedure of what is being done in EEPROMWrite().
          */
          ((four << 0) & 0xFF) + 
          ((three << 8) & 0xFFFF) + 
          ((two << 16) & 0xFFFFFF) + 
          ((one << 24) & 0xFFFFFFFF)
      );
}

// function to convert minutes recieved from server to milliseconds
// 1 min = 60 sec and 1 sec = 1000 millisec
// thus, 1 min = 60000 millis
unsigned long min_to_millis(int mins) {
      return (mins*60000);
}

// function to send HTTP request for getting the JSON data from the server
void startServer()   {
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
}
