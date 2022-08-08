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
The SS_disp() function in the SSD library we wrote in the Systick Handler is called, this function keeps the next digit open for a certain period of time when each tick is hit. Thus, each digit is given equal time and there is no bright level differences on the SSD.

### Keypad Key Adjustments

As requested in the project, each key was adjusted as it should work. Firstly we call detectButton() function o understand which key was pressed in related interrupts. detectButton() function returns the enum constant which key was pressed from the created enum type. Afterwards, instructures that are related to the button pressed with the function called doWorkButton() operates.

### Propering Guards for Amplitude/Frequency Inputs and Other Buttons

This condition is done with a simple if block. During Amplitude or Frequency entry if we pressed button except number keys the entered value is not accepted and the system resets itself.

### User Interface

The user interface works as requested. Button # is used as an Enter key Button, A is used to define the Amplitude of the signal, Button D is used to cycle through displaying the Mode, Amplitude and Frequency of the currently active signal, Button C is used to cycle through modes.

