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

void test_readCommandFromSerial(void){
    mySerial.println("TRAN,slave,master,usb");
    TEST_ASSERT_EQUAL(readCommandFromSerial(global.recevieContent, global.tempChar),
     "TRAN,slave,master,usb");

}
void loop() {

    RUN_TEST(test_readCommandFromSerial(void));
    delay(500);
    UNITY_END(); // stop unit testing

}

#endif
