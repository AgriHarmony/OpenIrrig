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

// Commands definition

const char SEPERATOR = ',';
#define OPCODE_START 0
#define OPCODE_END 4
#define SENS_COMMAND_READ_PARAID 1
#define SENS_COMMAND_ACTUATOR_PARAID 1
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
int extractPara(String cmd, int speIdxs[10],int paraNum, int ParaId);
int getNonNegetiveCount( int sepIdxs[10] );
int* findSepIdxs(int* sepIdxs, String cmd);
bool isParaIdValid( int paraNum, int paraId );
void execute_SENS( String cmd, int speIdxs[10],int paraNum );
void execute_IRRI( String cmd, int speIdxs[10],int paraNum );
#endif // OPERATION_H_
