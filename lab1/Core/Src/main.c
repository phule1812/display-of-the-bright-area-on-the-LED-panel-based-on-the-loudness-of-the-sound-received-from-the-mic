/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "P10.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t data[16];
volatile Pixel pix[3];
volatile uint8_t Tim2Count;
extern uint16_t AdcValUsred;
Pixel pixel;
int level = 0;
uint16_t level_led = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  pix[0].x = 10;
  pix[0].y = 2;
  pix[1].x = 10;
  pix[1].y = 4;
 void drawPoint0(int x, int y){
	 pixel.x = x;
	 pixel.y = y;
	 clearScreen((uint8_t*)&data);
	 drawPixel(pixel, (uint8_t*)&data, P10AB_11);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);

	 HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);

	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
	 HAL_Delay(0.1);
 }

 void drawPoint1(int x, int y){
	 pixel.x = x;
	 pixel.y = y;
	 clearScreen((uint8_t*)&data);
	 drawPixel(pixel, (uint8_t*)&data, P10AB_10);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);

	 HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);

	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
	 HAL_Delay(0.2);
 }

 void drawPoint2(int x, int y){
	 pixel.x = x;
	 pixel.y = y;
	 clearScreen((uint8_t*)&data);
	 drawPixel(pixel, (uint8_t*)&data, P10AB_01);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);

	 HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);

	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
	 HAL_Delay(0.2);
 }
 void drawPoint3(int x, int y){
	 pixel.x = x;
	 pixel.y = y;
	 clearScreen((uint8_t*)&data);
	 drawPixel(pixel, (uint8_t*)&data, P10AB_00);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);

	 HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);

	 HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
	 HAL_Delay(0.2);
 }

 void drawPoint(int x, int y){
	 if (y == 0 || y == 4 || y == 8|| y == 12 ){
		 drawPoint0(x, y);
	 }
	 else if (y == 1 || y == 5 || y == 9 || y == 13){
		 drawPoint1(x, y);
	 }
	 else if (y == 2 ||  y == 6 || y == 10 || y == 14){
		 drawPoint2(x, y);
	 }
	 else if (y == 3 || y == 7 || y == 11 || y == 15){
		 drawPoint3(x, y);
	 }
 }

 void drawSquare_edge(int lenght){
	 int x0 = 15;
	 int y0 = 7;
	 int k = 1 - lenght/2;
	 int x = x0 + k;
	 int y = y0 + k;
	 drawPoint(x, y);
	 for (uint8_t  i = 0; i < lenght; i ++){
		 drawPoint(x, y + i);
		 drawPoint(x + i, y);
	 }
	 for (uint8_t  i = 0; i < lenght; i ++){
		 drawPoint(x+i, y + lenght);
		 drawPoint(x + lenght, y+i);
	 }
	 drawPoint(x+lenght, y+lenght);
//	 drawPoint(x, y + lenght - 1);
//	 drawPoint(x + lenght - 1, y + lenght - 1);
//	 drawPoint(x + lenght - 1, y);
 }

 void drawSquare(int lenght){
	 for (uint8_t i = 0; i <= lenght; i++){
		 drawSquare_edge(i);
	 }
 }

  while (1)
  {

// P10AB_11 : 0, 4, 8, 12 ; P10AB_01 : 1, 5, 9, 13; P10AB_10 : 2, 6, 10, 14; P10AB_00 : 3, 7, 11, 15

//		  clearScreen((uint8_t*)&data);
//		  drawRect(pix[0], pix[1], (uint8_t*)&data, P10AB_11);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
//
//		  HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);
//
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
//		  HAL_Delay(1);

//		  clearScreen((uint8_t*)&data);
//		  drawRect(pix[0], pix[1], (uint8_t*)&data, P10AB_01);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
//
//		  HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);
//
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
//		  HAL_Delay(1);
//
//		  clearScreen((uint8_t*)&data);
//		  drawRect(pix[0], pix[1], (uint8_t*)&data, P10AB_10);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
//
//		  HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);
//
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
//		  HAL_Delay(1);
//
//
//		  clearScreen((uint8_t*)&data);
//		  drawPixel(pix[1], (uint8_t*)&data, P10AB_11);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
//
//		  HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 16, 10);
//
//		  HAL_GPIO_WritePin(GPIOC, SCLK_Pin, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOC, nOE_Pin, GPIO_PIN_SET);
//		  HAL_Delay(1);


//	  drawPoint(15, 7);
//	  drawPoint(16, 7);
//	  drawPoint(15, 8);
//	  drawPoint(16, 8);
	  uint8_t Level[5] = {2,6,4,8,10};

//	  for (uint8_t i = 0; i <= 5; i ++){
//		  drawSquare(Level[i]);
//		  HAL_Delay(10000);
//	  }

	  level = ((13*AdcValUsred/1900) - 189/19);
//	  level_led = level + (1);

	  drawSquare(level-2);

//
//	  for (uint8_t i = 2 ; i < 16; i = i +2 ){
//		  drawSquare(i);
//		  HAL_Delay(1000);
//	  }

//	  for(uint8_t i = 0; i < 15; i ++){
//		  drawPoint(15, i);
//		  HAL_Delay(100);
//	  }



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
