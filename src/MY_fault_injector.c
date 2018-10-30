#include "MY_fault_injector.h"
#include "MY_global_handlers.h"
#include "MY_useful_functions.h"

/* Discovery headers */
#include "stm32f3xx.h"
#include "stm32f3_discovery.h"

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"

/* Standard C library headers */
#include "string.h"

/* GLOBALS */
extern TIM_HandleTypeDef 	TIM2_HANDLE;
extern volatile int			TIM2_CNT;


/* ****** FUNCTIONS DEFINITION ************************************************************/

void FI_exec(void)
{
	static int InjFlag = 0;
	if(InjFlag==0)
	{
		TIM2_CNT = __HAL_TIM_GET_COUNTER(&TIM2_HANDLE);		// Save the counter when interrupt is called
		HAL_GPIO_WritePin(GPIOE, LED3_PIN,GPIO_PIN_SET);	// Turn on the LED3


		#if (FI_SELECT_TARGET == FIT_CURRENT_TCB)	/* Inject on the CURRENT TCB system variable */
		{

		}
		#elif (FI_SELECT_TARGET == FIT_KERNEL_LIST)
		{
			#if (FI_SELECT_LIST == FIT_RDY_LIST)	/* Inject on the READY TASKS LIST */
				OSList_t *FI_ListToInject = pxOSGetReadyTasksHandle();
			#elif (FI_SELECT_LIST == FIT_DLD_LIST)	/* Inject on the DELAYED TASKS LIST system variable */
				OSList_t *FI_ListToInject = pxOSGetDelayedTasksHandle();
			#elif (FI_SELECT_LIST == FIT_SUS_LIST)	/* Inject on the SUSPENDED TASKS LIST system variable */
				OSList_t *FI_ListToInject = pxOSGetSuspendedTasksHandle();
			#endif
			int prio_code = FI_PRIO_TARGET;
			int prio;
			/* INJECTION HAPPENS HERE */
			for(int i=0; i<7; i++)
			{
				prio = prio_code & (0x0001<<i);
				if(prio != 0)
				{
					//OSTCB_t *TCB_PT = (OSTCB_t*)(FI_ListToInject[i].pxIndex->pvOwner);
					//OSTCB_t *TCB_PT2= (OSTCB_t*)(FI_ListToInject[i].pxIndex->pxNext->pvOwner);

					/* ! ! Inject on the pointer to the next task in the list */
					FI_ListToInject[i].pxIndex->pxNext = (ListItem_t*)((size_t)(FI_ListToInject[i].pxIndex->pxNext)^0x00000001);
					//FI_ListToInject[i].pxIndex->pxNext = (ListItem_t*)((size_t)(FI_ListToInject[i].pxIndex->pxNext)^0x80000000);

					/* Inject on the pointer to the TCB */
					//FI_ListToInject[i].pxIndex->pvOwner = (OSTCB_t*)((size_t)(FI_ListToInject[i].pxIndex->pvOwner)^0x00000001);
					//FI_ListToInject[i].pxIndex->pvOwner = (OSTCB_t*)((size_t)(FI_ListToInject[i].pxIndex->pvOwner)^0x80000000);

					/* Inject on the pointer to Base of the Stack */
					//TCB_PT->pxStack = (StackType_t*)((size_t)(TCB_PT->pxStack)^0x00000001);
					//TCB_PT->pxStack = (StackType_t*)((size_t)(TCB_PT->pxStack)^0x80000000);

					/* Inject on the pointer to the Top of the Stack */
					//TCB_PT->pxTopOfStack = (StackType_t*)((size_t)(TCB_PT->pxTopOfStack)^0x00000001);
					//TCB_PT->pxTopOfStack = (StackType_t*)((size_t)(TCB_PT->pxTopOfStack)^0x80000000);
				}
			}
		}
	}
	InjFlag = 1;
	#endif
}
