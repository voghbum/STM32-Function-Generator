/*
 * keypad.c
 *
 *  Created on: Nov 15, 2021
 *      Author: huseyinasci
 */

#include "keypad.h"

void KEY_setRCC() {
	// A ve B pinlerini aç
	RCC -> IOPENR |= (3U);
}

void KEY_setMODER() {
	// ROW AYARLARI
	R1_p -> MODER &= ~(3U << 4*2);
	R1_p -> MODER |= (1U << 4*2);

	R2_p -> MODER &= ~(3U << 5*2);
	R2_p -> MODER |= (1U << 5*2);

	R3_p -> MODER &= ~(3U << 9*2);
	R3_p -> MODER |= (1U << 9*2);

	R4_p -> MODER &= ~(3U << 8*2);
	R4_p -> MODER |= (1U << 8*2);

	//COLUMN (INPUT) AYARLARI
	C1_p -> MODER &= ~(3U << 8*2);
	C2_p -> MODER &= ~(3U << 2*2);
	C3_p -> MODER &= ~(3U << 0*2);
	C4_p -> MODER &= ~(3U << 9*2);

	//COLUMN PUPDR AYARLARI
	C1_p -> PUPDR |= (2U << 8*2);
	C2_p -> PUPDR |= (2U << 2*2);
	C3_p -> PUPDR |= (2U << 0*2);
	C4_p -> PUPDR |= (2U << 9*2);
}

void KEY_setInterrupt(){
	// C1 -> PB8
	EXTI -> EXTICR[2] |= (1U << 0*8);

	// C2 -> PB2
	EXTI -> EXTICR[0] |= (1U << 2*8);

	// C3 -> PB0
	EXTI -> EXTICR[0] |= (1U << 0*8);

	// C4 -> PA9
	EXTI -> EXTICR[2] |= (0U << 1*8);

	EXTI -> RTSR1 |= (1U << 9);
	EXTI -> RTSR1 |= (1U << 0);
	EXTI -> RTSR1 |= (1U << 2);
	EXTI -> RTSR1 |= (1U << 8);

	EXTI -> IMR1 |= (1U << 9);
	EXTI -> IMR1 |= (1U << 0);
	EXTI -> IMR1 |= (1U << 2);
	EXTI -> IMR1 |= (1U << 8);

	NVIC_SetPriority(EXTI0_1_IRQn, 0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	NVIC_SetPriority(EXTI2_3_IRQn, 0);
	NVIC_EnableIRQ(EXTI2_3_IRQn);

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

static void KEY_clearAllRows() {
	R1_p -> ODR &= (uint32_t) (~R1_ODR);
	R2_p -> ODR &= (uint32_t) (~R2_ODR);
	R3_p -> ODR &= (uint32_t) (~R3_ODR);
	R4_p -> ODR &= (uint32_t) (~R4_ODR);
}

static void KEY_setAllRows() {
	R1_p -> ODR |= (R1_ODR);
	R2_p -> ODR |= (R2_ODR);
	R3_p -> ODR |= (R3_ODR);
	R4_p -> ODR |= (R4_ODR);
}

keypadBut_t KEY_detectButton() {
	KEY_clearAllRows();

	// sadece R1 açık
	KEY_setRow(1);
	if(C1_p -> IDR & C1_IDR) {
		//1
		KEY_setAllRows();
		return keypadBut1;
	} else if(C2_p -> IDR & C2_IDR) {
		//2
		KEY_setAllRows();
		return keypadBut2;
	} else if(C3_p -> IDR & C3_IDR) {
		//3
		KEY_setAllRows();
		return keypadBut3;
	} else if(C4_p -> IDR & C4_IDR) {
		//A
		KEY_setAllRows();
		return keypadButA;
	}

	// sadece R2 açık
	KEY_setRow(2);
	if(C1_p -> IDR & C1_IDR) {
		//4
		KEY_setAllRows();
		return keypadBut4;
	} else if(C2_p -> IDR & C2_IDR) {
		//5
		KEY_setAllRows();
		return keypadBut5;
	} else if(C3_p -> IDR & C3_IDR) {
		//6
		KEY_setAllRows();
		return keypadBut6;
	} else if(C4_p -> IDR & C4_IDR) {
		//B
		KEY_setAllRows();
		return keypadButB;
	}

	// sadece R3 açık
	KEY_setRow(3);
	if(C1_p -> IDR & C1_IDR) {
		//7
		KEY_setAllRows();
		return keypadBut7;
	} else if(C2_p -> IDR & C2_IDR) {
		//8
		KEY_setAllRows();
		return keypadBut8;
	} else if(C3_p -> IDR & C3_IDR) {
		//9
		KEY_setAllRows();
		return keypadBut9;
	} else if(C4_p -> IDR & C4_IDR) {
		//C
		KEY_setAllRows();
		return keypadButC;
	}

	// sadece R4 açık
	KEY_setRow(4);
	if(C1_p -> IDR & C1_IDR) {
		//*
		KEY_setAllRows();
		return keypadButAst;
	} else if(C2_p -> IDR & C2_IDR) {
		//0
		KEY_setAllRows();
		return keypadBut0;
	} else if(C3_p -> IDR & C3_IDR) {
		//#
		KEY_setAllRows();
		return keypadButHash;
	} else if(C4_p -> IDR & C4_IDR) {
		//D
		KEY_setAllRows();
		return keypadButD;
	}

	KEY_setAllRows();

	return none;
}

static void KEY_setRow(uint8_t key) {
	KEY_clearAllRows();

	switch(key){
	case 1:
		R1_p -> ODR |= (R1_ODR);
		break;
	case 2:
		R2_p -> ODR |= (R2_ODR);
		break;
	case 3:
		R3_p -> ODR |= (R3_ODR);
		break;
	case 4:
		R4_p -> ODR |= (R4_ODR);
		break;
	default:
		// allah kurtarsın
		break;
	}
}
