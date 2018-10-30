/* @file MY_os_threads.h
 	 *
 * @description
 	 * Here there are the definitions of the threads that the RTOS must execute.
 	 * They are instantiated in the 'main' function, by calling the function xTskCreate.
 	 * Change them as you want, according to your needs.
 */

#ifndef _MY_OS_THREADS_
#define _MY_OS_THREADS_


void OT_myThread_UART(void *params);
void OT_myThread_MEMS(void *params);


#endif
