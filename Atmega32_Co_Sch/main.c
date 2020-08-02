/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Admin
 */

#include "main.h"

void LED_Flash_Update1(void);
void LED_Flash_Update2(void);
void LED_Flash_Update3(void);

int main(void) {

	DDRD |= (1 << PD7) | (1 << PD6) | (1 << PD5);

	SCH_Init_T1();

	SCH_Add_Task(LED_Flash_Update1, 0, 1, 50);
	SCH_Add_Task(LED_Flash_Update2, 0, 1, 500);
	SCH_Add_Task(LED_Flash_Update3, 0, 1, 1000);

	SCH_Start();

	while (1) {
		SCH_Dispatch_Tasks();
	}
	return 0;
}

void LED_Flash_Update1(void) {
	PORTD ^= (1 << PD7);
}
void LED_Flash_Update2(void) {
	PORTD ^= (1 << PD6);
}
void LED_Flash_Update3(void) {
	PORTD ^= (1 << PD5);
}
