/*
 * Lab3_Process.h
 *
 *  Created on: Oct 22, 2024
 *      Author: HP WORK
 */

#ifndef INC_LAB3_PROCESS_H_
#define INC_LAB3_PROCESS_H_

#include "main.h"
#include "MyLED7SEG.h"
//#include "timer.h"

void Lab3_Init(void);
void Lab3_FSM_Traffic(void);
void Lab3_FSM_Input_Process(void);

void Enable_led7seg(int num);
void Update_Display(uint8_t main, uint8_t sub);
void Scan_Display(uint8_t index);

void Mode_1(void);
void Mode_2(void);
void Mode_3(void);
void Mode_4(void);

#endif /* INC_LAB3_PROCESS_H_ */
