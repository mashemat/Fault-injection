#include "MY_useful_functions.h"
#include "MY_global_handlers.h"

/* Discovery headers */
#include "stm32f3xx.h"

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"

/* Standard C library headers */
#include "string.h"


/* ****** FUNCTIONS DEFINITION ************************************************************/

void UF_delay(int factor)
{
    for(int i=0; i<factor*1000; i++);
}
void UF_TasksDump(char *buffer)
{
	char *indexer = buffer;
	int nTasks = uxTaskGetNumberOfTasks();
	TaskStatus_t *activeTasks = pvPortMalloc(nTasks*sizeof(TaskStatus_t));

	uxTaskGetSystemState(activeTasks,nTasks,NULL);
	sprintf(indexer,"\n%s - %s\t%s\t%s\t%s\t%s\n","N",
												"TCBpt",
												"TID",
												"StackBasePt",
												"StackRes",
												"Name");
	indexer += strlen(indexer);
	for(int i=0; i<nTasks; i++)
	{
		sprintf(indexer,"%d - %p\t%d\t%p\t%d\t\t%s\n",i,
										   activeTasks[i].xHandle,
										   activeTasks[i].xTaskNumber,
										   activeTasks[i].pxStackBase,
										   activeTasks[i].usStackHighWaterMark,
										   activeTasks[i].pcTaskName);
		indexer += strlen(indexer);
	}
	*indexer = '\n';
	*(indexer+1) = '\0';
	vPortFree(activeTasks);
}
void UF_TasksListDump(char *buffer)
{
	char *indexer = buffer;
	sprintf(indexer,"\n%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t%s\n","PRIO",
												  	  	   "ContPt",
														   "NextPt",
														   "PrevPt",
														   "TCBPt",
														   "StackBase",
														   "StackTop");
	indexer += strlen(indexer);
	OSList_t *readyTasks= pxOSGetReadyTasksHandle();
	for(int i=1;i<7;i++)
	{
		ListItem_t *surferPt = readyTasks[i].pxIndex;
		for(int j=0;j<readyTasks[i].uxNumberOfItems;j++)
		{
			OSTCB_t *tcb_pt = (surferPt->pvOwner);
			sprintf(indexer,"%d\t%p\t%p\t%p\t%p\t%p\t%p\n",i,
										surferPt->pvContainer,
										surferPt->pxNext,
										surferPt->pxPrevious,
										surferPt->pvOwner,
										tcb_pt->pxStack,
										tcb_pt->pxTopOfStack);
			surferPt = surferPt->pxNext;
			indexer += strlen(indexer);
		}
	}
	*indexer = '-';
	*(indexer+1) = '\n';
	*(indexer+2) = '\0';
}
void UF_OSStart(void)
{
	char buffer[2048];

	sprintf(buffer,"%s","\n\n\n***************************************\n\n\n");
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
	sprintf(buffer,"%s","System starting up...\n\n");
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)buffer, strlen(buffer), 0xFFFF);

	UF_TasksDump(buffer);
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);

	UF_TasksListDump(buffer);
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)(buffer), strlen(buffer), 0xFFFF);

	sprintf(buffer,"%s","System up successfully.\nStarting Scheduler...\n\n");
	HAL_UART_Transmit(&UART1_HANDLE, (uint8_t*)buffer, strlen(buffer), 0xFFFF);

	UF_delay(2000);
}
