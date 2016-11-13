#include <Operation.h>

int getNonNegetiveCount( int sepIdx[10] ){
  int i = 0, cnt = 0;
  while( sepIdx[i] >= 0 && i<10){
    cnt++;
    i++;
  }
  return cnt;
}

int* findSepIdxs(int* sepIdx, String cmd){
  int arrIdx = 0;
  for(int i=0; (unsigned)i < cmd.length(); i++){
    if(cmd[i] == SEPERATOR){
      sepIdx[arrIdx++] = i;
    }
  }
  return sepIdx;
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
  ParaId(int, 1<ParaId<ParaNum):
            select the parameter in command by ParaId. the ParaId is start from 1
            it mean that if you want first parameter in command, ParaId = 1
            Ex: "IRRI,3,15,5" && ParaId=2 => 15
*/
int extractPara(String cmd, int speIdx[10], int paraNum, int ParaId){

  String paraStr = "";
  // parameter index boundary check
  if( ParaId > 0 && ParaId <= paraNum ){
    int parnLen = 0;
    int idx = ParaId-1;
    if( ParaId == paraNum ){
        parnLen = cmd.length()-speIdx[idx]-2;
    }else{
        parnLen = speIdx[idx]-speIdx[idx]-1;
    }
    paraStr = cmd.substring(speIdx[idx]+1, parnLen);

    Serial.print("paraStr: ");
    Serial.println(paraStr);
    Serial.print("cmd.length()")
    Serial.print(cmd.length());
    Serial.print(" ,start: ");
    Serial.print(speIdx[idx]+1);
    Serial.print(" ,end: ");
    Serial.print(parnLen);
  }else{
    Serial.print("invalid ParaId");
  }
  return paraStr.toInt();
}

//
//  Function Implementation
//
void decode(String cmd){

  if( cmd != "" ){
    Serial.print(cmd);
    // Get opcode of cmd
    String op = cmd.substring(0,4);
    // Serial.println( op );

    // Find SEPERATOR idxs
    int speIdxSize = SEPERATOR_ARRAY_SIZE;
    int *sepIdx = new int[speIdxSize];
    for(int i=0;i<speIdxSize;i++){
      sepIdx[i] = -1;
    }
    sepIdx = findSepIdxs(sepIdx, cmd);
    // Serial.print("sepIdx[]: ");
    // for(int i=0;i<speIdxSize;i++){
    //   Serial.print(sepIdx[i]);
    //   Serial.print(",");
    // }
    // Serial.println();

    int paraNum = getNonNegetiveCount(sepIdx);
    // Serial.print("paraNum: ");
    // Serial.print(paraNum);

    if ( strcmp( op.c_str(), "SENS") == 0 ){
      Serial.println("SENS:");
      // pass test case
      int pin = -1;
      Serial.println("=====");
      pin = extractPara(cmd, sepIdx, paraNum, 1 );
      Serial.print("Pin:");
      Serial.println(pin);

      // fail test case
      // Serial.println("=====");
      // pin = extractPara(cmd, sepIdx, paraNum, 2 );
      // Serial.print("Pin:");
      // Serial.println(pin);
      //
      // Serial.println("=====");
      // pin = extractPara(cmd, sepIdx, paraNum, 0 );
      // Serial.print("Pin:");
      // Serial.println(pin);
      //
      // Serial.println("=====");
      // pin = extractPara(cmd, sepIdx, paraNum, -1 );
      // Serial.print("Pin:");
      // Serial.println(pin);

      // Serial.println(sensorAnalogRead( pin ));
    }
    // else if( strcmp( op.c_str(), "TRAN") == 0 ){
    //   Serial.print("TRAN:");
    //
    // }
    // else if( strcmp( op.c_str(), "IRRI") == 0 ){
    //   Serial.print("IRRI:");
    // }
    // else{
    //   Serial.println("undefine cmd");
    // }
  }
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
float sensorAnalogRead(int pin){
  return (float)(analogRead(pin)*(3.3/1023.0));
}
