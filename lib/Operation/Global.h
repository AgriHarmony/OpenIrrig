#ifndef GLOBAL_H
#define GLOBAL_H
#include "Arduino.h"

struct Global{
  int readCnt;
  int irrigEnableCnt;
  int irrigDisableCnt;
  bool enableIrrig;
  char tempChar;
  String recevieContent;
};
#endif
