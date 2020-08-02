/*
 * sch.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Admin
 */

#ifndef OS_SCH_H_
#define OS_SCH_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../std_Types.h"

#define SCH_MAX_TASKS (3)

#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

#define RETURN_NORMAL (tByte) 0
#define RETURN_ERROR (tByte) 1

typedef struct
{
// Pointer to the task (must be a 'void (void)' function)
void (* pTask)(void);
// Delay (ticks) until the function will (next) be run
// - see SCH_Add_Task() for further details
tWord Delay;
// Interval (ticks) between subsequent runs.
// - see SCH_Add_Task() for further details
tWord Period;
// Incremented (by scheduler) when task is due to execute
tByte RunMe;

tWord Repeat;
} sTask;

void SCH_Init_T1(void);
void SCH_Start(void);

tByte SCH_Add_Task(void (* pFunction)(), const tWord DELAY, const tWord PERIOD, const tWord Repeat);
tByte SCH_Delete_Task(const tByte TASK_INDEX);

void SCH_Report_Status(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Go_To_Sleep();

#endif /* OS_SCH_H_ */
