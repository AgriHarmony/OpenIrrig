#ifndef OPERATION_H_
#include "Arduino.h"

#define OPERATION_H_

#define MINIMUM_VALUE -32768
#define MAXMUM_VALUE 32767

// Decagon Sensor Value Setup
#define EC5_A2 2  // 5cm depth
#define EC5_A1 1  // 10cm depth
#define EC5_A0 0  // 15cm depth

// Actuactor Setup
#define VALVE_D8 8 // electric valve

// Read Sensor Behavior
#define SKIP_NUM 5 // skipping first 5 reading data due to sensor starting
#define CNT_TIME_UNIT 60000 // unit in ms
#define IRRIG_TIME_CNT 30
#define STOP_IRRIG_TIME_CNT 30
#define PURE_MONITOR_CNT 60 // Unit is CNT_TIME_UNIT

#define SEPERATOR_ARRAY_SIZE 10;
const char SEPERATOR = ',';


//
// Function Declaration
//

// ===========================
void slaveRead();
/* arduino as a slave listen to the master cmd */
// ===========================

// ===========================
String readCommandFromSerial( String recevieContent, char tempChar );
// ===========================

//
void decode( String cmd );
/* decode the command from master and correspondly act  */
//

void cleanRecevieContent( String recevieContent );
int extractPara(String cmd, int speIdx[10],int paraNum, int ParaId);
int getNonNegetiveCount( int sepIdx[10] );
int* findSepIdxs(int* sepIdx, String cmd);

#endif // OPERATION_H_
