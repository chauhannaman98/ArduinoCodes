#include <EEPROM.h>

void setup()
{
  Serial.begin(9600);
}

/*
 function: writes data to EEPROM in little endian order
 params: bigData(int, data to be written),
      address(int, starting address)
*/
bool writeData(int bigData, int address)  {
  byte littleData;
  //masking bigData for 8-LSBs
  littleData = bigData & 0xFF;
  EEPROM.write(address, littleData);
  //right shift 8 bits for 8-MSBs
  littleData = (bigData >> 8);
  EEPROM.write(address+1, littleData);
  return true;
}

bool askChoice()  {
  bool flag = true;
  int ch;
  Serial.println("1) Write\n2) Read");
  Serial.print("Enter choice: ");
  while(Serial.available()==0)  {}
  ch = Serial.parseInt();
  switch(ch)  {
    case 1: //write_();
            break;
    case 2: //read_();
            break;
    default: Serial.println("Enter correct choice!");
             flag=false;
             break;
  }
  return flag;
}

void loop()
{
  int data, addr;
  bool flag = askChoice();
  while(!flag)  {
    flag = askChoice();
  }
  
  Serial.print("Enter data: ");
  while(Serial.available()==0) {}
  data = Serial.parseInt();
}
