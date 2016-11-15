#ifndef UNIT_TEST

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Global.h"
#include "Operation.h"
struct Global global;
void setup()
{
  // Serial Start
  Serial.begin(9600);

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(VALVE_D8, OUTPUT);

  // initialize global struct
  global.readCnt = 0;
  global.irrigEnableCnt = 0;
  global.irrigDisableCnt = 0;
  global.enableIrrig = false;
  // global.tempChar = '';
  global.recevieContent = "";
  global.sensorReadValue = -1;
}

void loop()
{
  decode(readCommandFromSerial( global.recevieContent, global.tempChar ));
  cleanRecevieContent( global.recevieContent );
  // simplePeriodicIrrig();
}

#endif
