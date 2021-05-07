// Music.c
// This program can use timer0A and timer1A ISR  
// playing your favorite song.
//
// For use with the TM4C123
// EE319K lab6 extra credit
// Program written by: Anthony Do
// 1/17/21

#include "Sound.h"
#include "DAC.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void Music_Init(void){
  // write this
  // extra credit

}


// Play song, while button pushed or until end
void Music_PlaySong(void){
  // write this
  // extra credit

}

// Stop song
void Music_StopSong(void){
   // write this
  // extra credit

}

// Timer0A actually controls outputting to DAC
void Timer0A_Handler(void){
    // write this
  // extra credit

}

  // Timer1A acts as a metronome for the song(s)
void Timer1A_Handler(void){
    // write this
  // extra credit


}
#define NVIC_EN0_INT19          0x00080000  // Interrupt 19 enable
#define NVIC_EN0_INT21          0x00200000  // Interrupt 21 enable

// ***************** Timer_Init ****************
// Activate Timer0A and Timer1A interrupts to run user task periodically
// Inputs: period0 in nsec
//         period1 in msec
// Outputs: none
void Timer_Init(unsigned int period0, unsigned int period1){ uint32_t volatile delay;
   // write this
  // extra credit

}
void Timer_Stop(void){ 
    // write this
  // extra credit

}

