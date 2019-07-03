unsigned long Dx_ON= 15000;
unsigned long Ex_ON= 0;

boolean exFlag = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    

    if(Ex_ON < Dx_ON && exFlag == true){
      
      record_Ex_ON(exFlag);
      Serial.print("     E1_ON = ");
      Serial.print(Ex_ON);
      Serial.print("     D1_ON: ");
      Serial.println(Dx_ON);
    
    }
    
    if(Ex_ON >= Dx_ON) {
      Serial.print("Calling stop function");
      stop_Ex_ON();
  }
}

void record_Ex_ON(boolean flag) {

    Ex_ON = millis();
    Serial.print("Calling record function");

}

void stop_Ex_ON()  {

  //save elapsedTime to EEPROM first
  //ENTER EEPROM CODE HERE:
  Ex_ON = 0;
  exFlag = false;
  Serial.println("     Stopped E1_ON");
  
}
