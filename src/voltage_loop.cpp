/**
 * @file voltage_loop.c
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
#include "voltage_loop.h"

void ISETaFunc(CBalgo *hCBalgo){
    if(hCBalgo->RESET==0){
        if((hCBalgo->ISETA<0.8)&&(hCBalgo->ISETA>=0.015)&&(hCBalgo->SIGNDELTA[hCBalgo->NODE-1]==hCBalgo->SIGNDELTA_PV[hCBalgo->NODE-1])){
         if(hCBalgo->ABSDELTA[hCBalgo->NODE-1]>hCBalgo->VTHL_CB)
             hCBalgo->ISETA=hCBalgo->ISETA+hCBalgo->ISETA_INC_STEP;
         else
            hCBalgo->ISETA=hCBalgo->ISETA-0.001;
          }
        else{
          if(hCBalgo->SIGNDELTA[hCBalgo->NODE-1]!=hCBalgo->SIGNDELTA_PV[hCBalgo->NODE-1]){

                hCBalgo->ISETA=0.015;
          }
        }
    }
    else{
      if(hCBalgo->ABSDELTA[hCBalgo->NODE-1]>hCBalgo->VTHL_CB)
        hCBalgo->ISETA=hCBalgo->ISETA+hCBalgo->ISETA_INC_STEP;
    }
    hCBalgo->RESET=0;
}


