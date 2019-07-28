#include <SPI.h>
#include <SPIFlash.h>
#include <SD.h>
#include <DmTftIli9341.h>
#include <DmDrawBmpFromSdCard.h>
#define TFT_CS  10
#define SD_CS   8
#define F_CS    6
#define T_CS    4
 
DmTftIli9341 tft = DmTftIli9341(10, 9);
DmDrawBmpFromSdCard drawImage = DmDrawBmpFromSdCard();
 
void setup()    {
    // Set CS SPI pin HIGH for all SPI units, so they don't interfere
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);
    pinMode(T_CS, OUTPUT);
    digitalWrite(T_CS, HIGH);
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    pinMode(F_CS, OUTPUT);
    digitalWrite(F_CS, HIGH); 
    
    Serial.begin(9600);
    
    tft.init();
    SD.begin(SD_CS);
    drawImage.drawImage("logop565.bmp", tft, 0, 0);  //Display picture  
    tft.clearScreen();
    delay(2000);
    drawImage.drawImage("logop888.bmp", tft, 0, 0);
    }
    
void loop()   { 
    }
