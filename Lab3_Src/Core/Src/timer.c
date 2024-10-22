/*
 * timer.c
 *
 *  Created on: Oct 22, 2024
 *      Author: HP WORK
 */


#include "main.h"
#include "input_reading.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) {
		button_reading();
	}
}
