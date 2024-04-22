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




    // 3) move sprites

    // 4) start sounds
    // 5) set semaphore
    Flag = 0;

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
            }else {
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
                //ADD IT
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















typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<= French; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}



// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);




/*
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
*/



/*

  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black


  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);

*/

  drawMenuL();
  Clock_Delay1ms(2500);
  ST7735_FillScreen(0x0000);
  drawMenuLF();
  Clock_Delay1ms(2500);
  ST7735_FillScreen(0x0000);
  drawMainE();
  Clock_Delay1ms(2500);
  ST7735_FillScreen(0x0000);
  drawMainF();
  Clock_Delay1ms(2500);
  ST7735_FillScreen(0x0000);
  drawOptionsE();
  Clock_Delay1ms(2500);
  ST7735_FillScreen(0x0000);
  drawOptionsF();
  Clock_Delay1ms(2500);
  ST7735_FillScreen(0x0000);
  drawLevelE();
  Clock_Delay1ms(2500);
  ST7735_FillScreen(0x0000);
  drawLevelF();



  while(1){

  }
}










// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    
  }
}





// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2);
  // initialize all data structures
  __enable_irq();

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}
