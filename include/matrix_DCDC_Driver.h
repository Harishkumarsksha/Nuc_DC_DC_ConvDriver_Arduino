/**
 * @file matrix_DCDC_Driver.h
 * @author Harish 
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef MATRIX_DCDC_CONVERTER_DRIVER_H__
#define MATRIX_DCDC_CONVERTER_DRIVER_H__

#include <Arduino.h>
#include "Wire.h"
#include "stm32h743xx.h"
#include "main.h"


void  disableDCDCConverter();
void enableDCDCConverter(uint8_t DIR);
void switchBalanceNode(uint8_t currentNode, uint8_t prevoiusNode);
void disableCells();
void DCDCConverter_MatrixDriver(uint8_t currentNode,uint8_t previousNode, uint8_t DIR  );




#endif 