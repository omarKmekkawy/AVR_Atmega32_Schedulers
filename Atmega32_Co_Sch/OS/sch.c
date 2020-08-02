/*
 * sch.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Admin
 */

#include "sch.h"

// The task's array

sTask SCH_tasks_G[SCH_MAX_TASKS];
tByte Error_code_G;

void SCH_Init_T1(void) {

	tByte i;

	for (i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}

	TCCR1B |= (1 << WGM12); // enable CTC and no prescaler
	TCNT1 = 0;
	OCR1A = 7999; // Auto reload value
	TIMSK |= (1 << OCIE1A); // enable overflow interrupt flag
	TCCR1B |= (1 << CS10); // Enable the timer's clock with no prescaler
}

void SCH_Start(void) {
	sei(); // Enable Global Interrupt
}


ISR (TIMER1_COMPA_vect)
{
	SCH_Update();
}

void SCH_Update(void) {
	tByte Index;
	//TF2 = 0; // Have to manually clear this.
// NOTE: calculations are in *TICKS* (not milliseconds)
	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
// Check if there is a task at this location
		if (SCH_tasks_G[Index].pTask) {
			if (SCH_tasks_G[Index].Delay == 0) {
// The task is due to run
				SCH_tasks_G[Index].RunMe += 1;	// Inc. the 'RunMe' flag
				if (SCH_tasks_G[Index].Repeat) {
// Schedule regular tasks to run again
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Repeat;
				}
			} else {
// Not yet ready to run: just decrement the delay
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

void SCH_Dispatch_Tasks(void) {
	tByte Index;

	// Dispatches (runs) the next task (if one is ready)
	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
		if (SCH_tasks_G[Index].RunMe > 0) {
			(*SCH_tasks_G[Index].pTask)();  // Run the task

			SCH_tasks_G[Index].RunMe -= 1;   // Reset / reduce RunMe flag

			// Periodic tasks will automatically run again
			// - if this is a 'one shot' task, remove it from the array
			if (SCH_tasks_G[Index].Period == 0) {
				SCH_Delete_Task(Index);
			}
		}
	}

	// Report system status
	SCH_Report_Status();

	// The scheduler enters idle mode at this point
	SCH_Go_To_Sleep();
}

tByte SCH_Add_Task(void (*pFunction)(), const tWord DELAY, const tWord PERIOD,const tWord Repeat) {
	tByte Index = 0;

	// First find a gap in the array (if there is one)
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
		Index++;
	}

	// Have we reached the end of the list?
	if (Index == SCH_MAX_TASKS) {
		// Task list is full
		//
		// Set the global error variable
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;

		// Also return an error code
		return SCH_MAX_TASKS;
	}

	// If we're here, there is a space in the task array
	SCH_tasks_G[Index].pTask = pFunction;

	SCH_tasks_G[Index].Delay = DELAY;
	SCH_tasks_G[Index].Repeat = Repeat;
	SCH_tasks_G[Index].Period = PERIOD;

	SCH_tasks_G[Index].RunMe = 0;

	return Index; // return position of task (to allow later deletion)
}

tByte SCH_Delete_Task(const tByte TASK_INDEX) {
	tByte Return_code;

	if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
		// No task at this location...
		//
		// Set the global error variable
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;

		// ...also return an error code
		Return_code = RETURN_ERROR;
	} else {
		Return_code = RETURN_NORMAL;
	}

	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;

	SCH_tasks_G[TASK_INDEX].RunMe = 0;

	return Return_code;       // return status
}

void SCH_Report_Status(void) {
#ifdef SCH_REPORT_ERRORS
	// ONLY APPLIES IF WE ARE REPORTING ERRORS
	// Check for a new error code
	if (Error_code_G != Last_error_code_G)
	{
		// Negative logic on LEDs assumed
		Error_port = 255 - Error_code_G;

		Last_error_code_G = Error_code_G;

		if (Error_code_G != 0)
		{
			Error_tick_count_G = 60000;
		}
		else
		{
			Error_tick_count_G = 0;
		}
	}
	else
	{
		if (Error_tick_count_G != 0)
		{
			if (--Error_tick_count_G == 0)
			{
				Error_code_G = 0; // Reset error code
			}
		}
	}
#endif
}

void SCH_Go_To_Sleep() {
	//PCON |= 0x01;    // Enter idle mode (generic 8051 version)

	// Entering idle mode requires TWO consecutive instructions
	// on 80c515 / 80c505 - to avoid accidental triggering
	//PCON |= 0x01;    // Enter idle mode (#1)
	//PCON |= 0x20;    // Enter idle mode (#2)
}
