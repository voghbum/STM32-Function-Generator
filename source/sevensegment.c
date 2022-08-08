/*
 * sevenSegment.c
 *
 * Created on: Nov 14, 2021
 * Author: huseyinasci
 */

#include "sevensegment.h"
#include "stm32g0xx.h"
#include <stdlib.h>
#include "BSP.h"

#define LOOKUP_LEN 29

static const uint32_t LOOKUP[] = {
		SSD_ZERO,	//0
		SSD_ONE,	//1
		SSD_TWO,	//2
		SSD_THREE,	//3
		SSD_FOUR,	//4
		SSD_FIVE,	//5
		SSD_SIX,	//6
		SSD_SEVEN,	//7
		SSD_EIGHT,	//8
		SSD_NINE,	//9

		SSD_A,		//10
		SSD_B,		//11
		SSD_C,		//12
		SSD_D,		//13
		SSD_E,		//14
		SSD_F,		//15
		SSD_G,		//16
		SSD_H,		//17
		SSD_I,		//18
		SSD_J,		//19
		SSD_L,		//20
		SSD_N,		//21
		SSD_O,		//22
		SSD_P,		//23
		SSD_R,		//24
		SSD_S,		//25
		SSD_T,		//26
		SSD_U,		//27
		SSD_HYPEN	//28
};

// TODO: floating point sayılar ?
// TODO: Gereksiz digitleri kapatma ?
void SSD_getDigits(int32_t val) {
	/*
	 * val = 1234 olsun.
	 * [0] = 1;
	 * [1] = 2;
	 * [2] = 3;
	 * [3] = 4;
	 * 
	 * olur.
	 */
	
	
	SSD_numberDigits[0] = 0;
	SSD_numberDigits[1] = 0;
	SSD_numberDigits[2] = 0;
	SSD_numberDigits[3] = 0;
	
	if(((val < 0) && (val  < -999)) || (val > 9999)) {
		// overflow olduğu için "----" gösteriyorum.
					SSD_numberDigits[0] = 28;
					SSD_numberDigits[1] = 28;
					SSD_numberDigits[2] = 28;
					SSD_numberDigits[3] = 28;
					return;
	}

	// TODO: Negatif sayıları yazdırmak için bir değer
	if(val < 0){
		val *= -1;

		SSD_numberDigits[0] = 24;
		SSD_numberDigits[1] = (int16_t) val / 100;
		val %= 100;
		SSD_numberDigits[2] = (int16_t) val / 10;
		SSD_numberDigits[3] = (int16_t) val % 10;
	} else {
		SSD_numberDigits[0] = (int16_t) val / 1000;
		val %= 1000;
		SSD_numberDigits[1] = (int16_t) val / 100;
		val %= 100;
		SSD_numberDigits[2] = (int16_t) val / 10;
		SSD_numberDigits[3] = (int16_t) val % 10;
	}
}

void SSD_setAmp(){
	/*
	 * APLI yazacak
	 */

	SSD_numberDigits[0] = 10;
	SSD_numberDigits[1] = 23;
	SSD_numberDigits[2] = 20;
	SSD_numberDigits[3] = 18;
}

void SSD_setFreq() {
	/*
	 * Fre yazacak
	 */
	SSD_numberDigits[0] = -1;
	SSD_numberDigits[1] = 15;
	SSD_numberDigits[2] = 24;
	SSD_numberDigits[3] = 14;
}

void SSD_setSine(){
	/*
	 * SInE yazacak
	 */
	SSD_numberDigits[0] = 25;
	SSD_numberDigits[1] = 18;
	SSD_numberDigits[2] = 21;
	SSD_numberDigits[3] = 14;
}

void SSD_setTri(){
	/*
	 * TrI yazacak
	 */

	SSD_numberDigits[0] = -1;
	SSD_numberDigits[1] = 26;
	SSD_numberDigits[2] = 24;
	SSD_numberDigits[3] = 18;
}

void SSD_setSquare(){
	SSD_numberDigits[0] = 25;
	SSD_numberDigits[1] = 27;
	SSD_numberDigits[2] = 10;
	SSD_numberDigits[3] = 24;
}

void SSD_setRamp() {
	SSD_numberDigits[0] = -1;
	SSD_numberDigits[1] = 24;
	SSD_numberDigits[2] = 10;
	SSD_numberDigits[3] = 23;
}

void SSD_setWhiteNoise(){
	SSD_numberDigits[0] = 21;
	SSD_numberDigits[1] = 22;
	SSD_numberDigits[2] = 18;
	SSD_numberDigits[3] = 25;
}

void SSD_setRandDigital() {
	SSD_numberDigits[0] = 13;
	SSD_numberDigits[1] = 18;
	SSD_numberDigits[2] = 16;
	SSD_numberDigits[3] = 18;
}

// Timer için
void SSD_disp() {
	static volatile  uint8_t ar = 0;
	// SSD ->  _   _   _   _
	// D ->	   1   2   3   4
	// Ar ->  [0] [1] [2] [3]

	switch(ar){
	case 0:
		SSD_dispNumberDigit(SSD_numberDigits[0], 1);
		break;
	case 1:
		SSD_dispNumberDigit(SSD_numberDigits[1], 2);
		break;
	case 2:
		SSD_dispNumberDigit(SSD_numberDigits[2], 3);
		break;
	case 3:
		SSD_dispNumberDigit(SSD_numberDigits[3], 4);
		break;
	}

	ar++;

	if(ar == 4)
		ar = 0;
}

void SSD_dispNumberDigit(int16_t valLOOKUP, uint8_t SSDDigit) {
	SEGMENT_P->ODR |= SSD_CLEAR;

	if(valLOOKUP == -1 || valLOOKUP > LOOKUP_LEN - 1) {
			return;
	}

	SSD_setDigit(SSDDigit);


	SEGMENT_P -> ODR &= LOOKUP[valLOOKUP];

}

void SSD_setAllDigits() {
	// ALL DIGIT ODR
	DIGIT_1_P->ODR |= DIGIT_1;
	DIGIT_2_P->ODR |= DIGIT_2;
	DIGIT_3_P->ODR |= DIGIT_3;
	DIGIT_4_P->ODR |= DIGIT_4;
}

void SSD_resetAllDigits() {
	DIGIT_1_P->ODR &= ~DIGIT_1;
	DIGIT_2_P->ODR &= ~DIGIT_2;
	DIGIT_3_P->ODR &= ~DIGIT_3;
	DIGIT_4_P->ODR &= ~DIGIT_4;
}

void SSD_setDigit(uint8_t digit) {
	/*
	 * D1 => PA7
	 * D2 => PB3
	 * D3 => PA10
	 * D4 => PB1
	 */
	// önce hepsini kapat
	SSD_resetAllDigits();
	// **** //

	switch (digit) {
	case 1:
		DIGIT_1_P->ODR |= DIGIT_1;
		break;
	case 2:
		DIGIT_2_P->ODR |= DIGIT_2;
		break;
	case 3:
		DIGIT_3_P->ODR |= DIGIT_3;
		break;
	case 4:
		DIGIT_4_P->ODR |= DIGIT_4;
		break;
	default:
		break;
	}
}

// PINLERE GORE AYARLAMAN LAZIM
void SSD_setRCC() {
	// A ve B pinlerini aç
	RCC->IOPENR |= (3U);
}


// PINLERE GORE AYARLAMAN LAZIM
void SSD_setMODER() {
	// A için (SADECE SSD PINLERI)
	// 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
	// xx xx xx 01 01 01 xx xx 01 01 01 01 xx xx 01 01 lazım

	// 00 00 00 01 01 01 00 00 01 01 01 01 00 00 01 01 = 0x1505505 orlamak için
	// 11 11 11 01 01 01 11 11 01 01 01 01 11 11 01 01 = 0xFD5F55F5 andlemek için
	GPIOA->MODER |= (uint32_t) (0x1505505);
	GPIOA->MODER &= (uint32_t) (0xFD5F55F5);

	// B için (SADECE SSD PINLERI)
	// 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
	// xx xx xx xx xx xx xx xx xx xx xx xx 01 xx 01 xx
	//01 00 01 00 = 0x44 orlamak için
	// 11 11 11 11 11 11 11 11 11 11 11 11 01 11 01 11 = 0xFFFFFF77 andlemek için
	GPIOB->MODER |= (uint32_t) (0x44);
	GPIOB->MODER &= (uint32_t) (0xFFFFFF77);

	GPIOB->MODER &= ~(3U << 2*6);
	GPIOB->MODER |= (1U << 2*6);
}
