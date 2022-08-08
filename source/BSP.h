/*
 * BSP.h
 *
 *  Created on: Nov 29, 2021
 *      Author: huseyinasci
 */

#ifndef BSP_H_
#define BSP_H_
#include "stm32g0xx.h"

enum states {	MOD0 = 0, MOD1 = 1000, MOD2 = 500, MOD3 = 100, MOD4 = 10,
						MOD5 = 1	};

void BSP_systemInit();

void BSP_initializeOnBoardLed();
void BSP_setOnBoardLed();
void BSP_resetOnBoardLed();
void BSP_toggleOnBoardLed();

void BSP_initializeAndConfigClock();
void BSP_initializeAndConfigSysTickTimer(uint32_t time);
void SysTick_Handler();

void BSP_initializeButton();
void BSP_initializeInterruptForButton();

void BSP_Timer3_Config(uint32_t len);
void BSP_Timer2_Config();
void BSP_setWatchDogTimer();
void BSP_updateWatchDog();
void BSP_turnOffWatchDog();

void BSP_setPWM();

#endif /* BSP_H_ */
