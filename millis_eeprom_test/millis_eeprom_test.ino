#include <EEPROM.h>

const int n = 2;    //number of variables

boolean Appln_State[2] = {true, true};

//15 sec for 1 & 10 second for 2
unsigned long Dx_ON[2] = {15000, 10000};    //duration time
unsigned long Ex_ON[2] = {0, 0};                    //elapsed time

//variables for elapsed time trigger
unsigned long Ex_Start[2] = {0, 0};   //stores time when variable is triggered

//flags
boolean rFlag[2] = {false, false};       //flag to  record of Ex_ON
boolean trigFlag[2] = {true, true};     //flag to trigger  Ex_ON

//int choice;
int address = 0;

void setup() {
  
    Serial.begin(9600);
    EEPROM.begin(64);
    /*Serial.println("1. Trigger 1");
    Serial.println("2. Trigger 2");
    Serial.print("Enter choice (1/2): ");*/

    //Reading elapsed time from EEPROM
    for(int i = 0; i<2; i++)  {
       if(i==0)
          address = 0;        //saving Ex_ON of 1 on 0 location
       if(i==1)
          address = 5;     //saving Ex_ON of 2 on 5 location
      Ex_ON[i] = EEPROMRead(address);
    }

    //Reading duration time from EEPROM
    for(int i = 0; i<2; i++)  {
       if(i==0)
          address = 10;        //saving Dx_ON of 1 on 10 location
       if(i==1)
          address = 15;     //saving Dx_ON of 2 on 15 location
      Dx_ON[i] = EEPROMRead(address);
    }
    
    //Reading state from EEPROM
    for(int i = 0; i<2; i++)  {
       if(i==0)
          address = 20;        //saving Ex_ON of 1 on 0 location
       if(i==1)
          address = 25;     //saving Ex_ON of 2 on 32 location
      Appln_State[i] = EEPROMRead(address);
    }
}

void loop() {

   //Taking input from user in serial monitor
  /*if (Serial.available() > 0)
     int choice = Serial.parseInt();
  
  switch(choice)  {

    case 1: if(trigFlag[0])
                    trigger(0);
                 else
                    Serial.println("Variable 1 is already triggered");
                 Serial.println("\nVariable 1 triggered for 15 seconds");
                 break;
                
    case 2: if(trigFlag[1])
                    trigger(1);
                 else
                    Serial.println("Variable 1 is already triggered");
                 Serial.println("\nVariable 2 triggered for 10 seconds");
                 break;
   }*/

   trigger(0);

   //unsigned long currentMillis = millis();
   //Serial.print("\nMillis = ");
   //Serial.println(millis());
  
    //Starting elapsed time for both variables
    for(int i = 0; i<n; i++)  {
      
      if(Ex_ON[i] < Dx_ON[i] && rFlag[i])  {
        record_Ex_ON(i);
     }
   }

   //Checking stop condition for both variables
   for(int i = 0; i<n; i++)  {

     if(Ex_ON[i] >= Dx_ON[i]) {
        Serial.print("\n*****Calling stop function for ");
        Serial.print(i+1);
        Serial.println("*****");
        stop_Ex_ON(i);
     }
   }
}//loop


// user-defined functions here:
//function for recording elapsed time
void record_Ex_ON(int i) {

    unsigned long currentMillis = millis();
    Ex_ON[i] = currentMillis - Ex_Start[i];
    if(i==0)
      address = 0;        //saving Ex_ON of 1 on 0 location
    if(i==1)
      address = 32;     //saving Ex_ON of 2 on 32 location
    EEPROMWrite(address, Ex_ON[i]);
    Serial.print(" | Calling record function for ");
    Serial.print(i+1);
    Serial.print(" | E");
    Serial.print(i+1);
    Serial.print("_ON = ");
    Serial.println(Ex_ON[i]);
}

//function for stopping elapsed time
void stop_Ex_ON(int i)  {

    Ex_ON[i] = 0;
    if(i==0)
      address = 0;        //saving Ex_ON of 1 on 0 location
    if(i==1)
      address = 32;     //saving Ex_ON of 2 on 32 location
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

        if(trigFlag[i]) {
        Ex_Start[i] = millis();
        trigFlag[i] = false;    //false to prevent trigger again
        rFlag[i] = true;
        }
}

//function to write to EEPROM
void EEPROMWrite(int address, unsigned long value) {

    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);
    byte two = ((value >> 16) & 0xFF);
    byte one = ((value >> 24) & 0xFF);
    
    EEPROM.write(address, four);
    EEPROM.write(address + 1, three);
    EEPROM.write(address + 2, two);
    EEPROM.write(address + 3, one);
}

//function to read from EEPROM
long EEPROMRead(long address) {
    long four = EEPROM.read(address);
    long three = EEPROM.read(address + 1);
    long two = EEPROM.read(address + 2);
    long one = EEPROM.read(address + 3);

    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
