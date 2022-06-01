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

    for(uint8_t i=0;i<(hCBalgo->NCells-1);i++){
        for(uint8_t j=0;j<(i+1);j++)                                                      // mean of bottom cells for node i
          hCBalgo->VBOT[i]=hCBalgo->VBOT[i]+hCBalgo->VN_IN[j];
        for(uint8_t j=(i+1);j<hCBalgo->NCells;j++){

          hCBalgo->VTOP[i]=hCBalgo->VTOP[i]+hCBalgo->VN_IN[j];
          hCBalgo->DELTA[i]=(hCBalgo->VBOT[i])/(i+1)-(hCBalgo->VTOP[i]/(hCBalgo->NCells-1-i));  // error between bot and top mean value for node i
        }                                           // mean of top cells for node i
        if(hCBalgo->DELTA[i]<0){

          hCBalgo->SIGNDELTA[i]=-1;
        }
        else if(hCBalgo->DELTA[i]==0){

          hCBalgo->SIGNDELTA[i]=0;
        }
        else{

          hCBalgo->SIGNDELTA[i]=1;
          hCBalgo->ABSDELTA[i]=abs(hCBalgo->DELTA[i]);
        }
    }
    
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

    Serial.println("***************************************************************");
    Serial.println("ISETA");
    Serial.println(hCBalgo->ISETA);
    Serial.println("****************************************************************");

}


