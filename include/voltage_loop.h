/**
 * @file voltage_loop.h
 * @author Harish
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef VOLTAGE_LOOP_H__
#define VOLTAGE_LOOP_H__
#include <Arduino.h>
#include "Wire.h"
#include "stm32h743xx.h"
#include "main.h"

// #include "matrix_DCDC_Driver.h"
#include "algo.h"


void ISETaFunc(CBalgo *hCBalgo);

#endif 