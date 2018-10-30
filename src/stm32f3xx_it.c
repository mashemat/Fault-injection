/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "MY_useful_functions.h"
#include "MY_global_handlers.h"
#include "MY_useful_functions.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3_discovery.h"
#include "string.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f3xx_it.h"

/* GLOBALS */
extern TIM_HandleTypeDef  TIM2_HANDLE;
extern UART_HandleTypeDef UART1_HANDLE;
extern volatile int	      TIM2_CNT;
extern volatile int		  ETAF;
extern volatile int		  NMR;
extern volatile int		  NUW;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}

void Default_Handler_C(void)
{
	ETAF = __HAL_TIM_GET_COUNTER(&TIM2_HANDLE);
	char buffer[512];
	sprintf(buffer,"\n\n%s\n","---> Injection caused a system crash");
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);
	sprintf(buffer,"CNT:\t%d\tWhen the injection was done.\n",TIM2_CNT);
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);
	sprintf(buffer,"ETAF:\t%d\tTime elapsed before calling this handler.\n",ETAF);
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);
	sprintf(buffer,"NMR:\t%d\tNumber of MEMS reads.\n",NMR);
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);
	sprintf(buffer,"NUW:\t%d\tNumber of UART writes.\n",NUW);
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);

	/* Signal a critical error in the OS forever with all LEDs blinking */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.Pin = LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN | LED7_PIN | LED8_PIN | LED9_PIN | LED10_PIN;
	gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_struct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE,&gpio_struct);
	while(1){
		HAL_GPIO_WritePin(GPIOE, LED4_PIN | LED5_PIN | LED8_PIN | LED9_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, LED3_PIN | LED6_PIN | LED7_PIN | LED10_PIN, GPIO_PIN_RESET);
		UF_delay(750);
		HAL_GPIO_WritePin(GPIOE, LED4_PIN | LED5_PIN | LED8_PIN | LED9_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, LED3_PIN | LED6_PIN | LED7_PIN | LED10_PIN, GPIO_PIN_SET);
		UF_delay(750);
	}
}
