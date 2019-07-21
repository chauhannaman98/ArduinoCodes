#include <EEPROM.h>

const int n = 2;    //number of variables
const int pin[2] = {3, 4};

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
  
      Serial.begin(9600);
      EEPROM.begin(64);   // Initialising array of size 64 bytes in RAM to represent the 64 bytes in Flash as EEPROM
      
      //Reading saved data from EEPROM
      for(int i = 0; i<n; i++)  {
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

      /*if (millis()-start_time>=6000)  {
          min_count+=1;
          start_time=millis();
      }*/
      
      for(int i = 0; i<n; i++)  {

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

//function to write to EEPROM
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
