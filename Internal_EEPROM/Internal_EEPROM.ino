#include <EEPROM.h>

int data, addr;

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

/*
 function: writes data to EEPROM in little endian order
 params: bigData(long, data to be written),
      address(int, starting address)
*/
bool writeData(long bigData, int address)  {
  byte littleData;
  int len = sizeof(bigData);
  int byteSize = 8;
  littleData = bigData & 0xFF;
  EEPROM.write(address, littleData);  //1st byte written
  for(int i = 1; i<len; i++)  {       //loops to write other bytes
    littleData = (bigData >> i*byteSize);
    EEPROM.write(address+i, littleData);
  }
  return true;
}

void write_() {
  Serial.print("Enter data: ");
  while(Serial.available()==0) {}
  data = Serial.parseInt();
  Serial.println(data);
  Serial.print("Enter the address: ");
  while(Serial.available()==0) {}
  addr = Serial.parseInt();
  Serial.println(addr);
  if(writeData(data, addr))  {
    Serial.print(data);
    Serial.print(" written successfully to address ");
    Serial.println(addr);
  }
}

bool askChoice()  {
  bool flag = true;
  int ch;
  Serial.println("1) Write\n2) Read");
  Serial.print("Enter choice: ");
  while(Serial.available()==0)  {}
  ch = Serial.parseInt();
  Serial.println(ch);
  switch(ch)  {
    case 1: write_();
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
  bool flag = false;
  while(!flag)  {
    flag = askChoice();
    Serial.println();
  }
}
