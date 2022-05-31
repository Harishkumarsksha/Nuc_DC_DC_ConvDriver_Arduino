/**
 * @file matrix_DCDC_Driver.cpp
 * @author Harish 
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <Arduino.h>
#include "Wire.h"
#include "stm32h743xx.h"
#include "main.h"
#include "matrix_DCDC_Driver.h"


void DCDCConverter_MatrixDriver(uint8_t currentNode,uint8_t previousNode, uint8_t DIR  ){
    disableCells();
    disableDCDCConverter();
    switchBalanceNode(currentNode,previousNode);
    enableDCDCConverter(DIR); 
}

void disableDCDCConverter(){

  // Debuggin purpose 
  // Disabled the DC DC converter and bleed 
  Serial.println("Disabled the DC DC converter and bleed ");
  HAL_GPIO_WritePin(UVLO_GPIO_Port,UVLO_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Bleed_GPIO_Port,Bleed_Pin, GPIO_PIN_RESET);

}


void disableCells(){
    // Debuggin purpose 
  // Disabled All the Cells 
  Serial.println("Disabled All the Cells  ");
  HAL_GPIO_WritePin(CB7_GPIO_Port,CB7, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CB6_GPIO_Port,CB6, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CB5_GPIO_Port,CB5, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CB4_GPIO_Port,CB4, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CB3_GPIO_Port,CB3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CB2_GPIO_Port,CB2, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CB1_GPIO_Port,CB1, GPIO_PIN_RESET);
}

void switchBalanceNode(uint8_t currentNode, uint8_t prevoiusNode){

  if(currentNode>prevoiusNode){
    disableCells();
    switch (currentNode)
    {
    case 1:
      HAL_GPIO_WritePin(CB1_GPIO_Port,CB1, GPIO_PIN_SET);
        // Debuggin purpose 
      // Node 1 is enabled 
      Serial.println("Node 1 is enabled   ");
      break;
    case 2:

      HAL_GPIO_WritePin(CB2_GPIO_Port,CB2, GPIO_PIN_SET);
      // Debuggin purpose 
      // Node 2 is enabled 
      Serial.println("Node 2 is enabled   ");
      break;
    case 3:

      HAL_GPIO_WritePin(CB3_GPIO_Port,CB3, GPIO_PIN_SET);
      // Debuggin purpose 
      // Node 3 is enabled 
      Serial.println("Node 3 is enabled   ");
      break;
    case 4:

      HAL_GPIO_WritePin(CB4_GPIO_Port,CB4, GPIO_PIN_SET);
      // Debuggin purpose 
      // Node 4 is enabled 
      Serial.println("Node 4 is enabled   ");
      break;
    case 5:

      HAL_GPIO_WritePin(CB5_GPIO_Port,CB5, GPIO_PIN_SET);
      // Debuggin purpose 
      // Node 5 is enabled 
      Serial.println("Node 5 is enabled   ");
      break;
    case 6:

      HAL_GPIO_WritePin(CB6_GPIO_Port,CB6, GPIO_PIN_SET);
      // Debuggin purpose 
      // Node 6 is enabled 
      Serial.println("Node 6 is enabled   ");
      break;
    case 7:

      HAL_GPIO_WritePin(CB7_GPIO_Port,CB7, GPIO_PIN_SET);
       // Debuggin purpose 
      // Node 7 is enabled 
      Serial.println("Node 7 is enabled   ");
      break;
    
    default:
      disableCells();
      break;
    }
  }
  else {

    HAL_GPIO_WritePin(Bleed_GPIO_Port,Bleed_Pin, GPIO_PIN_SET); // Switch on the bleed 
    Serial.println("Bleed is Enabled   ");
    HAL_Delay(10); // DC Dc output capacitor discharge can be increased according to the selecetedx output caopacitor 
    HAL_GPIO_WritePin(Bleed_GPIO_Port,Bleed_Pin, GPIO_PIN_RESET); // Switch off  the bleed after output node capacitor discharged 
    Serial.println("Bleed Disabled  ");

    for (uint8_t i = 1; i < currentNode+1; i++)
    {
      switch (i)
        {
        case 1:
          disableCells();
          HAL_GPIO_WritePin(CB1_GPIO_Port,CB1, GPIO_PIN_SET);
            // Debuggin purpose 
          // Node 1 is enabled 
          Serial.println("Node 1 is enabled   ");
          break;
        case 2:
          disableCells();
          HAL_GPIO_WritePin(CB2_GPIO_Port,CB2, GPIO_PIN_SET);
          // Debuggin purpose 
          // Node 2 is enabled 
          Serial.println("Node 2 is enabled   ");
          break;
        case 3:
          disableCells();
          HAL_GPIO_WritePin(CB3_GPIO_Port,CB3, GPIO_PIN_SET);
          // Debuggin purpose 
          // Node 3 is enabled 
          Serial.println("Node 3 is enabled   ");
          break;
        case 4:
          disableCells();
          HAL_GPIO_WritePin(CB4_GPIO_Port,CB4, GPIO_PIN_SET);
          // Debuggin purpose 
          // Node 4 is enabled 
          Serial.println("Node 4 is enabled   ");
          break;
        case 5:
          disableCells();
          HAL_GPIO_WritePin(CB5_GPIO_Port,CB5, GPIO_PIN_SET);
          // Debuggin purpose 
          // Node 5 is enabled 
          Serial.println("Node 5 is enabled   ");
          break;
        case 6:
          disableCells();
          HAL_GPIO_WritePin(CB6_GPIO_Port,CB6, GPIO_PIN_SET);
          // Debuggin purpose 
          // Node 6 is enabled 
          Serial.println("Node 6 is enabled   ");
          break;
        case 7:
          disableCells();
          HAL_GPIO_WritePin(CB7_GPIO_Port,CB7, GPIO_PIN_SET);
          // Debuggin purpose 
          // Node 7 is enabled 
          Serial.println("Node 7 is enabled   ");
          break;

        default:
          disableCells();
          break;
      }
  }
}
}

void enableDCDCConverter(uint8_t DIR){

  if (HAL_GPIO_ReadPin(nFault_GPIO_Port,nFault_Pin) == GPIO_PIN_SET){
    
      HAL_GPIO_WritePin(UVLO_GPIO_Port,UVLO_Pin, GPIO_PIN_SET);
      HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin, GPIO_PIN_SET);
      // Debuggin purpose 
      // DC Dc converter is enabled 
        Serial.println("DC Dc converter is enabled    ");
      if(DIR==1){
        // Debuggin purpose 
      // DC Dc converter is in the buck mode 
        Serial.println("DC Dc converter is in the buck mode    ");

        HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin, GPIO_PIN_SET); // Buck Mode 
      }
      else {
      // Debuggin purpose 
      // DC Dc converter is in the Bost mode 
        Serial.println("DC Dc converter is in the Bost mode    ");
        HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin, GPIO_PIN_RESET); // Boost  Mode 
      }
  }
  // Read the Fault is the nfault is the low then low the uvlo check the uvlo 
  // if still nfault enable is the low the continue the same process five times 
  // if nfault is High in any of the 5 attempts break the loop 

  else {

    for (uint8_t i = 0; i < 5; i++)
    {
      HAL_GPIO_WritePin(UVLO_GPIO_Port,UVLO_Pin, GPIO_PIN_RESET);
        // Debuggin purpose 
      // DC Dc converter is in the Fault
        Serial.println("DC Dc converter is in Fault    ");
      if (HAL_GPIO_ReadPin(nFault_GPIO_Port,nFault_Pin) == GPIO_PIN_SET){
        HAL_GPIO_WritePin(UVLO_GPIO_Port,UVLO_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(EN_GPIO_Port,EN_Pin, GPIO_PIN_SET);
        // Debuggin purpose 
        // DC Dc converter is enabled 
        Serial.println("DC Dc converter is enabled    ");
        if(DIR==1){
            // Debuggin purpose 
          // DC Dc converter is in the buck mode 
            Serial.println("DC Dc converter is in the buck mode    ");

            HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin, GPIO_PIN_SET); // Buck Mode 
          }
          else {
          // Debuggin purpose 
          // DC Dc converter is in the Bost mode 
            Serial.println("DC Dc converter is in the Bost mode    ");
            HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin, GPIO_PIN_RESET); // Boost  Mode 
          }
        break;
      }
    }    
  }
}