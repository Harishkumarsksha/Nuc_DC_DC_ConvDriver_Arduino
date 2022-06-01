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
  double VBOT[8];
  double VTOP[8];
  double DELTA[8];
  int SIGNDELTA[8];
  int SIGNDELTA_PV[8];
  double ABSDELTA[8];
  double MAXDELTA;
  uint8_t DIR;
  double ISETA;
  uint8_t RESET;
  double ISETA_INC_STEP;
  double VTHL_CB;

  bool   BUCK=0;
  bool   BOOST=0;

  uint8_t NODEARRAY[8];

}CBalgo;


void CBalgoFunc(CBalgo *hCBalgo);
void CBalgoTest(CBalgo *hCBalgo);
#endif 