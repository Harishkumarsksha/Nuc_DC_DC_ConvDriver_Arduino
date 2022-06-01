/**
 * @file BLE_Voltages.cpp
 * @author Harish 
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>
#include "stm32h743xx.h"
#include "main.h"

#include "algo.h"
#include "BLE_Voltages.h"




// void getBLEdata(CBalgo *hCBalgo,BLE *hBLE){
//     //1,f,1793,1559,152,2,f,1788,1548,151,3,f,1788,1447,139,4,f,1792,1545,151,5,f,1799,1476,142,6,f,1794,1548,152,7,f,1793,1486,145,@,
//     hBLE->BLE_buffer[0] = BMS_DATA_AVERAGE_REQ;
//     if(HAL_UART_Transmit(&huart3,hBLE->BLE_buffer,1,10) == HAL_OK){
//         if (HAL_UART_Receive (&huart3, hBLE->BLE_buffer,hBLE->BLEbyteCount, 10)==HAL_OK)
//         {
//             dataConvertBLE(hCBalgo,hBLE);
//         }
        
//     }
// }



// void dataConvertBLE(CBalgo *hCBalgo,BLE *hBLE){
//         // Check the last terionation charecter to make sure all the data has recived 
//         if(hBLE->BLE_buffer[127]=='@'){
//                 uint8_t count = 0;
//                 for(uint8_t i=0;i< hBLE->BLEbyteCount;i++){
                    
//                     if (hBLE->BLE_buffer[i]=='f')
//                     {
//                         hBLE->VBAT[count]=(int16_t)((hBLE->BLE_buffer[i+2]<<8) + hBLE->BLE_buffer[i+3]);
//                         count++;
//                     }
                    
//                 }
//         }
// }



void VoltageInitializationDumy(CBalgo *hCBalgo,uint8_t min,uint8_t max){
  // uint8_t RAND_MAX=4;
  //Debuggin g purpose 
  Serial.println("Vtolgates Data:");
  Serial.println("*****************************************************");
  for(uint8_t i=0;i<hCBalgo->NCells;i++){
    // hCBalgo->VN_IN[i]=((float)rand()/(float)(0.1)) * i;
    hCBalgo->VN_IN[i]=((max - min) * ((double)rand() / RAND_MAX)) + min;

    Serial.println(hCBalgo->VN_IN[i]);
  }
  Serial.println("*****************************************************");
}
