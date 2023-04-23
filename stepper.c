// Stepper.c
// Runs on TM4C123
// PD3 connected to driver for stepper motor coil A
// PD2 connected to driver for stepper motor coil A'
// PD1 connected to driver for stepper motor coil B
// PD0 connected to driver for stepper motor coil B'

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

struct State{
  uint8_t Out;     // Output
  uint8_t Next[2]; // CW/CCW Next[0]->CW, Next[1]->CCW
};

struct State1{
  uint8_t Out1;     // Output
  uint8_t Next1[2]; // CW/CCW Next[0]->CW, Next[1]->CCW
};
typedef const struct State StateType;
typedef const struct State1 StateType1;

#define CLOCKWISE 0        // Next index
#define COUNTERCLOCKWISE 1 // Next index

#define CLOCKWISE1 0        // Next index
#define COUNTERCLOCKWISE1 1 // Next index

StateType fsm1[4]={
	// index 0: state 0,state goes from 0 to 3,  output 1100,
	// if next state index is 0: move clockwise, next state for clockwise movement is 1
	// CW state transition is: 0->1->2->3 then repeat
	// CCW state transition is: 0->3->2->1 then repeat
  {0x0C,{1,3}}, // state 0, PD3-0:1100. CW next state->1, CCW next state->3
  {0x06,{2,0}}, // state 1, PD3-0:0110
  {0x03,{3,1}}, // state 2, PD3-0:0011
  {0x09,{0,2}}  // state 3, PD3-0:1001
};

StateType1 fsm2[4]={
	// index 0: state 0,state goes from 0 to 3,  output 1100,
	// if next state index is 0: move clockwise, next state for clockwise movement is 1
	// CW state transition is: 0->1->2->3 then repeat
	// CCW state transition is: 0->3->2->1 then repeat
  {0xC0,{1,3}}, // state 0, PC7-4:1100 0000. CW next state->1, CCW next state->3
  {0x60,{2,0}}, // state 1, PC7-4:0110 0000
  {0x30,{3,1}}, // state 2, PC7-4:0011 0000
  {0x90,{0,2}}  // state 3, PC7-4:1001 0000
};

unsigned char s; // current state
unsigned char s2;

#define STEPPER1  (*((volatile uint32_t *)0x4000703C))  // PORT D, pin: 0,1,2,3
#define STEPPER2  (*((volatile uint32_t *)0x400063C0))  // PORT C, pin: 4,5,6,7
	
unsigned char test;
	
// Move 1.8 degrees clockwise, delay is the time to wait after each step
void Stepper1_CW(uint32_t delay){
  s = fsm1[s].Next[CLOCKWISE]; // clock wise circular
  STEPPER1 = fsm1[s].Out; // step motor
  SysTick_Wait(delay);
}
// Move 1.8 degrees counterclockwise, delay is wait after each step
void Stepper1_CCW(uint32_t delay){
  s = fsm1[s].Next[COUNTERCLOCKWISE]; // counter clock wise circular
  STEPPER1 = fsm1[s].Out; // step motor
  SysTick_Wait(delay); // blind-cycle wait
}

// Move 1.8 degrees clockwise, delay is the time to wait after each step
void Stepper2_CW(uint32_t delay){
  s2 = fsm2[s2].Next1[CLOCKWISE1]; // clock wise circular
	test = fsm2[s2].Out1;
  STEPPER2 = fsm2[s2].Out1; // step motor
  SysTick_Wait(delay);
}
// Move 1.8 degrees counterclockwise, delay is wait after each step
void Stepper2_CCW(uint32_t delay){
  s2 = fsm2[s2].Next1[COUNTERCLOCKWISE1]; // counter clock wise circular
  STEPPER2 = fsm2[s2].Out1; // step motor
  SysTick_Wait(delay); // blind-cycle wait
}

// Initialize Stepper interface
void Stepper1_Init(void){
	if ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOD) != SYSCTL_RCGC2_GPIOD){
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // Activate Port D clocks
	while ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOD) != SYSCTL_RCGC2_GPIOD){} // wait for clock to be active
	}
  SysTick_Init();
  s = 0; 
                                    // 2) no need to unlock PD3-0
  GPIO_PORTD_AMSEL_R &= ~0x0F;      // 3) disable analog functionality on PD3-0
  GPIO_PORTD_PCTL_R &= ~0x0000FFFF; // 4) GPIO configure PD3-0 as GPIO
  GPIO_PORTD_DIR_R |= 0x0F;   // 5) make PD3-0 out
  GPIO_PORTD_AFSEL_R &= ~0x0F;// 6) disable alt funct on PD3-0
  GPIO_PORTD_DR8R_R |= 0x0F;  // enable 8 mA drive
  GPIO_PORTD_DEN_R |= 0x0F;   // 7) enable digital I/O on PD3-0 
}

void Stepper2_Init(void){
	if ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOC) != SYSCTL_RCGC2_GPIOC){
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // Activate Port C clocks
	while ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOC) != SYSCTL_RCGC2_GPIOC){} // wait for clock to be active
			
	}

  s2 = 0; 
                                    // 2) no need to unlock PC7-4
  GPIO_PORTC_AMSEL_R &= ~0xF0;      // 3) disable analog functionality on PC7-4
  GPIO_PORTC_PCTL_R &= ~0xFFFF0000; // 4) GPIO configure PC7-0 as GPIO
  GPIO_PORTC_DIR_R |= 0xF0;   // 5) make PC7-4 out
  GPIO_PORTC_AFSEL_R &= ~0xF0;// 6) disable alt funct on PC7-4
  GPIO_PORTC_DR8R_R |= 0xF0;  // enable 8 mA drive
  GPIO_PORTC_DEN_R |= 0xF0;   // 7) enable digital I/O on PC7-4 
}