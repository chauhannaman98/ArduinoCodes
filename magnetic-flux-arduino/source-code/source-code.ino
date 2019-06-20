/* magnetic-flux-measuring-using-arduino-and-hall-sensor
 * by - Naman Chauhan
 * 
 * Pin connections:
 * Hall sensor to Arduino -
 * 1/Supply to VCC(+5V)
 * 2/Ground to GND
 * 3/Output to A0
 * 
 * LCD to Arduino
 * PIN1 or VSS to ground
 * PIN2 or VDD or VCC to +5v power
 * PIN3 or VEE to ground (gives maximum contrast best for a beginner)
 * PIN4 or RS (Register Selection) to PIN8 of ARDUINO UNO
 * PIN5 or RW (Read/Write) to ground (puts LCD in read mode eases the communication for user)
 * PIN6 or E (Enable) to PIN9 of ARDUINO UNO
 * PIN11 or D4 to PIN10 of ARDUINO UNO
 * PIN12 or D5 to PIN11 of ARDUINO UNO
 * PIN13 or D6 to PIN12 of ARDUINO UNO
 * PIN14 or D7 to PIN13 of ARDUINO UNO
 * 
 * Note: I have commented out the commands using LCD and only using only the one which are
 * required for the serial communication on serial monitor. You can comment out the commands
 * as per your need.
 */

/*
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);    
// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN
*/

char ADCSHOW[5];    
//initializing a character of size 5 for showing the ADC result

void setup()  {
  // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  }

void loop() {
  /*lcd.print("FluxDensity");
  lcd.setCursor(0, 1);    //move to second line
  lcd.print("(in Gauss):");   // showing units*/
  Serial.print("Flux Density (in Gauss): ");
  String ADCVALUE = String((analogRead(A0)-515)/3.76);
 
  /* Now since the default reference if 5V and resolution is 10-bit 
   * so for every 5/1024 = 5mV, we get one increment is count, 
   * The sensor provides increment voltage of 1.3V for every 1Gauss increment if field.
   * So we need to divide ADC value by 3.76 for getting the gauss value, 
   * now the 0 gauss output of sensor is 2.5V so we need to subtract that first. 
   * To hold a 0V read at 0 Gauss field. */

  // Convert the reading to a char array
  ADCVALUE.toCharArray(ADCSHOW, 5);
  /*lcd.print(ADCSHOW);//showing the field strength value
  lcd.print("G   ");
  lcd.setCursor(0, 0);// set the cursor to column 0, line 0*/
  Serial.print(ADCSHOW);
  Serial.println("G");
  Serial.println();
  delay(1000);
  }
