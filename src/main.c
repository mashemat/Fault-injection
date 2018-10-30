/* @file main.c
 	 *
 * @description
	 * This file contains the main program to be executed by the microcontroller STM32.
	 * All the other routines and functions are described in those header files whose name
	 * begins with 'MY_'.
 */

/* Discovery headers */
#include "stm32f3xx.h"				// Header for generic stm32f3 micro
#include "stm32f3_discovery.h"		// Header for the stm32f3-Discovery board

/* FreeRTOS headers */
#include "FreeRTOS.h"				// Useful for FreeRTOS compilation
#include "list.h"					// List file of FreeRTOS
#include "task.h"					// Task file of FreeRTOS
#include "queue.h"					// Queue file of FreeRTOS
#include "semphr.h"					// Semaphore file of FreeRTOS

/* My headers */
#include "MY_global_handlers.h"		// Global handler used through the program
#include "MY_useful_functions.h"	// Useful functions are defined here
#include "MY_hardware_config.h"		// HW configuration for the micro using HAL
#include "MY_fault_injector.h"		// Injector function is defined here
#include "MY_os_threads.h"			// Threads to be executed in parallel are defined here

/* GLOBALS */
extern SemaphoreHandle_t 	UART_mutex;
extern SemaphoreHandle_t    MEMS_mutex;
extern volatile int			NMR;
extern volatile int			NUW;
extern float				MEMS_GYRO_xyz[3];
extern short int 			MEMS_ACCELERO_xyz[3];

/* Standard C library headers */
#include "string.h"

/* ****** MAIN ************************************************************/
int main(void)
{
	HAL_Init();
	HC_SystemClock_Config();		// Configure System clock

	/* Distributing clock */
	__HAL_RCC_USART1_CLK_ENABLE();	// Enable Clock for USART1
	__HAL_RCC_TIM2_CLK_ENABLE();	// Enable Clock for TIM2
	__HAL_RCC_GPIOC_CLK_ENABLE();	// Enable Clock for GPIOC
	__HAL_RCC_GPIOE_CLK_ENABLE();	// Enable Clock for GPIOE

	/* Configuring hardware */
	HC_LED3_Config();				// Configure LED3 (NORD) as output
	HC_UART1_Config();				// Configure UART and related pins for PC communication
	HC_TIM2_Config();				// Configure general purpose Timer2
	HC_GYRO_Config();				// Configure automatically the gyroscope
	HC_ACCELERO_Config();			// Configure automatically the accelerometer

	/* Initializing globals */
	NMR = 0;							  // Initialize the NMR to zero
	NUW = 0;							  // Initialize the NUW to zero
	MEMS_GYRO_xyz[0] = 0;
	MEMS_GYRO_xyz[1] = 0;
	MEMS_GYRO_xyz[2] = 0;
	MEMS_ACCELERO_xyz[0] = 0;
	MEMS_ACCELERO_xyz[1] = 0;
	MEMS_ACCELERO_xyz[2] = 0;
	UART_mutex = xSemaphoreCreateMutex(); // Initialize mutex
	MEMS_mutex = xSemaphoreCreateMutex(); // Initialize mutex

	/* Creating Tasks */
	xTaskCreate(OT_myThread_MEMS,"MEMS11",128,"MEMS11",2,NULL);
	xTaskCreate(OT_myThread_MEMS,"MEMS12",128,"MEMS12",2,NULL);
	/*xTaskCreate(OT_myThread_MEMS,"MEMS21",128,"MEMS21",2,NULL);
	xTaskCreate(OT_myThread_MEMS,"MEMS22",128,"MEMS22",2,NULL);
	xTaskCreate(OT_myThread_MEMS,"MEMS31",128,"MEMS31",3,NULL);
	xTaskCreate(OT_myThread_MEMS,"MEMS32",128,"MEMS32",3,NULL);
	xTaskCreate(OT_myThread_UART,"UART41",512,(void*)"UART41",4,NULL);
	xTaskCreate(OT_myThread_UART,"UART42",512,(void*)"UART42",4,NULL);
	xTaskCreate(OT_myThread_UART,"UART51",512,(void*)"UART51",5,NULL);
	xTaskCreate(OT_myThread_UART,"UART52",512,(void*)"UART52",5,NULL);*/
	xTaskCreate(OT_myThread_UART,"UART61",512,(void*)"UART61",6,NULL);
	xTaskCreate(OT_myThread_UART,"UART62",512,(void*)"UART62",6,NULL);

	/* Starting up the system */
	UF_OSStart();							// Send some information about system over the UART

	/* Enabling interrupts */
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);	// TIM2 interrupt has maximum priority
	HAL_NVIC_EnableIRQ(TIM2_IRQn);			// Enable TIM2 interrupt

	/* Starting scheduler */
	vTaskStartScheduler();

	for(;;);
}
/* ****** END MAIN ********************************************************/
