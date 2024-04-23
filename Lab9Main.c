// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: 12/31/2023

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "Game.h"
#include "Graphics.h"
#include "Lab9Main.h"


//#include "images/images.h"

 uint32_t Flag;
 uint32_t Data;



 extern uint16_t score;
 uint8_t combo;
 uint8_t maxCombo;

 uint32_t switchData;

uint32_t UP = (1<<24);
uint32_t LFT = (1<<25);

Sprite_t playerArrows;
Sprite_t playerSelector;
Sprite_t pressedArrow;

Sprite_t cpuLeft;
Sprite_t cpuUp;
Sprite_t cpuDown;
Sprite_t cpuRight;




uint8_t START;
uint8_t INITIAL;
uint8_t MENU;
uint8_t LANG; //1 for french and 0 for English
uint8_t LEVEL;

uint8_t FMENUE; //first menu AND language selection menu
uint8_t FMENUF;
uint8_t MMENUE; //main menu
uint8_t MMENUF;
uint8_t OMENUE;//options menu
uint8_t OMENUF;
uint8_t LMENUE;//level menu
uint8_t LMENUF;

extern uint8_t checker;

uint32_t lastSwitchIN = 0;
uint32_t HAHALOL = 0;
uint32_t oneTime = 1;










// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}





// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    Data = ADCin();

    // 2) read input switches
    switchData = Switch_In();

    if(START){
        if(switchData == UP){
            noteSelector();
            //Sound_Start(10726); (FOR DEBUG)
        }else {
            Sound_Stop();
        }
    }



    // 5) set semaphore
    Flag = 0;                                                                       //maybe use late

    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}


int main(void) { // main
    __disable_irq();
    PLL_Init();
    LaunchPad_Init();
    TimerG12_IntArm(80000000 / 30, 2);                // initialize interrupts on TimerG12 at 30 Hz
    __enable_irq();
    fullInit();
    gameInit();
    while (1) {

        if(MENU){
            menuHandler();
            menuSelection();
        }

        if(START){
            if(switchData == UP){
                drawplayableArrow(&pressedArrow);
            }else if(switchData == LFT){
                drawAll(&pressedArrow);
            }
            else {
                drawplayerArrows(&playerArrows);
            }
        }



        if(START){
            collisionChecker(&cpuLeft, &cpuUp, &cpuDown, &cpuRight);
            drawGameScore(score);
            if(LEVEL == 1){
            levelOne(&cpuLeft, &cpuUp, &cpuDown, &cpuRight);
            }
            if(LEVEL == 2){
                levelTwo(&cpuLeft, &cpuUp, &cpuDown, &cpuRight);
            }
            graphicsUpdater(&playerSelector, &playerArrows);
            INITIAL = 0;
            updateSelectorCoords(&playerSelector);
        }




        Clock_Delay(800000); // 10ms, to debounce switch

    }
}




void gameInit(){
    ST7735_FillScreen(ST7735_BLACK);
    playerArrowsInit(&playerArrows);
    selectorInit(&playerSelector);

    cpuInit(&cpuLeft, &cpuUp, &cpuDown, &cpuRight);

    score = 0;
    combo = 0;
    maxCombo = 0;
    START = 0;                      //CHANGE TO 0 WHEN ACTUAL GAME TIME
    INITIAL = 1;
    MENU = 1;                       //CHANGE TO 1 WHEN ACTUAL GAME
    LANG = 0; //1 for frnch
    LEVEL = 1;

    FMENUE =1;
    FMENUF =0;
    MMENUE =0;
    MMENUF=0;
    OMENUE=0;
    OMENUF=0;
    LMENUE=0;
    LMENUF=0;
}

void fullInit(){
    ST7735_InitPrintf();
    ST7735_FillScreen(ST7735_BLACK);
    ADCinit();
    Switch_Init();                                    // initialize switches
    LED_Init();                                       // initialize LED
    DAC5_Init();     // DAC initialization
    Sound_Init();                                     // initialize sound
    TExaS_Init(0, 0, &TExaS_LaunchPadLogicPB27PB26);  // PB27 and PB26
}













