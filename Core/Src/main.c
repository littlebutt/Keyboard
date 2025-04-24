/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include "atk_md0430_touch.h"
#include "delay.h"

#include "display.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PI (float)(3.1415926)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SRAM_HandleTypeDef hsram4;

/* USER CODE BEGIN PV */
static float cube[8][3] = {
  {-32, -32, -32},
  {-32, +32, -32},
  {+32, +32, -32},
  {+32, -32, -32},
  {-32, -32, +32},
  {-32, +32, +32},
  {+32, +32, +32},
  {+32, -32, +32}
};

static uint8_t line_id[24] = {
  1, 2, 2, 3,
  3, 4, 4, 1,
  5, 6, 6, 7,
  7, 8, 8, 5,
  8, 4, 7, 3,
  6, 2, 5, 1
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FSMC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
 * @brief       计算矩阵乘法
 * @param       a      : 矩阵a
 *              b[3][3]: 矩阵b
 * @retval      计算结果
 */
static float *demo_matconv(float *a, float b[3][3])
{
    float res[3];
    uint8_t res_index;
    uint8_t a_index;
    
    for (res_index=0; res_index<3; res_index++)
    {
        res[res_index] = b[res_index][0] * a[0] + b[res_index][1] * a[1] + b[res_index][2] * a[2];
    }
    
    for (a_index=0; a_index<3; a_index++)
    {
        a[a_index] = res[a_index];
    }
    
    return a;
}

/**
 * @brief       旋转向量
 * @param       point: 需要旋转的向量
 *              x    : X轴旋转量
 *              y    : Y轴旋转量
 *              z    : Z轴旋转量
 * @retval      计算结果
 */
static void demo_rotate(float *point, float x, float y, float z)
{
    float rx[3][3];
    float ry[3][3];
    float rz[3][3];
    
    x /= PI;
    y /= PI;
    z /= PI;
    
    rx[0][0] = cos(x);
    rx[0][1] = 0;
    rx[0][2] = sin(x);
    rx[1][0] = 0;
    rx[1][1] = 1;
    rx[1][2] = 0;
    rx[2][0] = -sin(x);
    rx[2][1] = 0;
    rx[2][2] = cos(x);
    
    ry[0][0] = 1;
    ry[0][1] = 0;
    ry[0][2] = 0;
    ry[1][0] = 0;
    ry[1][1] = cos(y);
    ry[1][2] = -sin(y);
    ry[2][0] = 0;
    ry[2][1] = sin(y);
    ry[2][2] = cos(y);
    
    rz[0][0] = cos(z);
    rz[0][1] = -sin(z);
    rz[0][2] = 0;
    rz[1][0] = sin(z);
    rz[1][1] = cos(z);
    rz[1][2] = 0;
    rz[2][0] = 0;
    rz[2][1] = 0;
    rz[2][2] = 1;
    
    demo_matconv(demo_matconv(demo_matconv(point, rz), ry), rx);
}

/**
 * @brief       演示立方体3D旋转
 * @param       无
 * @retval      无
 */
static void demo_show_cube(void)
{
    uint8_t point_index;
    uint8_t line_index;
    static uint16_t x = 240;
    static uint16_t y = 441;
    static atk_md0430_touch_point_t point[1];
    
    /* ATK-MD0430模块触摸扫描 */
    if (atk_md0430_touch_scan(point, sizeof(point) / sizeof(point[0])) == sizeof(point) / sizeof(point[0]))
    {
        if ((point[0].x > 56) && (point[0].x < (atk_md0430_get_lcd_width() - 56)) && (point[0].y > 138) && (point[0].y < (atk_md0430_get_lcd_height() - 56)))
        {
            x = point[0].x;
            y = point[0].y;
        }
    }
    
    for (point_index=0; point_index<8; point_index++)
    {
        demo_rotate(cube[point_index], 0.05f, 0.03f, 0.02f);
    }
    
    for (line_index=0; line_index<24; line_index+=2)
    {
        /* ATK-MD0430模块LCD画线段 */
        atk_md0430_draw_line(   x + cube[line_id[line_index] - 1][0],
                                y + cube[line_id[line_index] - 1][1],
                                x + cube[line_id[line_index + 1] - 1][0],
                                y + cube[line_id[line_index + 1] - 1][1],
                                ATK_MD0430_BLUE);
    }
    
    delay_ms(20);
    
    atk_md0430_fill(x - 56, y - 56, x + 56, y + 56, ATK_MD0430_WHITE);
}
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
  display_ctx ctx = display_init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  delay_init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
  uint8_t ret;
 
  ret = atk_md0430_init();
  if (ret != 0)
  {
      while (1)
      {
          delay_ms(200);
      }
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);

  display_layout(ctx);
  while (1)
  {
    // demo_show_cube();
    lv_timer_handler();
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, ATK_MD0430_TOUCH_IIC_SDA_Pin|ATK_MD0430_TOUCH_TCS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ATK_MD0430_BL_Pin|ATK_MD0430_TOUCH_IIC_SCL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : ATK_MD0430_TOUCH_IIC_SDA_Pin */
  GPIO_InitStruct.Pin = ATK_MD0430_TOUCH_IIC_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ATK_MD0430_TOUCH_IIC_SDA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ATK_MD0430_TOUCH_PEN_Pin */
  GPIO_InitStruct.Pin = ATK_MD0430_TOUCH_PEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ATK_MD0430_TOUCH_PEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ATK_MD0430_BL_Pin ATK_MD0430_TOUCH_IIC_SCL_Pin */
  GPIO_InitStruct.Pin = ATK_MD0430_BL_Pin|ATK_MD0430_TOUCH_IIC_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ATK_MD0430_TOUCH_TCS_Pin */
  GPIO_InitStruct.Pin = ATK_MD0430_TOUCH_TCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ATK_MD0430_TOUCH_TCS_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};
  FSMC_NORSRAM_TimingTypeDef ExtTiming = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM4 memory initialization sequence
  */
  hsram4.Instance = FSMC_NORSRAM_DEVICE;
  hsram4.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram4.Init */
  hsram4.Init.NSBank = FSMC_NORSRAM_BANK4;
  hsram4.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram4.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram4.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram4.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram4.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram4.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram4.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram4.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram4.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram4.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;
  hsram4.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram4.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 0x00;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 0x0f;
  Timing.BusTurnAroundDuration = 0x00;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */
  ExtTiming.AddressSetupTime = 0x00;
  ExtTiming.AddressHoldTime = 15;
  ExtTiming.DataSetupTime = 0x01;
  ExtTiming.BusTurnAroundDuration = 0;
  ExtTiming.CLKDivision = 16;
  ExtTiming.DataLatency = 17;
  ExtTiming.AccessMode = FSMC_ACCESS_MODE_A;

  if (HAL_SRAM_Init(&hsram4, &Timing, &ExtTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
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
