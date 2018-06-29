/*
 * https://github.com/chauhannaman98/IR-Home-Automation
 *
 * IR_Automation_SrcCode.ino
 *
 * Created: Sept 17, 2017
 * Author : Naman Chauhan
 * 
 **************************************************************************************
 *
   Pin            Pin State:HIGH                      Pin State:LOW
   Digital 2      NC1 is disconnected with COM1       NC1 is connected with COM1 
                  NO1 is connected with COM1          NO1 is disconnected with COM1
   Digital 7      NC2 is disconnected with COM2       NC2 is connected with COM2
                  NO2 is connected with COM2          NO2 is disconnected with COM2
   Digital 8      NC3 is disconnected with COM3       NC3 is connected with COM3
                  NO3 is connected with COM3          NO3 is disconnected with COM3
   Digital 10     NC4 is disconnected with COM4       NC4 is connected with COM4
                  NO4 is connected with COM4          NO4 is disconnected with COM4
   -----------------------------------------------------------------------------------               
   
   IR Remote Codes(Can be different depending upon the remote being used):
   
   POWER :          16580863
   VOL+ :           16613503
   FUNC/STOP :      16597183
   PLAY BACKWARDS : 16589023
   PAUSE/STOP :     16621663
   PLAY FORWARD :   16605343
   ARROW DOWN :     16584943
   VOL- :           16617583
   ARROW UP :       16601263
   0 :              16593103
   EQ :             16625743
   ST/REPT :        16609423
   1 :              16582903
   2 :              16615543
   3 :              16599223
   4 :              16591063
   5 :              16623703
   6 :              16607383
   7 :              16586983
   8 :              16619623
   9 :              16603303
   -----------------------------------------------------------------------------------
   
   Download the IRremote library : http://image.dfrobot.com/image/data/DFR0107/IRremote.zip
   
 */

#include<IRremote.h>      //including infrared remote header file

#define power 16580863            //code for power button
#define button_1 16582903         //code for button 1
#define button_2 16615543         //code for button 2
#define button_3 16599223         //code for button 3
#define button_4 16591063         //code for button 4

int RECV_PIN = 11;        //IR reciever pin
IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned int value;

int relay1 = 2;
int relay2 = 7;
int relay3 = 8;
int relay4 = 10;
unsigned int relay_state[] = {0, 0, 0, 0, 0};

void setup()  {
  Serial.begin(9600);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  irrecv.enableIRIn();    //Start the IR reciever
}

void loop() {
  
  if (irrecv.decode(&results))  {
    Serial.println("code recieved");
    value = results.value;
    switch(value) {

      case power:   if (relay_state[1] == 1 && relay_state[2] == 1 && 
                    relay_state[3] == 1 && relay_state[4] == 1)  {                 
                    digitalWrite(relay1, LOW);                // turn it off when button is pressed
                    relay_state[1] = 0;                       // and set its state as off

                    digitalWrite(relay2, LOW);
                    relay_state[2] = 0;
                    
                    digitalWrite(relay3, LOW);
                    relay_state[3] = 0;
                    
                    digitalWrite(relay4, LOW);
                    relay_state[4] = 0;
                    }
                    
                    if (relay_state[1] == 0 && relay_state[2] == 0 && 
                       relay_state[3] == 0 && relay_state[4] == 0) {
                       digitalWrite(relay1, HIGH);               // turn it on when the button is pressed
                       relay_state[1] = 1;                       // and set its state as ON
        
                       digitalWrite(relay2, HIGH);  
                       relay_state[2] = 1;
                       
                       digitalWrite(relay3, HIGH);  
                       relay_state[3] = 1;
                       
                       digitalWrite(relay4, HIGH);  
                       relay_state[4] = 1;
                    }
                    break;


      case button_1:  if (relay_state[1] == 1)  {                 // if first app is ON then
                      digitalWrite(relay1, LOW);                // turn it off when button is pressed
                      relay_state[1] = 0;                       // and set its state as off
                      }
                      
                      if (relay_state[1] == 0) {
                        digitalWrite(relay1, HIGH);               // turn it on when the button is pressed
                        relay_state[1] = 1;                       // and set its state as ON
                      }
                      break;

                  
      case button_2:  if (relay_state[2] == 1)  {                 // if first app is ON then
                        digitalWrite(relay2, LOW);                // turn it off when button is pressed
                        relay_state[2] = 0;                       // and set its state as off
                      }
                      
                      if (relay_state[2] == 0) {
                        digitalWrite(relay2, HIGH);               // turn it on when the button is pressed
                        relay_state[2] = 1;                       // and set its state as ON
                      }
                      break;

      
      case button_3:  if (relay_state[3] == 1)  {                 // if first app is ON then
                      digitalWrite(relay3, LOW);                // turn it off when button is pressed
                      relay_state[3] = 0;                       // and set its state as off
                      }
                      
                      if (relay_state[3] == 0) {
                        digitalWrite(relay3, HIGH);               // turn it on when the button is pressed
                        relay_state[3] = 1;                       // and set its state as ON
                      }
                      break;

      
      case button_4:  if (relay_state[4] == 1)  {                 // if first app is ON then
                      digitalWrite(relay4, LOW);                // turn it off when button is pressed
                      relay_state[4] = 0;                       // and set its state as off
                      }
                      
                      if (relay_state[4] == 0) {
                      digitalWrite(relay4, HIGH);               // turn it on when the button is pressed
                      relay_state[4] = 1;                       // and set its state as ON
                      }
                      break;

       default: {
                  Serial.print("Key ");
                  Serial.print(value);
                  Serial.println(" not programmed");
                }
                break;
    }

    Serial.println(value);      
    irrecv.resume();
    Serial.println("Resumed the IR reciever");   
  }
}
