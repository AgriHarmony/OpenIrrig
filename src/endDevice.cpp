/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "SoftwareSerial.h"
#define ec5_a2 2
#define ec5_a1 1
#define ec5_a0 0
void setup()
{
  Serial.begin(9600);

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{


   // wait for a second
  delay(1000);

  float v0 = analogRead(ec5_a0)*(3.3/1023.0);
  float v1 = analogRead(ec5_a1)*(3.3/1023.0);
  float v2 = analogRead(ec5_a2)*(3.3/1023.0);
  Serial.print("ec5,a0,");
  Serial.print(v0);
  Serial.print(",");
  Serial.print("ec5,a1,");
  Serial.print(v1);
  Serial.print(",");
  Serial.print("ec5,a2,");
  Serial.println(v2);

}
