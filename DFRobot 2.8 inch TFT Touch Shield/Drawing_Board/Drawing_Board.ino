#include<SPI.h>
#include<DmTftIli9341.h>
#include<DmTouch.h>
#include<utility/DmTouchCalibration.h>

DmTftIli9341 tft = DmTftIli9341(10,9);         //declaring tft pins and the tft object
DmTouch dmTouch = DmTouch(DmTouch::DM_TFT28_105);         //declaring touch object
DmTouchCalibration calibration = DmTouchCalibration(&tft, &dmTouch);

bool calibrated = false;
uint16_t x = 0;
uint16_t y = 0;

void setup()    {
    dmTouch.setCalibrationMatrix(calibration.getDefaultCalibrationData((int)DmTouch::DM_TFT28_105));
    tft.init();      //initialising the tft display
    dmTouch.init();      //initialising the touch
}

void loop()    {
    bool touched = true;
    if (dmTouch.isTouched())   {
        dmTouch.readTouchData(x, y, touched);   //getting location of the point touched
        tft.fillCircle(x, y, 2, BLUE);    //drawing a point of size 2px of blue color
        /******
         *Syntax : <object name>.fillCircle(x, y, <point size>, <COLOR IN CAPS>);
         * Note : Colors can also be in HEX form.
         *****/
    }
}
