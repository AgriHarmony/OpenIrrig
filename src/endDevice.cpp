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

#define SKIP_NUM 5 // skipping first 5 reading data due to sensor starting
#define IRRIG_TIME_CNT 10
#define STOP_IRRIG_TIME_CNT 50
int readCnt = 0;
int irrigEnableCnt = 0;
int irrigDisableCnt = 0;
bool enableIrrig = true;
//
// Function Declaration
//

// ===========================
void readSensors(bool enableIrrig, int irrigEnableCnt, int irrigDisableCnt);
/* Read all the EC-5 Sensor data */
// ===========================

// ===========================
void simplePeriodicIrrig();
/* the old version of periodic irrigation implementation */
// ===========================

// ===========================
void slaveRead();
/* arduino as a slave listen to the master cmd */
// ===========================

void setup()
{
  // Serial Start
  Serial.begin(9600);

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(VALVE_D8, OUTPUT);
}

void loop()
{
  simplePeriodicIrrig();
}

//
//  Function Implementation
//
void simplePeriodicIrrig(){

  if (readCnt > SKIP_NUM)
  {

      // irrigation over 10 mins
      if ( irrigEnableCnt == IRRIG_TIME_CNT ){
          enableIrrig = false;
          irrigEnableCnt = 0;
      }
      // Stop irrigation over 50 mins
      if ( irrigDisableCnt == STOP_IRRIG_TIME_CNT ){
          enableIrrig = true;
          irrigDisableCnt = 0;
      }
      // open valve for 600 sec
      if ( enableIrrig ){
        digitalWrite(VALVE_D8, HIGH);
        irrigEnableCnt += 1;
      }else{
        digitalWrite(VALVE_D8, LOW);
        irrigDisableCnt += 1;
      }

      readSensors(enableIrrig, irrigEnableCnt, irrigDisableCnt);
      delay(5000);

    }else{
        readCnt++;
        Serial.print("In Skip mode: ");
        Serial.print("SKIP_NUM: ");
        Serial.print(SKIP_NUM);
        Serial.print(",");
        Serial.print("readCnt: ");
        Serial.println(readCnt);

    }

}

void readSensors(bool enableIrrig, int irrigEnableCnt, int irrigDisableCnt)
{


    float v0 = analogRead(EC5_A0)*(3.3/1023.0);
    float v1 = analogRead(EC5_A1)*(3.3/1023.0);
    float v2 = analogRead(EC5_A2)*(3.3/1023.0);
    Serial.print("Status:");
    Serial.print(enableIrrig);
    Serial.print(",");

    Serial.print("EnableCnt:");
    Serial.print(irrigEnableCnt);
    Serial.print(",");

    Serial.print("DisableCnt:");
    Serial.print(irrigDisableCnt);
    Serial.print(",");

    Serial.print("ec5,a0,");
    Serial.print(v0);
    Serial.print(",");

    Serial.print("ec5,a1,");
    Serial.print(v1);
    Serial.print(",");

    Serial.print("ec5,a2,");
    Serial.println(v2);
  }
