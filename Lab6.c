// Lab6.c
// Runs on TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Anthony Do
// Date Created: 3/6/17 
// Last Modified: 1/17/21  
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/LaunchPad.h"
#include "../inc/CortexM.h"
#include "Sound.h"
#include "Key.h"
#include "Music.h"
#include "TExaS.h"

// Period =  80000000/64/Freq=1250000/Freq
#define C1   597   // 2093 Hz
#define B1   633   // 1975.5 Hz
#define BF1  671   // 1864.7 Hz
#define A1   710   // 1760 Hz
#define AF1  753   // 1661.2 Hz
#define G1   797   // 1568 Hz
#define GF1  855   // 1480 Hz
#define F1   895   // 1396.9 Hz
#define E1   948   // 1318.5 Hz
#define EF1  1005   // 1244.5 Hz
#define D1   1064   // 1174.7 Hz
#define DF1  1123   // 1108.7 Hz
#define C    1195   // 1046.5 Hz
#define B    1266   // 987.8 Hz
#define BF   1341   // 932.3 Hz
#define A    1421   // 880 Hz
#define AF   1505   // 830.6 Hz
#define G    1595   // 784 Hz
#define GF  1689   // 740 Hz
#define F   1790   // 698.5 Hz
#define E   1896   // 659.3 Hz
#define EF  2009   // 622.3 Hz
#define D   2129   // 587.3 Hz
#define DF  2255   // 554.4 Hz
#define C0  2389   // 523.3 Hz
#define B0  2531   // 493.9 Hz
#define BF0 2682   // 466.2 Hz
#define A0  2841   // 440 Hz
#define AF0 3010   // 415.3 Hz
#define G0  3189   // 392 Hz
#define GF0 3379   // 370 Hz
#define F0  3580   // 349.2 Hz
#define E0  3792   // 329.6 Hz
#define EF0 4027   // 311.1 Hz
#define D0  4257   // 293.7 Hz
#define DF0 4509   // 277.2 Hz
#define C7  4778   // 261.6 Hz
#define B7  5062   // 246.9 Hz
#define BF7 5363   // 233.1 Hz
#define A7  5682   // 220 Hz
#define AF7 6020   // 207.7 Hz
#define G7  6378   // 196 Hz
#define GF7 6757   // 185 Hz
#define F7  7159   // 174.6 Hz
#define E7  7585   // 164.8 Hz
#define EF7 8036   // 155.6 Hz
#define D7  8513   // 146.8 Hz
#define DF7 9020   // 138.6 Hz
#define C6  9556   // 130.8 Hz

void DAC_Init(void);         // your lab 6 solution
void DAC_Out(uint8_t data);  // your lab 6 solution
uint8_t Testdata;

// lab video Lab6_voltmeter
int voltmetermain(void){ //voltmetermain(void){     
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  DAC_Init(); // your lab 6 solution
  Testdata = 15;
  EnableInterrupts();
  while(1){                
    Testdata = (Testdata+1)&0x0F;
    DAC_Out(Testdata);  // your lab 6 solution
  }
}

// lab video Lab6_static
int staticmain(void){   uint32_t last,now;  
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  LaunchPad_Init();
  DAC_Init(); // your lab 6 solution
  Testdata = 15;
  EnableInterrupts();
  last = LaunchPad_Input();
  while(1){                
    now = LaunchPad_Input();
    if((last != now)&&now){
       Testdata = (Testdata+1)&0x0F;
       DAC_Out(Testdata); // your lab 6 solution
    }
    last = now;
    Clock_Delay1ms(25);   // debounces switch
  }
}
uint32_t i = 0;
void heartbeat(void){
	if(i & 0x00010000){
		GPIO_PORTF_DATA_R ^= 0x02;
	}
	i++;
}

//**************Lab 6 solution below*******************

int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Key_Init();
  LaunchPad_Init();
  Sound_Init();
  // other initialization
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_RCGCGPIO_R&0x20) != 0x20){};
	GPIO_PORTF_DIR_R |= 0x02;
	GPIO_PORTF_DEN_R |= 0x02;
	EnableInterrupts();
  while(1){ 
		heartbeat();
		int btns = Key_In();
		if(btns == 0){
			Sound_Off();
		}
		if(btns == 1){
			Sound_Start(A);
		}
		else if((btns >= 2)&&(btns <= 3)){
			Sound_Start(B);
		}
		else if((btns >= 4)&&(btns <= 7)){
			Sound_Start(E);
		}

		else if((btns >= 8)&&(btns <= 15)){
			Sound_Start(F);
		}
  }           
} 

/*#include "DAC.h"
int main(void){ uint32_t data; // 0 to 63 DAC output
  LaunchPad_Init();    // like Program 4.6 in the book, 80 MHz
  DAC_Init();
  for(;;) {
    DAC_Out(data);
    data = 0x3F&(data+1); // 
  }
}*/
