/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "SoftwareSerial.h"

// Decagon Sensor Value Setup
#define EC5_A2 2  // 15cm depth
#define EC5_A1 1  // 10cm depth
#define EC5_A0 0  // 5cm depth

// Actuactor Setup
#define VALVE_D8 8 // electric valve

// Read Sensor Behavior
#define SKIP_NUM 0 // skipping first 5 reading data due to sensor starting
#define CNT_TIME_UNIT 60000 // unit in ms
#define PURE_SENS_CNT 1 // Unit is CNT_TIME_UNIT, and take it as base line
#define IRRIG_TIME_CNT 15
#define STOP_IRRIG_TIME_CNT 45


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

// ===========================
void readCommandFromSerial();
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
  // readCommandFromSerial();
  simplePeriodicIrrig();
}

//
//  Function Implementation
//

void readCommandFromSerial(){
  if( Serial.available() ){
     String inBuffer = Serial.readString();
     if (inBuffer != NULL) {
       Serial.println(inBuffer);
     }
  }
}
void simplePeriodicIrrig(){

  if (readCnt > SKIP_NUM + PURE_SENS_CNT )
  {
      // start to irrigate
      if ( irrigEnableCnt >= IRRIG_TIME_CNT ){
          enableIrrig = false;
          irrigEnableCnt = 0;
      }
      // Stop irrigation over 50 mins
      if ( irrigDisableCnt >= STOP_IRRIG_TIME_CNT ){
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
      // Serial.print(irrigEnableCnt);
      // Serial.print(",");
      // Serial.print(irrigDisableCnt);
      // Serial.print(",");
      // This Part should be moved
      Serial.print("Status:");
      if( enableIrrig == true ){
          Serial.print("IRRI");
      }else{
          Serial.print("IDLE");
      }
      // Serial.print("MONI");
      Serial.print(",");

    }else{
      if ( readCnt < SKIP_NUM ){
        Serial.print("In Skip mode: ");
        Serial.print("SKIP_NUM: ");
        Serial.print(SKIP_NUM);
        Serial.print(",");
        Serial.print("readCnt: ");
        Serial.println(readCnt);
      } else {
        Serial.print("SENS");
      }
      Serial.print(",");
    }
    readCnt++;
    readSensors(enableIrrig, irrigEnableCnt, irrigDisableCnt);
    delay(CNT_TIME_UNIT);
}
/*
*   void readSensors(bool, int, int)
*   @Para:
*   @Return:
*/
void readSensors(bool enableIrrig, int irrigEnableCnt, int irrigDisableCnt)
{
    float v0 = analogRead(EC5_A0)*(3.3/1023.0);
    float v1 = analogRead(EC5_A1)*(3.3/1023.0);
    float v2 = analogRead(EC5_A2)*(3.3/1023.0);

    // A0 sensor
    // Serial.print("ec5,a0,");
    Serial.print(v0);
    Serial.print(",");

    // A1 sensor
    // Serial.print("ec5,a1,");
    Serial.print(v1);
    Serial.print(",");

    // A2 sensor
    // Serial.print("ec5,a2,");
    Serial.println(v2);
    // Serial.println();
  }
