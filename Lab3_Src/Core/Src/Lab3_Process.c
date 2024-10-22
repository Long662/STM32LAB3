/*
 * Lab3_Process.c
 *
 *  Created on: Oct 22, 2024
 *      Author: HP WORK
 */
//----------------------------------------------
// Init somethings for LAB3
//----------------------------------------------
#include "Lab3_Process.h"

LED7SEG_Name SEG1;
LED7SEG_Name SEG2;

void Lab3_Init(void){
	// Turn off all traffic led
	HAL_GPIO_WritePin(GPIOA, RED_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, YELLOW_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GREEN_0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, RED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, YELLOW_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_SET);

	// Turn off 4 led 7SEG
	HAL_GPIO_WritePin(GPIOA, EN1_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, EN1_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, EN2_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, EN2_2_Pin, GPIO_PIN_SET);

	// Init 2 led 7seg for 2 road
	LED7SEG_Init(&SEG1,	GPIOB, SEG1_0_Pin,
						GPIOB, SEG1_1_Pin,
						GPIOB, SEG1_2_Pin,
						GPIOB, SEG1_3_Pin,
						GPIOB, SEG1_4_Pin,
						GPIOB, SEG1_5_Pin,
						GPIOB, SEG1_6_Pin);
	LED7SEG_Init(&SEG2,	GPIOB, SEG2_0_Pin,
						GPIOB, SEG2_1_Pin,
						GPIOB, SEG2_2_Pin,
						GPIOB, SEG2_3_Pin,
						GPIOB, SEG2_4_Pin,
						GPIOB, SEG2_5_Pin,
						GPIOB, SEG2_6_Pin);
}

//----------------------------------------------
// Process in LAB3
//----------------------------------------------
int Main_led_buffer[2];
int Sub_led_buffer[2];

void Update_Display(uint8_t main, uint8_t sub){
	// Update main road index
	Main_led_buffer[0] = main / 10;
	Main_led_buffer[1] = main % 10;
	// Update sub road index
	Sub_led_buffer[0] = sub / 10;
	Sub_led_buffer[1] = sub % 10;
}

void Enable_led7seg(int num){
	switch (num){
		case 0: HAL_GPIO_WritePin(EN1_1_GPIO_Port, EN1_1_Pin, RESET);
				HAL_GPIO_WritePin(EN1_2_GPIO_Port, EN1_2_Pin, SET);
				HAL_GPIO_WritePin(EN2_1_GPIO_Port, EN2_1_Pin, RESET);
				HAL_GPIO_WritePin(EN2_2_GPIO_Port, EN2_2_Pin, SET);
				break;
		case 1: HAL_GPIO_WritePin(EN1_1_GPIO_Port, EN1_1_Pin, SET);
				HAL_GPIO_WritePin(EN1_2_GPIO_Port, EN1_2_Pin, RESET);
				HAL_GPIO_WritePin(EN2_1_GPIO_Port, EN2_1_Pin, SET);
				HAL_GPIO_WritePin(EN2_2_GPIO_Port, EN2_2_Pin, RESET);
				break;
	}
}

void Scan_Display(uint8_t index) {
	Enable_led7seg(index);
	LED7SEG_Write(&SEG1, Main_led_buffer[index]);
	LED7SEG_Write(&SEG2, Sub_led_buffer[index]);
}
//----------------------------------------------
// Mode running in LAB3
//----------------------------------------------
// Init Duration for each led in the main road (second)
uint8_t RED_Dur_count = 2;
uint8_t YELLOW_Dur_count = 2;
uint8_t GREEN_Dur_count = 2;
uint8_t Main_Dur_count = 2; // The main road will act Red first
uint8_t Sub_Dur_count = 2; // The sub road will act Green first

enum Led_state{RED, GREEN, YELLOW};
enum Led_state Main_led = RED;
enum Led_state Sub_led = GREEN;

void Mode_1(void){
	Main_Dur_count--;
	Sub_Dur_count--;
	// FSM for main led
	switch (Main_led) {
		case RED:
			// Main road
			HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(YELLOW_0_GPIO_Port, YELLOW_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, GPIO_PIN_SET);
			// Times to change state
			if (Main_Dur_count <= 0) {
				Main_led = GREEN;
				Main_Dur_count = GREEN_Dur_count;
			}
			break;
		case YELLOW:
			// Main road
			HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW_0_GPIO_Port, YELLOW_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, GPIO_PIN_SET);
			// Time to change states
			if (Main_Dur_count <= 0) {
				Main_led = RED;
				Main_Dur_count = RED_Dur_count;
			}
			break;
		case GREEN:
			// Main road
			HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW_0_GPIO_Port, YELLOW_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, GPIO_PIN_RESET);
			// Times to change state
			if (Main_Dur_count <= 0) {
				Main_led = YELLOW;
				Main_Dur_count = YELLOW_Dur_count;
			}
			break;
		default: // DO NOT THING
			break;
	}
	// FSM for sub led
	switch (Sub_led) {
		case RED:
			// Main road
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(YELLOW_1_GPIO_Port, YELLOW_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, GPIO_PIN_SET);
			// Times to change state
			if (Sub_Dur_count <= 0) {
				Sub_led = GREEN;
				Sub_Dur_count = GREEN_Dur_count;
			}
			break;
		case YELLOW:
			// Main road
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW_1_GPIO_Port, YELLOW_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, GPIO_PIN_SET);
			// Time to change states
			if (Sub_Dur_count <= 0) {
				Sub_led = RED;
				Sub_Dur_count = RED_Dur_count;
			}
			break;
		case GREEN:
			// Main road
			HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(YELLOW_1_GPIO_Port, YELLOW_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, GPIO_PIN_RESET);
			// Times to change state
			if (Sub_Dur_count <= 0) {
				Sub_led = YELLOW;
				Sub_Dur_count = YELLOW_Dur_count;
			}
			break;
		default: // DO NOT THING
			break;
	}
	Update_Display(Main_Dur_count, Sub_Dur_count);
}
