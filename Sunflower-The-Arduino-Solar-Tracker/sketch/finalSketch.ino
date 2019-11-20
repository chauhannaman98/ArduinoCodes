/*
 * https://github.com/chauhannaman98/Sunflower-The-Arduino-Solar-Tracker
 *
 * Source_Code.ino
 *
 * Nov 16, 2017 © GPL3+
 * Author : Naman Chauhan
 */

#include <Servo.h>
#include <LowPower.h>

Servo servohori;
int servoh = 0;
int servohlimithigh = 180;
int servohlimitlow = 0;

Servo servoverti;
int servov = 0;
int servovlimithigh = 180;
int servovlimitlow = 0;

//Assigning LDRs variables
int ldrtopl = 0;
int ldrtopr = 1;
int ldrbotr = 2;
int ldrbotl = 3;

void setup() {
  servohori.attach(10);
  servohori.write(0);
  servoverti.attach(9);
  servoverti.write(0);
}

void loop() {
  /* code */
  servoh = servohori.read();
  servov = servoverti.read();

  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

  if (avgtop < avgbot)  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) {
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop) {
          servoverti.write(servov -1);
          if (servov < servovLimitLow)  {
            servov = servovLimitLow;
          }
       delay(10);
       }
       else {
          servoverti.write(servov);
       }

  if (avgleft > avgright) {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh) {
      servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)  {
      servoh = servohLimitLow;
    }
  delay(10);
  }
  else  {
    servohori.write(servoh);
  }
  
  delay(50)
  
  for(int i=0; i<23; i++) { // looping sleep of 8 seconds 23 times.
    // 8 x 23 = 3 minutes approx
  LowPower.idle(SLEEP_2S, ADC_OFF, BOD_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);    // Goes to sleep for 8 seconds
  }
  
}
