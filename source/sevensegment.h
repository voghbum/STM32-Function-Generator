/*
 * sevenSegment.h
 *
 *  Created on: Nov 14, 2021
 *      Author: huseyinasci
 */

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include "stm32g0xx.h"
#include <stdlib.h>

/*	Segmentlerin hepsi PA pinlerinde
 *
 * 	A Segmenti	=>	PA0
 * 	B Segmenti	=>	PA1
 * 	C Segmenti	=>	PA12
 * 	D Segmenti	=>	PA6
 * 	E Segmenti	=>	PA11
 * 	F Segmenti	=>	PA4
 * 	G Segmenti	=>	PA5
 *
 * 		   D1	=>	PA7
 * 		   D2	=>	PB3
 * 		   D3	=>	PA10
 * 		   D4	=>	PB1
 */


/* Segmentleri yakmak için gerekli bitler
 * (ANOTA GÖRE YAZILDI)
 */

/*	KOLAYLIK OLMASI İÇİN SEGMENTLERİN HEPSİ A VEYA
	B PINLERİNDE OLACAK ŞEKİLDE YAZILDI.
	ÖRNEĞİN A SEGMENTİ B PININDE G SEGMENTİ B
	PININDE OLURSA ÇALIŞMAZ.
*/
#define SEGMENT_P		(GPIOA)

#define SEGMENT_A		((uint32_t) (0xFFFE))
#define SEGMENT_B		((uint32_t) (0xFFFD))
#define SEGMENT_C		((uint32_t) (0xEFFF))
#define SEGMENT_D		((uint32_t) (0xFFBF))
#define SEGMENT_E		((uint32_t) (0xF7FF))
#define SEGMENT_F		((uint32_t) (0xFFEF))
#define SEGMENT_G		((uint32_t) (0xFFDF))

//DEFINE SSD DIGITS
#define DIGIT_1			((uint32_t) (0x80)) //10000000
#define DIGIT_1_P		(GPIOA)

#define DIGIT_2			((uint32_t) (0x40))
#define DIGIT_2_P		(GPIOB)

#define DIGIT_3			((uint32_t) (0x400))
#define DIGIT_3_P		(GPIOA)

#define DIGIT_4			((uint32_t) (0x2))
#define DIGIT_4_P		(GPIOB)

/* SADECE USTTEKI DEFINELARI SSDYİ BAĞLADIĞIN YERLERE GÖRE
 * DEĞİŞTİRMEN YETERLİ ! */
// ********* //

/* DEFINE SSD NUMBER BITS */
#define	SSD_ZERO	(SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_F)
#define	SSD_ONE		(SEGMENT_B & SEGMENT_C)
#define	SSD_TWO		(SEGMENT_A & SEGMENT_B & SEGMENT_G & SEGMENT_E & SEGMENT_D)
#define	SSD_THREE	(SEGMENT_A & SEGMENT_B & SEGMENT_G & SEGMENT_C & SEGMENT_D)
#define	SSD_FOUR	(SEGMENT_F & SEGMENT_B & SEGMENT_G & SEGMENT_C)
#define	SSD_FIVE	(SEGMENT_A & SEGMENT_F & SEGMENT_G & SEGMENT_C & SEGMENT_D)
#define	SSD_SIX		(SEGMENT_A & SEGMENT_F & SEGMENT_G & SEGMENT_C & SEGMENT_D & SEGMENT_E)
#define	SSD_SEVEN	(SEGMENT_A & SEGMENT_B & SEGMENT_C)
#define	SSD_EIGHT	(SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_F & SEGMENT_G)
#define	SSD_NINE	(SEGMENT_A & SEGMENT_F & SEGMENT_G & SEGMENT_B & SEGMENT_C & SEGMENT_D)

#define SSD_A		(SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_E & SEGMENT_F & SEGMENT_G)
#define SSD_B		(SEGMENT_F & SEGMENT_G & SEGMENT_C & SEGMENT_D & SEGMENT_E)
#define SSD_C		(SEGMENT_A & SEGMENT_F & SEGMENT_E & SEGMENT_D)
#define SSD_D		(SEGMENT_B & SEGMENT_C & SEGMENT_G & SEGMENT_E & SEGMENT_D)
#define SSD_E		(SEGMENT_A & SEGMENT_F & SEGMENT_G & SEGMENT_E & SEGMENT_D)
#define SSD_F		(SEGMENT_A & SEGMENT_F & SEGMENT_G & SEGMENT_E)
#define SSD_G		(SSD_SIX)
#define SSD_H		(SEGMENT_F & SEGMENT_B & SEGMENT_C & SEGMENT_E & SEGMENT_G)
#define SSD_I		(SEGMENT_F & SEGMENT_E)
#define SSD_J		(SEGMENT_B & SEGMENT_C & SEGMENT_D) //
#define SSD_L		(SEGMENT_F & SEGMENT_E & SEGMENT_D)
#define SSD_N		(SEGMENT_G & SEGMENT_C & SEGMENT_E)
#define SSD_O		(SSD_ZERO)
#define SSD_P		(SEGMENT_B & SEGMENT_A & SEGMENT_G & SEGMENT_F & SEGMENT_E)
#define SSD_R		(SEGMENT_E & SEGMENT_G)
#define SSD_S		(SSD_FIVE)
#define SSD_T		(SEGMENT_F & SEGMENT_G & SEGMENT_E & SEGMENT_D)
#define SSD_U		(SEGMENT_E & SEGMENT_C & SEGMENT_D)
#define SSD_HYPEN	(SEGMENT_G)

//SSD'yi temizlemek için bununla orlayacaksın.
#define	SSD_CLEAR	((uint16_t) (~(SEGMENT_A & SEGMENT_B & SEGMENT_C & SEGMENT_D & SEGMENT_E & SEGMENT_F & SEGMENT_G)))
// ******* //

#define DELAY_FOR_SSD (700)

int16_t SSD_numberDigits[4];

void SSD_setMODER();
void SSD_setRCC();
void SSD_getDigits(int32_t val);
void SSD_disp();
void SSD_dispNumberDigit(int16_t valLOOKUP, uint8_t SSDDigit);
void SSD_setAllDigits();
void SSD_resetAllDigits();
void SSD_setDigit(uint8_t digit);

void SSD_setAmp();
void SSD_setFreq();
void SSD_setSine();
void SSD_setTri();
void SSD_setRamp();
void SSD_setSquare();
void SSD_setRandDigital();
void SSD_setWhiteNoise();


#endif /* SEVENSEGMENT_H_ */
