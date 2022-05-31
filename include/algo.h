/**
 * @file algo.h
 * @author Harish 
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ALGO_H__
#define ALGO_H__
#include <Arduino.h>
#include "Wire.h"
#include "stm32h743xx.h"
#include "main.h"

// #include "matrix_DCDC_Driver.h"

typedef struct {
  uint8_t NODE ;
  uint8_t NCells;
  double VN_IN[8];
  bool CELLBALANCED;
  bool CB_ENABLE;
  float VBOT[8];
  float VTOP[8];
  float DELTA[8];
  int SIGNDELTA[8];
  int SIGNDELTA_PV[8];
  float ABSDELTA[8];
  float MAXDELTA;
  uint8_t DIR;
  float ISETA;
  uint8_t RESET;
  float ISETA_INC_STEP;
  float VTHL_CB;

}CBalgo;


void CBalgoFunc(CBalgo *hCBalgo);
void VoltageInitialization(CBalgo *hCBalgo,uint8_t min,uint8_t max);
void CBalgoTest(CBalgo *hCBalgo);
#endif 