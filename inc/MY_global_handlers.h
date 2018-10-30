/* @file MY_global_handlers.h
 	 *
 * @description
 	 * This file contains variables that are globally accessed by the program.
 	 * They are referred to, where they are needed, by using the keyword 'extern'.
 	 * These variables are defined in this way because they are used by different
 	 * tasks and function at the same time.
 */

#ifndef _MY_GLOB_HAND_
#define _MY_GLOB_HAND_


#include "stm32f3xx.h"

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define N_OF_TASKS 4

float				MEMS_GYRO_xyz[3];		// This contains the 3-D values provided by the gyro
short int			MEMS_ACCELERO_xyz[3];	// This contains the 3-D values provided by the accelero
int					MEMS_GYRO_enabled;		// Flag used to inform if the gyro has been initialized correctly
int					MEMS_ACCELERO_enabled;	// Flag used to inform if the accelero has been initialized correctly
TIM_HandleTypeDef 	TIM2_HANDLE;			// Handler to the TIMER2
UART_HandleTypeDef 	UART1_HANDLE;			// Handler to the UART1
SemaphoreHandle_t 	UART_mutex;				// Semaphore for UART synchronization
SemaphoreHandle_t   MEMS_mutex;				// Semaphore for MEMS access

volatile int		TIM2_CNT;				// Count of the timer
volatile int		ETAF;					// Time between fault injection and error handler call
volatile int		NMR;					// Number of MEMS reads since the startup
volatile int 		NUW;					// Number of UART writes since the startup


#endif
