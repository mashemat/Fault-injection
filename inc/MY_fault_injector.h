/* @file MY_fault_injector.h
 	 *
 * @description
	 * This Fault Injector is highly configurable at compile time and allows to choose
	 * what part of the OS has to be affected: according to the value assigned to
	 * 'FI_SELECT_TARGET', the 'FI_exec' function will adapt its behavior in order
	 * to damage the desired OS component.
	 * Before compiling, the programmer must setup the Fault Injector as its behavior
	 * cannot be modified dynamically at run time.
	 *
 * @param FI_SELECT_TARGET
	 * Possible configurations for select_target:
	 * 		FIT_CURRENT_TCB  : inject the currentTCB value; change the memory cell
	 * 						   pointed to by the currentTCB protected variable
	 * 		FIT_KERNEL_LIST  : inject one of the lists used by the kernel to manage the tasks
	 *
 * @param FI_SELECT_LIST
 	 * Possible configurations for select_list are:
	 *		FIT_RDY_LIST     : inject the list of ready tasks; this causes
	 *						   the most damages to the system as the list of pointers
	 *						   to the active tasks is modified pseudo-randomly
	 *		FIT_DLD_LIST     : inject the list of delayed tasks; as the previous configuration
	 *						   but only delayed tasks are affected
	 *		FIT_SUS_LIST     : inject the list of suspended tasks; as the previous configuration
	 *						   but only suspended tasks are affected
	 *
 * @param FI_PRIO_TARGET
	 * If FIT_RDY_LIST, has been chosen as target, choose which tasks have to be injected,
	 * on the basis of their priority. As the max priority is 7 and the minimum one is 0,
	 * choose 0x01 to inject ONLY the tasks with prio 0, 0x02 to inject ONLY the tasks with prio
	 * 1, 0x05 to inject BOTH the tasks with prio 0 and 2 ... look at the bits of these values to
	 * understand how they are chosen. Max value for this parameter is 0x7F (0b01111111).
 */

#ifndef _MY_FAULT_INJ_
#define _MY_FAULT_INJ_

/* Possible targets for the injection */
#define FIT_CURRENT_TCB  0
#define FIT_KERNEL_LIST  1

/* Possible target lists to inject */
#define FIT_RDY_LIST	   0
#define FIT_SUS_LIST	   1
#define FIT_DLD_LIST	   2

/* Configuration */
#define FI_SELECT_TARGET   FIT_KERNEL_LIST	// What do you want to inject
#define FI_SELECT_LIST	   FIT_RDY_LIST		// If you choose FIT_KERNEL_LIST, choose the list
#define FI_PRIO_TARGET 	   0x44				// Tasks to inject on the basis of the priority

void FI_exec(void);							// Function containing the injection code


#endif
