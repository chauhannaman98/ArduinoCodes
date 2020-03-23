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

/*OVERLOADED FUNCTION
 function: writes data to EEPROM in little endian order
 params: bigData(float, data to be written),
     address(int, starting address)
*/
bool writeData(float bigData, int address)  {
  byte littleData;
  //masking bigData for 8-LSBs
  littleData = bigData & 0xFF;
  EEPROM.write(address++, littleData);  //writing 1st byte
  //right shift 8 bits for 8-MSBs
  littleData = (bigData >> 8);
  littleData = bigData & 0xFF;
  EEPROM.write(address++, littleData);  //writing 2nd byte
  littleData = (bigData >> 16);
  littleData = bigData & 0xFF;
  EEPROM.write(address++, littleData);  //writing 3rd byte
  littleData = (bigData >> 24);
  littleData = bigData & 0xFF;
  EEPROM.write(address, littleData);  //writing 4th byte
  return true;
}

void loop()
{
  int data, addr;
  Serial.print("Enter data: ");
  while(Seria.available()==0) {}
  Serial.parseInt(data);
}
