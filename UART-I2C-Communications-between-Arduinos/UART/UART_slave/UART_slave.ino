// Include the Software Serial library
#include <SoftwareSerial.h>

// Define a Software Serial object and the used pins
SoftwareSerial softSerial(8, 9); // RX, TX

// LED Pin
int LED = 13;

void setup()  {
  softSerial.begin(9600); // Soft Serial
  pinMode(LED, OUTPUT); // Define LED pin mode
}

void loop() {
  // Check if there is anything in the soft Serial Buffer
  if (softSerial.available()) {
  // Read one value from the soft serial buffer and store it in the
  variable com
  int com = softSerial.read();
  // Act according to the value received
  if (com == 'x'){
  // Stop the LED
  digitalWrite(LED, LOW);
  }
  else if (com == 'a')  {
  // Start the LED
  digitalWrite(LED, HIGH);
    }
  }
}
