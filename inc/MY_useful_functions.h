/* @file MY_useful_functions.h
 	 *
 * @description
 	 * Here there are some self-defined functions that can be used when needed.
 */

#ifndef _MY_US_FUNCT_
#define _MY_US_FUNCT_


void UF_delay(int factor);				// Very primitive delay function
void UF_TasksDump(char *buffer);		// Creates a dump about tasks on the system (ready, suspended and delayed)
void UF_TasksListDump(char *buffer);	// Tasks list dump: information about instantiated tasks, their TCB and stacks
void UF_OSStart(void);					// Startup of the OS fashion

#endif
