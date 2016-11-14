#include <Arduino.h>
#include <unity.h>
#include <Global.h>
#include <Operation.h>
#include "SoftwareSerial.h"

#ifdef UNIT_TEST
SoftwareSerial mySerial(10, 11);
struct Global global;

void setup() {
    UNITY_BEGIN();    // IMPORTANT LINE!
    Serial.begin(57600);
    while(!Serial){
        ;
    }
    mySerial.begin(57600);

    // initialize global struct
    global.readCnt = 0;
    global.irrigEnableCnt = 0;
    global.irrigDisableCnt = 0;
    global.enableIrrig = false;
    // global.tempChar = '';
    global.recevieContent = "";

    // mySerial.println("TRAN,slave,master,usb");
    // mySerial.println("SENS,0");
    // mySerial.println("IRRI,1,60,30");

}

// void test_readCommandFromSerial(void){
//     mySerial.println("TRAN,slave,master,usb");
//     TEST_ASSERT_EQUAL_STRING(readCommandFromSerial(global.recevieContent, global.tempChar),
//      "TRAN,slave,master,usb");
//
// }
void loop() {
    String s1 = "123";
    const char* s2 = "123";
    Serial.print("s1: ");
    Serial.print(typeof(s1));
    Serial.print("s2: ");
    Serial.print(typeof(s2));

    // RUN_TEST(test_readCommandFromSerial);
    delay(500);
    UNITY_END(); // stop unit testing

}

#endif
