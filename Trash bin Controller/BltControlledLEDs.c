// BLTControlledLEDs.c
// Runs on LM4F120/TM4C123
// This is an example program which shows how to use Bluetooth to received commands from a Bluetooth terminal
// and use the received command to control the onboard LEDs.
// U1Rx (PB0)
// U1Tx (PB1)
// Ground connected ground in the USB cable

//Sensor 1 Full PE1
//Sensor 1 Empty PE2

//Sensor 2 Full PE3
//Sensor 2 Empty PE4

//Stepper 1 PD3-0
//Stepper 2 PC7-4


// Header files 
#include <stdint.h>
#include <string.h>

#include "tm4c123gh6pm.h"
#include "stepper.h"
#include "systick.h"

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A

#define T1ms 16000    // assumes using 16 MHz Clock 

#define SENSOR  (*((volatile uint32_t *)0x40024078))  // PORT E4-1

void UART_Init(void);
unsigned char UART1_InChar(void);
void BLT_InString(unsigned char *bufPt);
void UART0_OutChar(unsigned char data);
void UART0_OutString(unsigned char *pt);
void PortE_Init(void);

int main(void) {
	unsigned char test1; // for bluetooth controlled LEDs
  //unsigned char str[30];      // for testing strings from Bluetooth
	
	//unsigned char str1[30] = "1";
	//unsigned char str2[30] = "2";

	UART_Init(); // Initialize UART1
  PortE_Init(); // Initilize for the three onboard LEDs
	UART0_OutString((unsigned char *)">>> Welcome to Bluetooth Controlled LED App <<<\n\r");
  
	unsigned int i = 0;
	
	unsigned char S;

  Stepper1_Init();
	Stepper2_Init();
	
	//unsigned int e1 = 1;
	//unsigned int e2 = 1;
	
	while(1) {
		test1 = UART1_InChar(); //comp char -> test1
		//BLT_InString(str);
		
    //UART0_OutChar('j'); //mcu -> comp char
		//UART0_OutChar(CR);
    //UART0_OutChar(LF);
		
		//UART0_OutString((unsigned char *)"Apple Suck\n\r");
		//UART0_OutChar(CR);
    //UART0_OutChar(LF);
		//UART0_OutString((unsigned char *)"Sensor1 50\n\r");
		//UART0_OutString((unsigned char *)"Sensor2 100\n\r");

		/*
		for (int i = 0; i < 30; i++) {
			if (str[i] != str1[i]) {
				e1 = 0;
      }
			else if(str[i] != str2[i]){
				e2 = 0;
			}
		}
		*/
		//clockwise
		if (test1 == '1'){
			for (i=0;i<600; i++) {
			Stepper1_CW(2*T1ms);   // output every 10ms, frequency for the stepper motor is 100Hz.
			}		
			SysTick_Wait(500*T1ms);  // wait for 0.5s
				
			// turn counter clockwise 90 degrees
			for (i=0;i<500; i++) {
				Stepper1_CCW(2*T1ms);   // output every 10ms
			}
			SysTick_Wait(500*T1ms);  // wait for 0.5s
		}
		else if (test1 == '2'){
			//clockwise
			for (i=0;i<600; i++) {
				Stepper2_CW(2*T1ms);   // output every 10ms, frequency for the stepper motor is 100Hz.
			}		
			SysTick_Wait(500*T1ms);  // wait for 0.5s
		
			// turn counter clockwise 90 degrees
			for (i=0;i<500; i++) {
				Stepper2_CCW(2*T1ms);   // output every 10ms
			}
			SysTick_Wait(500*T1ms);  // wait for 0.5s
		}
		
		S = SENSOR;
		
		//Sensor 1 Full
		if(S & (0x01 << 2)){
			UART0_OutString((unsigned char *)"Sensor1\t Full\n\r");
		}
		else if (S | ~(0x01 << 2)){
			UART0_OutString((unsigned char *)"Sensor1\tNot Full\n\r");
		}
		
		//Sensor 1 Empty
		if(S & (0x01 << 1)){
			UART0_OutString((unsigned char *)"Sensor1\tNot Empty\n\r");
		}
		else if(S | ~(0x01 << 1)){
			UART0_OutString((unsigned char *)"Sensor1\tEmpty\n\r");
		}
		
		//Sensor 2 Full
		if(S & (0x01 << 3)){
			UART0_OutString((unsigned char *)"Sensor2\tFull\n\r");
		}
		else if(S | ~(0x01 << 3)){
			UART0_OutString((unsigned char *)"Sensor2\tNot Full\n\r");
		}
		
		//Sensor 2 Empty
		if(S & (0x01 << 4)){
			UART0_OutString((unsigned char *)"Sensor2\tNot Empty\n\r");
		}
		else if(S | ~(0x01 << 4)){
			UART0_OutString((unsigned char *)"Sensor2\tEmpty\n\r");
		}
	}
}

//------------UART_Init------------
// Initialize the UART for 19200 baud rate (assuming 16 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){
	// Activate Clocks
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
	
	
	UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 17;                    // IBRD = int(16,000,000 / (16 * 57600)) = int(17.3611111)
  UART0_FBRD_R = 23;                     // FBRD = round(3611111 * 64) = 27
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= 0x301;                 // enable UART for both Rx and Tx

  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA1,PA0
	
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
	
	// Data Communication Mode, Buad Rate = 57600
  UART1_IBRD_R = 17;                    // IBRD = int(16,000,000 / (16 * 57600)) = int(17.3611111)
  UART1_FBRD_R = 23;                     // FBRD = round(3611111 * 64) = 27
	
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= 0x301;                 // enable UART for both Rx and Tx
  
  GPIO_PORTB_AFSEL_R |= 0x03;           // enable alt funct on PB1,PB0
  GPIO_PORTB_DEN_R |= 0x03;             // enable digital I/O on PB1,PB0
                                        // configure PB1,PB0 as UART1
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTB_AMSEL_R &= ~0x03;          // disable analog functionality on PB1,PB0

}

//------------UART0_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(unsigned char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

//------------UART0_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART0_OutString(unsigned char *pt){
  while(*pt){
    UART0_OutChar(*pt);
    pt++;
  }
}

//------------UART1_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART1_InChar(void){
  while((UART1_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART1_DR_R&0xFF));
}

// This function reads response from HC-05 Bluetooth module.
void BLT_InString(unsigned char *bufPt) {
  unsigned char length=0;
  bufPt[length] = UART1_InChar();
  
  // Two possible endings for a reply from HC-05: OK\r\n, ERROR:(0)\r\n
  while (bufPt[length]!=LF) {
    length++;
    bufPt[length] = UART1_InChar();
  };
    
  // add null terminator
  length++;
  bufPt[length] = 0;
}

// Port E Initialization
void PortE_Init(void){ volatile unsigned long delay;
	if ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOE) != SYSCTL_RCGC2_GPIOE){
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // Activate Port E clocks
	while ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOE) != SYSCTL_RCGC2_GPIOE){} // wait for clock to be active
	}

  GPIO_PORTE_CR_R |= 0x1E;         // allow changes to PE4-1
  GPIO_PORTE_AMSEL_R &= ~0x1E;      // 3) disable analog function
  GPIO_PORTE_PCTL_R &= ~0x000FFFF0; // 4) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R &= ~0x1E;         // 6) PE4-1 Input
  GPIO_PORTE_AFSEL_R &= ~0x1E;      // 7) no alternate function     
  GPIO_PORTE_DEN_R |= 0x1E;         // 8) enable digital pins PE4-1 
}