unsigned long Dx_ON[2] = {15000, 10000};
unsigned long Ex_ON[2] = {0, 0};

boolean exFlag[2] = {true, true};

void setup() {
  
  Serial.begin(9600);
  
}

void loop() {

    //Starting elapsed time for both variables
    for(int i = 0; i<2; i++)  {
      
      if(Ex_ON[i] < Dx_ON[i] && exFlag[i] == true)  {
        record_Ex_ON(i);     
     }
   }

   //Checking stop condition for both variables
   for(int i = 0; i<2; i++)  {

     if(Ex_ON[i] >= Dx_ON[i]) {
        Serial.print("\n*****Calling stop function for ");
        Serial.print(i+1);
        Serial.println("*****");
        stop_Ex_ON(i);
     }
   }

   unsigned long currentMillis = millis();
   Serial.print("   |   Millis = ");
   Serial.println(currentMillis);
}



// user-defined functions here:
void record_Ex_ON(int i) {

    Ex_ON[i] = millis();
    Serial.print("   |   Calling record function for ");
    Serial.print(i+1);
    Serial.print("     E");
    Serial.print(i+1);
    Serial.print("_ON = ");
    Serial.print(Ex_ON[i]);
    
}

void stop_Ex_ON(int i)  {

  //save elapsedTime to EEPROM first
  //ENTER EEPROM CODE HERE:
  Ex_ON[i] = 0;
  exFlag[i] = false;
  Serial.println("     Stopped E");
  Serial.print(i+1);
  Serial.print("_ON = ");
  
}
