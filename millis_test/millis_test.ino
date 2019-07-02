const int ledPin = LED_BUILTIN;

//taking duration of 30 sec = 30000 ms
unsigned long D1_ON = 30000;  
unsigned long E1_ON = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  
  unsigned long currentMillis = millis();
  Serial.print("Millis: ");
  Serial.print(currentMillis);
  Serial.print("   D1_ON: ");
  Serial.print(D1_ON);
  Serial.print("   E1_ON: ");
  Serial.println(E1_ON);
  
  /*Case 1:
  * When current time is less than duration,
  * add time to elapsed time and
  * print on the serial monitor
  * Keep led pin ON
  */
  if(currentMillis <= D1_ON)  {
    E1_ON = currentMillis;
    digitalWrite(ledPin, LOW);
  }

  /*Case 2:
  * When current time is more than or equal to duration,
  * don't add time to elapsed time and
  * print on the serial monitor
  */
  if(currentMillis > D1_ON) {
    //Duration completed!LED switchedd OFF
    digitalWrite(ledPin, HIGH);
  }

}
