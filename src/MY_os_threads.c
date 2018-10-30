#include "MY_os_threads.h"
#include "MY_global_handlers.h"
#include "MY_useful_functions.h"

/* Discovery headers */
#include "stm32f3xx.h"
#include "stm32f3_discovery.h"
#include "stm32f3_discovery_gyroscope.h"
#include "stm32f3_discovery_accelerometer.h"

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Standard C library headers */
#include "stdio.h"
#include "string.h"

/* GLOBALS */
extern int 				MEMS_GYRO_enabled;
extern int 				MEMS_ACCELERO_enabled;
extern volatile int		NMR;
extern volatile int		NUW;
extern SemaphoreHandle_t 	UART_mutex;
extern SemaphoreHandle_t    MEMS_mutex;


/* ****** FUNCTIONS DEFINITION ************************************************************/

void OT_myThread_MEMS(void *params)
{
	while(1)
	{
		if(xSemaphoreTake(MEMS_mutex,(TickType_t)10)==pdTRUE){
			/* BEGIN of critical section for MEMS */
			if(MEMS_GYRO_enabled==1)
			{
				BSP_GYRO_GetXYZ(MEMS_GYRO_xyz);
			}
			if(MEMS_ACCELERO_enabled==1)
			{
				BSP_ACCELERO_GetXYZ(MEMS_ACCELERO_xyz);
			}
			NMR++;
			/* END of critical section*/
			xSemaphoreGive(MEMS_mutex);
		}
		vTaskDelay(10/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
void OT_myThread_UART(void *params)
{
	while(1)
	{
		char buffer[80];
		sprintf(buffer,"%s\t%s:\t%d\t%d\t%d\t%s:\t%d\t%d\t%d\n",(char*)params,"GYRO",
										 (int)MEMS_GYRO_xyz[0],
										 (int)MEMS_GYRO_xyz[1],
										 (int)MEMS_GYRO_xyz[2],
										 "ACCEL",
										 (int)MEMS_ACCELERO_xyz[0],
										 (int)MEMS_ACCELERO_xyz[1],
										 (int)MEMS_ACCELERO_xyz[2]);
		if(xSemaphoreTake(UART_mutex,(TickType_t)10)==pdTRUE){
			/* BEGIN of critical section for UART */
			HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);
			UF_delay(10);
			NUW++;
			/* END of critical section*/
			xSemaphoreGive(UART_mutex);
		}
		vTaskDelay(50/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
