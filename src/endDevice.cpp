/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "SoftwareSerial.h"
#define EC5_A2 2  // 5cm depth
#define EC5_A1 1  // 10cm depth
#define EC5_A0 0  // 15cm depth
#define VALVE_D8 8 // electric valve
void setup()
{
  Serial.begin(9600);

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(VALVE_D8, OUTPUT);
}

void loop()
{

  // open valve for 15 sec
  digitalWrite(VALVE_D8, HIGH);
  delay(15000);
  digitalWrite(VALVE_D8, LOW);

  // wait for minutes
  delay(60000);

  float v0 = analogRead(EC5_A0)*(3.3/1023.0);
  float v1 = analogRead(EC5_A1)*(3.3/1023.0);
  float v2 = analogRead(EC5_A2)*(3.3/1023.0);
  Serial.print("ec5,a0,");
  Serial.print(v0);
  Serial.print(",");
  Serial.print("ec5,a1,");
  Serial.print(v1);
  Serial.print(",");
  Serial.print("ec5,a2,");
  Serial.println(v2);

}
