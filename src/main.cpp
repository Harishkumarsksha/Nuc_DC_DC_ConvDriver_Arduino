#include <Arduino.h>
#include "Wire.h"
#include "stm32h743xx.h"
#include "main.h"

#include "matrix_DCDC_Driver.h"
#include "algo.h"
#include "voltage_loop.h"
#include "BLE_Voltages.h"

ETH_TxPacketConfig TxConfig;

ETH_HandleTypeDef heth;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart3;

HAL_StatusTypeDef ret;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);



void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 24;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}



/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10707DBC;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, UVLO_Pin|EN_Pin|DIR_Pin|Bleed_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_OTG_FS_PWR_EN_GPIO_Port, USB_OTG_FS_PWR_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : UVLO_Pin EN_Pin DIR_Pin Bleed_Pin */
  GPIO_InitStruct.Pin = UVLO_Pin|EN_Pin|DIR_Pin|Bleed_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : nFault_Pin */
  GPIO_InitStruct.Pin = nFault_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(nFault_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OTG_FS_PWR_EN_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_PWR_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_OTG_FS_PWR_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OTG_FS_OVCR_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_OVCR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OTG_FS_OVCR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}



/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

static I2C_HandleTypeDef i2cHandler;
HAL_StatusTypeDef status;
CBalgo hCBalgo;
BLE hBLE;

// User Function Definitions 

// void CBalgoFunc(CBalgo *hCBalgo);
// void VoltageInitialization(CBalgo *hCBalgo,uint8_t min,uint8_t max);
void dataConvertBLEVoltages(BLE *hBLE);
void setup(){

  SystemClock_Config(); // system clock configuration 
  MX_I2C1_Init(); // i2c1 initialization 
  Serial.begin(9600); // startuart communication uart1 
  Wire.begin(); // start the i2c communication of i2c1


  // Preinitialization 
  uint8_t CurrentNode = 7; 
  uint8_t PreviousNode = 1;
  uint8_t DIR = 0;
  Serial.println("DC to Dc converter Driver");
  // DCDCConverter_MatrixDriver(CurrentNode,PreviousNode, DIR);

  hCBalgo.NCells=8;
  // hCBalgo.VN_IN[8]={3.2,3.33,3.4,3.25,3.6,3.7,3.56,3.62};
  // VoltageInitialization(&hCBalgo,3.2,4);

  // CBalgoFunc(&hCBalgo);
  Serial.print(0xfd,HEX);

  
}

void loop(){
  
  /**
   * @brief INA Function Testing 
   * 
   */


  //   // Current node and the prevois node and the dir are coming from the algorithm
  //   // for the driver testing purpose initialized locally 
  //   uint8_t CurrentNode = 5; 
  //   uint8_t PreviousNode = 7;
  //   uint8_t DIR = 0;

  //     // if condion is just to read the user choice fro the serial terminal 
  //     // in original progra if condition for check serial port wont be there 
  //     if (Serial.available() > 0) {

  //       // to read the user terinal values for the debuggub purpose 
  //       Serial.println("Enter the Prevoius Node :");
  //       PreviousNode = Serial.read();
  //       Serial.println("Enter the CurrentNode Node :");
  //       CurrentNode = Serial.read();
  //       Serial.println("Enter the Direction");
  //       Serial.println("0 for the Boost Mode :");
  //       Serial.println("1 for Buck Mode      :");
  //       DIR = Serial.read();

  //       DCDCConverter_MatrixDriver(CurrentNode,PreviousNode, DIR);
        
  // }

  // else {

  //     DCDCConverter_MatrixDriver(CurrentNode,PreviousNode, DIR);
  // }
  
  // AlgoTesting 
  CBalgoTest(&hCBalgo);
  // VoltageInitialization(&hCBalgo,3.2,4);
  // CBalgoFunc(&hCBalgo);
  // Serial.println("*****************************************************");
  // Serial.println("Algo Outputs");
  // Serial.print("Node Needs to be balanced: ");
  // Serial.println(hCBalgo.NODE);
  // Serial.println("Direction :");
  // Serial.println(hCBalgo.DIR);
  // Serial.println("*****************************************************");


  
  //  // reply only when you receive data:
  //     Serial.print(0xfd,HEX);
  //     int incomingByte = 0; // for incoming serial data
  //     if (Serial.available() > 0) {
  //       Serial.readBytes(hBLE.BLE_buffer,hBLE.BLEbyteCount);
  //       // Serial.println(sizeof(BLE_Data)/sizeof(BLE_Data[0]));

  //       dataConvertBLEVoltages(&hBLE);
  //       HAL_Delay(1000);
  //     }

  // getBLEdata(&hCBalgo,&hBLE);
}




void getBLEdata(CBalgo *hCBalgo,BLE *hBLE){
    //1,f,1793,1559,152,2,f,1788,1548,151,3,f,1788,1447,139,4,f,1792,1545,151,5,f,1799,1476,142,6,f,1794,1548,152,7,f,1793,1486,145,@,
    hBLE->BLE_buffer[0] = BMS_DATA_AVERAGE_REQ;
    if(HAL_UART_Transmit(&huart3,hBLE->BLE_buffer,1,10) == HAL_OK){
        if (HAL_UART_Receive (&huart3, hBLE->BLE_buffer,hBLE->BLEbyteCount, 10)==HAL_OK)
        {
            dataConvertBLE(hCBalgo,hBLE);
        }
        
    }
}



void dataConvertBLE(CBalgo *hCBalgo,BLE *hBLE){
        // Check the last terionation charecter to make sure all the data has recived 
        if(hBLE->BLE_buffer[126]=='@'){
                uint8_t count = 0;
                for(uint8_t i=0;i< hBLE->BLEbyteCount;i++){
                    
                    if (hBLE->BLE_buffer[i]=='f')
                    {
                        hBLE->VBAT[count]=(int16_t)((hBLE->BLE_buffer[i+2]<<8) + hBLE->BLE_buffer[i+3]);
                        count++;
                    }
                    
                }
        }
}


void dataConvertBLEVoltages(BLE *hBLE){
  // Check the last terionation charecter to make sure all the data has recived 
                uint8_t count = 0;
                for(uint8_t i=0;i< hBLE->BLEbyteCount+1;i++){
                    // 0x66 is the vale of the 'f'
                    if (hBLE->BLE_buffer[i]==0x66)
                    {
                        hBLE->VBAT[count]=(int16_t)((hBLE->BLE_buffer[i+2]<<12) | (hBLE->BLE_buffer[i+3]<<8) | (hBLE->BLE_buffer[i+4]<<4) | (hBLE->BLE_buffer[i+5]));
                        count++;
                    }
                    
                }
                if( hBLE->VBAT[0]==1795){
                  Serial.print("data detected");
                }
                count=0;
        if(hBLE->BLE_buffer[126]==0x64){
        }
}