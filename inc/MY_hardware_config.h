/* @file MY_hardware_config.h
 	 *
 * @description
 	 * Here you can find all the configuration of the STM32F3 micro.
 	 * All names are self-explanatory.
 	 *
 * @param HC_TIM_PERIOD
 	 * This constant is used at compile time to specify which is the maximum value that
 	 * the TIM2 must reach before raising an interrupt and resetting automatically: the higher,
 	 * the longer time interval between two interrupts.
 */

#ifndef _MY_HW_CONFIG_
#define _MY_HW_CONFIG_


#include "stm32f3xx.h"


#define HC_TIM_PERIOD 75000

void HC_SystemClock_Config(void);							// Configure the system clock
void HC_TIM2_Config(void);									// Configure the TIM 2
void HC_UART1_Config(void);									// Configure the UART 1 for communication with PC
void HC_LED3_Config(void);									// Configure LED_nord for the callback of the timer
void HC_GYRO_Config(void);									// Configure the embedded gyro
void HC_ACCELERO_Config(void);								// Configure the embedded accelero
void HAL_TIM_OC_ElapsedCallback(TIM_HandleTypeDef *htim);	// Callback for the timer interrupt


#endif
