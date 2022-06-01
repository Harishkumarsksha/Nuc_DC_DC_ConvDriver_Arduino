/**
 * @file algo.cpp
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
#include "algo.h"
#include "voltage_loop.h"
#include "matrix_DCDC_Driver.h"
#include "BLE_Voltages.h"







void CBalgoFunc(CBalgo *hCBalgo){
    // check if the cellsare unblanced 

    double MAXVCELL=hCBalgo->VN_IN[0];
    for(uint8_t i=1;i<hCBalgo->NCells;i++){
        if(hCBalgo->VN_IN[i]>MAXVCELL){
          MAXVCELL=hCBalgo->VN_IN[i];
        }
    }

    double MINVCELL=hCBalgo->VN_IN[0];
    for(uint8_t i=1;i<hCBalgo->NCells;i++){
        if(hCBalgo->VN_IN[i]<MINVCELL){
            MINVCELL=hCBalgo->VN_IN[i];
        }
    }
    double ERROR=MAXVCELL-MINVCELL;
    if(ERROR<0.002){
      hCBalgo->CELLBALANCED=1;
      hCBalgo->NODE=0;
      hCBalgo->CB_ENABLE=0;
      hCBalgo->BUCK=0;
      hCBalgo->BOOST=0;
      }



  else{

    // compute bottom and top cells mean, error, check error sign
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



        // look for the unbalanced node  
      // Serial.println("*****************************************************");
      hCBalgo->MAXDELTA=hCBalgo->ABSDELTA[0];
      for(uint8_t i=1;i<hCBalgo->NCells;i++){
          if( hCBalgo->ABSDELTA[i]>hCBalgo->MAXDELTA){
            hCBalgo->MAXDELTA=hCBalgo->ABSDELTA[i];
            hCBalgo->NODE=i+1;

          }
            // Serial.println("absolute delta");
            // Serial.println(hCBalgo->ABSDELTA[i]);
            

      }
      // Serial.println("*****************************************************");
      // set the pin DIR - buck or boost
      if( hCBalgo->SIGNDELTA[ hCBalgo->NODE-1]<0){
        hCBalgo->DIR=1; // TRUE - BUCK MODE --> GPIO pin set HIGH
        hCBalgo->BUCK=1;
        hCBalgo->BOOST=0;
      }
        
      else{
        hCBalgo->DIR=0; // FALSE - BOOST MODE --> GPIO pin set LOW
        hCBalgo->BUCK=0;
        hCBalgo->BOOST=1;
      }
      hCBalgo->CB_ENABLE=1;
      hCBalgo->CELLBALANCED=0;
      hCBalgo->NODEARRAY[hCBalgo->NODE-1]=1;

  }
 DCDCConverter_MatrixDriver(hCBalgo->NODE,hCBalgo->NODEARRAY[hCBalgo->NODE-1], hCBalgo->DIR);
 ISETaFunc(hCBalgo);
}


void CBalgoTest(CBalgo *hCBalgo){
  
  VoltageInitializationDumy(hCBalgo,3.8,4);
  CBalgoFunc(hCBalgo);
  Serial.println("*****************************************************");
  Serial.println("Algo Outputs");
  Serial.print("Node Needs to be balanced: ");
  Serial.println(hCBalgo->NODE);
  Serial.println("Direction :");
  Serial.println(hCBalgo->DIR);
  Serial.println("*****************************************************");
}

