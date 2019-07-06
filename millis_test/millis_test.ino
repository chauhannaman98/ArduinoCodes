const int n = 2;    //number of variables

//15 sec for 1 & 10 second for 2
unsigned long Dx_ON[2] = {15000, 10000};
unsigned long Ex_ON[2] = {0, 0};

//variables for elapsed time trigger
unsigned long Ex_Start[2] = {0, 0};   //stores time when variable is triggered

//flags
boolean rFlag[2] = {false, false};       //flag to  record of Ex_ON
boolean trigFlag[2] = {true, true};     //flag to trigger  Ex_ON

int choice;

void setup() {
  
    Serial.begin(9600);
    Serial.println("1. Trigger 1");
    Serial.println("2. Trigger 2");
    Serial.print("Enter choice (1/2): ");
}

void loop() {

   //Taking input from user in serial monitor
  if (Serial.available() > 0)
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
   }

   //trigger(0);

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

   //Serial.println();
}


// user-defined functions here:
//function for recording elapsed time
void record_Ex_ON(int i) {

    unsigned long currentMillis = millis();
    Ex_ON[i] = currentMillis - Ex_Start[i];
    Serial.print(" | Calling record function for ");
    Serial.print(i+1);
    Serial.print(" | E");
    Serial.print(i+1);
    Serial.print("_ON = ");
    Serial.println(Ex_ON[i]);
}


//function for stopping elapsed time
void stop_Ex_ON(int i)  {

    //save elapsedTime to EEPROM first
    //ENTER EEPROM CODE HERE:
    Ex_ON[i] = 0;
    Ex_Start[i] = 0;
    rFlag[i] = false;
    Serial.print("   STOPPED E");
    Serial.print(i+1);
    Serial.print("_ON = ");
    Serial.println(Ex_ON[i]);
}

void trigger(int i) {

        if(trigFlag[i]) {
        Ex_Start[i] = millis();
        trigFlag[i] = false;    //false to prevent trigger again
        rFlag[i] = true;
        }
}
