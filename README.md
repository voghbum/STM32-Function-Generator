# STM32 Function Generator
 This Project asked to us for creating a function generator. In order to wok on this project, we need to be familiar with the Seven Segment Display and Keypad setup and usage, and to know how to use Interrupt, Timer and PWM
 
 ## FEATURES
 ### Bright Level Differences on SSD
There is no bright level differences in between segments and digits in SSD. We solved this problem by using sysTick Timer. There is no brightness difference in the SSD because SysTick Timer lights each digit consecutively for a certain period of time (this period is too short for the human eye to perceive) and keep the duration of each digit on constant.

birinci foto gelecek

```C
void SysTick_Handler(){
 static volatile int8_t ct = -1;
 ct++;

if(ct == 5) { 
 SSD_disp();
 ct = 0;
 }
}
```
