// Sound.c
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// Jonathan Valvano
// 11/15/2021 
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/DAC5.h"
#include "../inc/Timer.h"

uint32_t i; //index

const uint8_t SinWave[32] = {
  16,19,22,24,27,28,30,31,31,31,30,
  28,27,24,22,19,16,13,10,8,5,4,
  2,1,1,1,2,4,5,8,10,13};


const uint8_t Trumpet[64] = {
  20,21,21,22,23,23,23,23,21,18,15,
  10,6,3,2,6,15,23,28,29,29,26,
  23,22,21,21,20,21,21,21,21,20,
  20,20,20,20,20,21,21,20,20,20,
  20,20,21,21,22,22,21,21,21,21,
  21,21,22,22,21,21,21,20,20,20,20,20
};



void SysTick_IntArm(uint32_t period, uint32_t priority){
  // write this

    i = 0; //WHY?

       SysTick->CTRL = 0;         // disable SysTick during initialization
       SysTick->LOAD = period - 1;  // set reload register

       SCB->SHP[1] = SCB->SHP[1]&(~0xC0000000)|priority<<30; // WHY??

       SysTick->VAL = 0;          // clear count, cause reload
       SysTick->CTRL = 0x0007;    // enable SysTick with core clock and interrupts

}


// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5 bit DAC
void Sound_Init(void){
// write this

    SysTick_IntArm(1, 1);

  
}
void SysTick_HandlerV2(void){ // called at 11 kHz
  // output one value to DAC if a sound is active
    if(i > 31){
        i = 0;
    }
    DAC5_Out(SinWave[i]);
    i++;
	
}

void SysTick_Handler(void){ // called at 11 kHz
  // output one value to DAC if a sound is active
    if(i > 64){
        i = 0;
    }
    DAC5_Out(Trumpet[i]);
    i++;

}

//******* Sound_Start ************
// This function does not output to the DAC. 
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement

/*

void Sound_Start(const uint8_t *pt, uint32_t count){
// write this
    SysTick->LOAD = count-1;  // reload value
    SysTick->VAL = 0;          // any write to current clears it
  
}

*/

void Sound_Start(uint32_t period){
  // write this
  // set reload value
  // write any value to VAL, cause reload

    SysTick->LOAD = period-1;  // reload value
    SysTick->VAL = 0;          // any write to current clears it

}




void Sound_Stop(void){
  // either set LOAD to 0 or clear bit 1 in CTRL
  // write this
    SysTick->LOAD = 0;  // Makes load a '0'
    //SysTick->CTRL = (SysTick->CTRL & ~(0x2)); // Clears the CTRL bit
}





void Sound_Shoot(void){
// write this
  
}
void Sound_Killed(void){
// write this
  
}
void Sound_Explosion(void){
// write this
 
}

void Sound_Fastinvader1(void){
  
}
void Sound_Fastinvader2(void){
  
}
void Sound_Fastinvader3(void){
  
}
void Sound_Fastinvader4(void){
  
}
void Sound_Highpitch(void){
  
}
