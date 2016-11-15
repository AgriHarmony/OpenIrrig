#include <Operation.h>

int getNonNegetiveCount( int sepIdxs[10] ){
  int i = 0, cnt = 0;
  while( sepIdxs[i] >= 0 && i<10){
    cnt++;
    i++;
  }
  return cnt;
}

int* findSepIdxs(int* sepIdxs, String cmd){
  int arrIdx = 0;
  for(int i=0; (unsigned)i < cmd.length(); i++){
    if(cmd[i] == SEPERATOR){
      sepIdxs[arrIdx++] = i;
    }
  }
  return sepIdxs;
}

/*
  cmd(arduino string):
            a string with full command (include opcode and parameters)
  speIdx(int[]):
            array of indexes command SEPERATOR(,).
            Ex: "SENS,3" => speIdx[10] = {4, -1, -1, -1, -1, -1, -1, -1, -1, -1}
  ParaNum(int):
            the total number of parameters
            Ex: speIdx[10] = {4, -1, -1, -1, -1, -1, -1, -1, -1, -1} => 1
  paraId(int, 1<paraId<ParaNum):
            select the parameter in command by paraId. the paraId is start from 1
            it mean that if you want first parameter in command, paraId = 1
            Ex: "IRRI,3,15,5" && paraId=2 => 15
*/
int extractPara(String cmd, int speIdxs[10], int paraNum, int paraId){

  String paraStr = "";
  int paraLen = 0;
  int shiftIdx = paraId-1;
  int start = speIdxs[shiftIdx]+1;
  if( paraId == paraNum ){
      // (cmd.length()-1): must -1 due to length() include null at string end
      // speIdx[paraId-1]+1): c array index start from 0, shift 1 by Function
      //                      define paraId start from 1
      paraLen = (cmd.length()-1) - (speIdxs[shiftIdx]+1);
  }
  else if( paraId < paraNum ){
      paraLen = (speIdxs[shiftIdx+1]-1) - speIdxs[shiftIdx];
  }

  paraStr = cmd.substring(start, start+paraLen);
  // Serial.print("paraStr: ");
  // Serial.println(paraStr);
  // Serial.print("cmd.length(): ");
  // Serial.print(cmd.length());
  // Serial.print(" ,start: ");
  // Serial.print(start);
  // Serial.print(" ,start char: ");
  // Serial.print(cmd[start]);
  // Serial.print(" ,end: ");
  // Serial.print(start+paraLen);
  // Serial.print(" ,end char: ");
  // Serial.println(cmd[start+paraLen]);

  return paraStr.toInt();
}
bool isParaIdValid( int paraNum, int paraId ){
  // parameter index boundary check
  if( paraId > 0 && paraId <= paraNum )
    return true;
  else // paraId <= 0 || paraId > paraNum, invalid.
    return false;
}
//
//  Function Implementation
//
void decode(String cmd){

  if( cmd != "" ){

    // Get opcode of cmd
    String op = cmd.substring( OPCODE_START, OPCODE_END );
    // Serial.println( op );

    // Find SEPERATOR idxs
    int speIdxSize = SEPERATOR_ARRAY_SIZE;
    int *sepIdxs = new int[speIdxSize];
    for(int i=0;i<speIdxSize;i++){
      sepIdxs[i] = -1;
    }
    sepIdxs = findSepIdxs(sepIdxs, cmd);

    int paraNum = getNonNegetiveCount(sepIdxs);
    // Serial.print("paraNum: ");
    // Serial.print(paraNum);

    if ( strcmp( op.c_str(), "SENS") == 0 ){
      execute_SENS( cmd, sepIdxs, paraNum );
    }
    else if( strcmp( op.c_str(), "IRRI") == 0 ){
      execute_IRRI( cmd, sepIdxs, paraNum );
    }
    else if ( strcmp( op.c_str(), "DWRI") == 0){

    }
    // else if( strcmp( op.c_str(), "TRAN") == 0 ){
    //   Serial.print("TRAN:");
    //
    // }
    // else{
    //   Serial.println("undefine cmd");
    // }
  }
}
float sensorAnalogRead(int pin){
  return (float)(analogRead(pin)*(3.3/1023.0));
}
void execute_DWRI( String cmd, int sepIdxs[10],int paraNum ){
  int actuatorPin = -1;
  if( isParaIdValid( paraNum, SENS_COMMAND_ACTUATOR_PARAID ) )
    actuatorPin = extractPara(cmd, sepIdxs, paraNum, SENS_COMMAND_ACTUATOR_PARAID );

  digitalWrite( actuatorPin, HIGH );
}
void execute_IRRI( String cmd, int sepIdxs[10],int paraNum ){
  int actuatorPin = -1;
  if( isParaIdValid( paraNum, SENS_COMMAND_ACTUATOR_PARAID ) )
    actuatorPin = extractPara(cmd, sepIdxs, paraNum, SENS_COMMAND_ACTUATOR_PARAID );

  digitalWrite( actuatorPin, HIGH );

}
void execute_SENS( String cmd, int sepIdxs[10],int paraNum ){
  // pass test case

  int sensorPin = -1;
  if( isParaIdValid( paraNum, SENS_COMMAND_READ_PARAID ) )
    sensorPin = extractPara(cmd, sepIdxs, paraNum, SENS_COMMAND_READ_PARAID );

  // Print info. part
  Serial.print( cmd.substring( OPCODE_START, OPCODE_END ) );
  Serial.print( "," );
  Serial.println( sensorAnalogRead(sensorPin) );

  // Serial.println("=== paraId:1 ===");
  // if( isParaIdValid( paraNum, 1 ) )
  //   pin = extractPara(cmd, sepIdxs, paraNum, 1 );
  // Serial.print("Pin:");
  // Serial.println(pin);
  //
  // // fail test case
  // Serial.println("=== paraId:2 ===");
  // if( isParaIdValid( paraNum, 2 ) )
  //   pin = extractPara(cmd, sepIdxs, paraNum, 2 );
  // Serial.print("Pin:");
  // Serial.println(pin);
  //
  // Serial.println("=== paraId:0 ===");
  // if( isParaIdValid( paraNum, 0 ) )
  //   pin = extractPara(cmd, sepIdxs, paraNum, 0 );
  // Serial.print("Pin:");
  // Serial.println(pin);
  //
  // Serial.println("=== paraId:-1 ===");
  // if( isParaIdValid( paraNum, -1 ) )
  //   pin = extractPara(cmd, sepIdxs, paraNum, -1 );
  // Serial.print("Pin:");
  // Serial.println(pin);
}
String readCommandFromSerial( String recevieContent, char tempChar ){

  recevieContent = "";
  // Serial.println("reading");
  while( Serial.available() ){
    tempChar = Serial.read();
    // Serial.print(tempChar);
    recevieContent.concat(tempChar);
    delay (10);
    if (recevieContent != "" && tempChar == '\n') {
      break;
    }
  }
  return recevieContent;
}
void cleanRecevieContent(String recevieContent){
  recevieContent = "";
}
