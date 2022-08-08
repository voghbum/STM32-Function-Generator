/*
 * BSP.c
 *
 *  Created on: Nov 29, 2021
 *      Author: huseyinasci
 *      		Selin Yıldırım
 */
#include "BSP.h"
#include "stm32g0xx.h"
#include "sevensegment.h"
#include "keypad.h"

void BSP_systemInit(){
	BSP_initializeAndConfigClock();
	BSP_initializeAndConfigSysTickTimer(1000);
	SSD_setRCC();
	SSD_setMODER();
	KEY_setRCC();
	KEY_setMODER();
	KEY_setInterrupt();
	BSP_setWatchDogTimer();
	BSP_setPWM();
}

/*
 * PWM SETUP
 */
void BSP_setPWM(){
		//WORKING WITH PB3 PIN'S AF2 FUNCTION AS TIM2_CH2
		//enable gpiob
		RCC->IOPENR |= (1U << 1);
		//enable tim2 clock
		RCC->APBENR1 |= RCC_APBENR1_TIM2EN;

		//select AF from moder
		GPIOB->MODER &= ~(3U << 2*3);
		GPIOB->MODER |= (2U << 2*3);
		//set alternate function 2 // 0010 FOR AF2
		GPIOB->AFR[0] &= ~(0XFU << 4*3);
		GPIOB->AFR[0] |= (2U << 4*3);

	    // zero out the control register just in case
		TIM2->CR1 = 0;

	    // Select PWM Mode 1
	    TIM2->CCMR1 |= (6U << 12);

	    // Preload Enable
	    TIM2->CCMR1 |= TIM_CCMR1_OC2PE;

	    // Capture compare ch2 enable
	    TIM2->CCER |= TIM_CCER_CC2E;

	    // zero out counter
	    TIM2->CNT = 0;
	    // 1 ms interrupt
	    TIM2->PSC = 18;// 16 bit;
	    TIM2->ARR = 1599;

	    // zero out duty
	    TIM2->CCR2 =0 ;

	    // Update interrupt enable
	    TIM2->DIER |= (1 << 0);

	    // TIM1 Enable
	    TIM2->CR1 |= TIM_CR1_CEN;

	    NVIC_SetPriority(TIM2_IRQn, 1);
	    NVIC_EnableIRQ(TIM2_IRQn);
}

//**** ONBOARD LED ****/
void BSP_initializeOnBoardLed(){
	/* Enable GPIOC clock */
	RCC->IOPENR |= (1U << 2);

	/* Setup PC6 as output */
	GPIOC->MODER &= ~(3U << 2*6);
	GPIOC->MODER |= (1U << 2*6);

	/* Turn off LED */
	BSP_resetOnBoardLed();
}

void BSP_setOnBoardLed(){
	GPIOC->ODR |= (1U << 6);
}

void BSP_resetOnBoardLed(){
	GPIOC->ODR &= ~(1U << 6);
}

void BSP_toggleOnBoardLed(){
	GPIOC->ODR ^= (1U << 6);
}

//**** SYSTICK TIMER ****/
void BSP_initializeAndConfigSysTickTimer(uint32_t time) {
	SysTick_Config(SystemCoreClock / time);
}

//****************
void BSP_initializeAndConfigClock(){
	SystemCoreClockUpdate();
}

//****************
// TIMER3 FOR STATE DELAY
void BSP_Timer3_Config(uint32_t len){
	RCC -> APBENR1 |= (1U << 1);
	TIM3 -> CR1 = 0;
	TIM3 -> CR1 |= (1 << 7);	// we set buffer
	TIM3 -> CNT = 0;

	// TODO: AYARLAMAN LAZIM
	TIM3 -> PSC = (20*len); 		// this two instructions arrange one delay time,
								// f.ex if a=1000 one toggle lead tens seconds,

	TIM3 -> ARR = (15999); 		// this timer's clock 16MHz
	TIM3 -> DIER |= (1 << 0); 	// enable interrupt
	TIM3 -> CR1 |= (1 << 0); 	// enable control register

	NVIC_SetPriority(TIM3_IRQn, 0); // set timer's priority
}

//SSD için
void BSP_Timer2_Config(){
	RCC -> APBENR1 |= (1U << 0);
	TIM2 -> CR1 = 0;
	TIM2 -> CR1 |= (1 << 7);		// we set buffer
	TIM2 -> CNT = 0;

	// TODO: AYARLAMAN LAZIM
	TIM2 -> PSC = (10); 			// this two instructions arrange one delay time,
 									// f.ex if a=1000 one toggle lead tens seconds,

	TIM2 -> ARR = (15999); 			// this timer's clock 16MHz
	TIM2 -> DIER |= (1 << 0); 		// enable interrupt
	TIM2 -> CR1 |= (1 << 0); 		// enable control register

	NVIC_SetPriority(TIM2_IRQn, 1); // set timer's priority
	NVIC_EnableIRQ(TIM2_IRQn); 		// enable NVIC interrupt
}

void BSP_initializeInterruptForButton(){
	//Button -> PA4

	GPIOA -> PUPDR |= (2U << 15 * 2);

	/* External Interrupt ayarları */
	// rising edge'de yakalamak istediğim için RTSR1
	// PA0 yani 0. porta bağlı olduğu için 0. portu birledik.
	EXTI -> RTSR1 |= (1U << 15);

	EXTI -> EXTICR[3] &= ~(3U << 8 * 3);

	EXTI -> IMR1 |= (1U << 15);


	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void BSP_initializeButton(){
	// Button -> PA0
	RCC -> IOPENR |= (1U);
	GPIOA -> MODER &= ~(3U << 15 * 2);
	// **** //
}

void BSP_setWatchDogTimer() {
	IWDG -> KR 		= 0x5555; // SABİT
	IWDG -> PR 		= 0x256; // süre ile ilgili
	IWDG -> RLR 	= 0xFFF; // süre ile ilgili
	IWDG -> WINR 	= 0xFFF;

	// IWDG_SR = update için
}

void BSP_updateWatchDog(){
	IWDG -> SR = 0x7;
}

void BSP_turnOffWatchDog(){
	IWDG -> KR = 0x0000;
}


