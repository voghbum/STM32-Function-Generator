/*
 * 	main.c
 *
 * 	Author: Hüseyin Aşcı
 * 	Description: blinky external PA4 led interval 1 sec.
 *
 */

#include "stm32g0xx.h"
#include "BSP.h"
#include "keypad.h"
#include "sevensegment.h"

int RAMPLOOKUP[256] = {
			13,25,38,50,63,75,88,100,
			113,125,138,150,163,175,188,200,
			213,225,238,250,263,275,288,300,
			313,325,338,350,363,375,388,400,
			413,425,438,450,463,475,488,500,
			513,525,538,550,563,575,588,600,
			613,625,638,650,663,675,688,700,
			713,725,738,750,763,775,788,800,
			813,825,838,850,863,875,888,900,
			913,925,938,950,963,975,988,1000,
			1013,1025,1038,1050,1063,1075,1088,1100,
			1113,1125,1138,1150,1163,1175,1188,1200,
			1213,1225,1238,1250,1263,1275,1288,1300,
			1313,1325,1338,1350,1363,1375,1388,1400,
			1413,1425,1438,1450,1463,1475,1488,1500,
			1513,1525,1538,1550,1563,1575,1588,1600,
			1588,1575,1563,1550,1538,1525,1513,1500,
			1488,1475,1463,1450,1438,1425,1413,1400,
			1388,1375,1363,1350,1338,1325,1313,1300,
			1288,1275,1263,1250,1238,1225,1213,1200,
			1188,1175,1163,1150,1138,1125,1113,1100,
			1088,1075,1063,1050,1038,1025,1013,1000,
			988,975,963,950,938,925,913,900,
			888,875,863,850,838,825,813,800,
			788,775,763,750,738,725,713,700,
			688,675,663,650,638,625,613,600,
			588,575,563,550,538,525,513,500,
			488,475,463,450,438,425,413,400,
			388,375,363,350,338,325,313,300,
			288,275,263,250,238,225,213,200,
			188,175,163,150,138,125,113,100,
			88,75,63,50,38,25,13,0,
		  };

enum {sine = 0, square, triangular, sawtooth, whiteNoise, randomDig} signal;
enum {dispMode = 0, dispAmp, dispFreq, input} displayMode;

volatile keypadBut_t currentButton = none;
volatile keypadBut_t prevButton = none;

volatile uint8_t isInputAmp = 0;
volatile uint8_t isInputFreq = 0;

volatile int32_t var = 0;

volatile int32_t amp		= 5;
volatile int32_t freq		= 10;


void doWorkForButtons();
void sysSet();
void setSignalDisp();
void setVar();
void setSignalOutput();

void EXTI0_1_IRQHandler() {
	currentButton = KEY_detectButton();
	doWorkForButtons();
	EXTI -> RPR1 |= (1 << 0);
}

void EXTI2_3_IRQHandler() {
	currentButton = KEY_detectButton();
	doWorkForButtons();
	EXTI -> RPR1 |= (1 << 2);
}

void EXTI4_15_IRQHandler() {
	currentButton = KEY_detectButton();
	doWorkForButtons();
	EXTI -> RPR1 |= (1 << 8);
	EXTI -> RPR1 |= (1 << 9);
}

// bunun göz fpsine ayarlanması lazım.
// galiba 5 ms
void SysTick_Handler(){
	static volatile int8_t ct = -1;

	ct++;
	if(ct == 5) {
		SSD_disp();
		ct = 0;
	}
}

void TIM2_IRQHandler(void){
	static volatile int i = 0;
	TIM2->CCR2 = RAMPLOOKUP[i];
	i++;
	if(i == 256)
		i = 0;
	TIM2->SR &= ~(1U << 0);
}

int main(void) {
	var = 0;
	isInputFreq = 0;
	isInputAmp = 0;
	displayMode = dispMode;
	sysSet();
	//*****

	BSP_systemInit();
	setSignalDisp();
    return 0;
}

void doWorkForButtons() {

	if(currentButton != keypadButC || currentButton != keypadButD || currentButton > 9) {
		if(prevButton == currentButton) {
				return;
			}
	}

	if(isInputAmp == 1) {
		switch(currentButton) {
		case keypadButC:
		case keypadButD:
		case keypadButB:
			var = 0;
			isInputAmp = 0;
			displayMode = dispMode;
			sysSet();
			return;
		default:
			break;
		}
	}
	else if(isInputFreq == 1) {
			switch(currentButton) {
			case keypadButC:
			case keypadButD:
			case keypadButA:
				var = 0;
				isInputFreq = 0;
				displayMode = dispMode;
				sysSet();
				return;
			default:
				break;
			}
		}

	switch(currentButton) {
	case keypadButC:
		signal++;
		if(signal == 6)
			signal = 0;
		setSignalOutput();
		break;
	case keypadButD:
		displayMode++;
		if(displayMode >= 3)
			displayMode = 0;
		break;
	case keypadButA:
		displayMode = input;
		isInputAmp = 1;
		break;
	case keypadButB:
		displayMode = input;
		isInputFreq = 1;
		break;
	case keypadButHash:
		amp = isInputAmp ? var : amp;
		freq = isInputFreq ? var : freq;
		isInputAmp = 0;
		isInputFreq = 0;
		var = 0;
		displayMode = dispMode;
		break;
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		if(isInputAmp || isInputFreq) {
			setVar();
		}
		break;
	default:
		//..
		break;
	}

	prevButton = currentButton;

	sysSet();
}

void sysSet() {
	switch(displayMode) {
	case dispAmp:
		SSD_getDigits(amp);
		break;
	case dispFreq:
		SSD_getDigits(freq);
		break;
	case dispMode:
		setSignalDisp();
		break;
	case input:
		SSD_getDigits(var);
		break;

	}
}

void setSignalDisp(){
	switch(signal) {
	case sine:
		SSD_setSine();
		break;
	case square:
		SSD_setSquare();
		break;
	case triangular:
		SSD_setTri();
		break;
	case sawtooth:
		SSD_setRamp();
		break;
	case whiteNoise:
		SSD_setWhiteNoise();
		break;
	case randomDig:
		SSD_setRandDigital();
		break;
	}
}

void setVar() {
	var *= 10;
	var += currentButton;
	SSD_getDigits(var);
}

void setSignalOutput() {
	// burada sinyal outuputu ile ilgili pwm düzenlemeleri
	// yapılacak
}
