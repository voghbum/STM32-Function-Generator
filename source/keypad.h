/*
 * keypad.h
 *
 *  Created on: Nov 15, 2021
 *      Author: huseyinasci
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stm32g0xx.h"

#define R1_p			(GPIOB)
#define R1_ODR			((uint16_t) (0x10))

#define R2_p			(GPIOB)
#define R2_ODR			((uint16_t) (0x20))

#define R3_p			(GPIOB)
#define R3_ODR			((uint16_t) (0x200))

#define R4_p			(GPIOA)
#define R4_ODR			((uint16_t) (0x100))

#define C1_p			(GPIOB) //PB8
#define C1_IDR			((uint16_t) (0x100))

#define C2_p			(GPIOB) //PB2
#define C2_IDR			((uint16_t) (0x4))

#define C3_p			(GPIOB) //PB0
#define C3_IDR			((uint16_t) (0x1))

#define C4_p			(GPIOA) //PA9
#define C4_IDR			((uint16_t) (0x200))

typedef enum keypadButton{keypadBut0 = 0, keypadBut1 = 1, keypadBut2 = 2, keypadBut3 = 3, keypadBut4 = 4,
	keypadBut5 = 5, keypadBut6 = 6, keypadBut7 = 7, keypadBut8 = 8, keypadBut9 = 9, keypadButA = 10,
	keypadButB = 11, keypadButC = 12, keypadButD = 13, keypadButHash = 14, keypadButAst = 15, none = -1} keypadBut_t;

void KEY_setRCC();
void KEY_setMODER();
void KEY_setInterrupt();
static void KEY_clearAllRows();
static void KEY_setAllRows();
static void KEY_setRow(uint8_t key);
keypadBut_t KEY_detectButton();


#endif /* KEYPAD_H_ */
