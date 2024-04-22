/*
 * Switch.c
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"

#define UP (1<<24)
#define DWN (1<<26)
#define LFT (1<<25)
#define RT (1<<27)

#define SP  (1<<18)

// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    // write this
    IOMUX->SECCFG.PINCM[PA24INDEX] = 0x00040081; // input
    IOMUX->SECCFG.PINCM[PA25INDEX] = 0x00040081; // input
    IOMUX->SECCFG.PINCM[PA26INDEX] = 0x00040081; // input
    IOMUX->SECCFG.PINCM[PA27INDEX] = 0x00040081; // input
    IOMUX->SECCFG.PINCM[PB16INDEX] = 0x00040081; // input

    //GPIOA->DOE31_0 |= 0x01<<24;

}
// return current state of switches
uint32_t Switch_In(void){
    uint32_t testS = GPIOA->DIN31_0;

    uint32_t test2 = UP + DWN + LFT + RT;

    uint32_t testU = UP;
    uint32_t testD = DWN;
    uint32_t testL = LFT;
    uint32_t testR = RT;

    return (GPIOA->DIN31_0 & (UP + DWN + LFT + RT));

    return GPIOA->DIN31_0 & UP;
}

