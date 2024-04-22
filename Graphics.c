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
#include "images/images.h"
#include "Sound.h"
#include "Game.h"
#include "Graphics.h"

extern uint8_t SELECTORUPDATE;
extern uint8_t START;
extern uint8_t INITIAL;
extern uint32_t CURRARROW;

extern uint16_t score;
extern uint8_t combo;
extern uint8_t maxCombo;

extern uint32_t phase;



void graphicsUpdater(Sprite_t *playerSelector, Sprite_t *playerArrows){
    if(INITIAL == 1){
        drawSelector(playerSelector);
        drawplayerArrows(playerArrows);
    }
    if(SELECTORUPDATE == 1){
        drawSelector(playerSelector);
    }
    INITIAL = 0;
}



uint8_t SxOld = 0, SyOld = 0;
void drawSelector(Sprite_t *playerSelector){
    ST7735_DrawBitmap(SyOld, SxOld, oldSelector, playerSelector->h, playerSelector->w);

    ST7735_DrawBitmap(playerSelector->y, playerSelector->x, selector, playerSelector->h, playerSelector->w);
    SxOld = playerSelector->x;
    SyOld = playerSelector->y;
}

void drawplayerArrows(Sprite_t *playerArrows){
    ST7735_DrawBitmap(playerArrows->y, playerArrows->x, startArrows, playerArrows->h, playerArrows->w);
}

//28 by 28
void drawplayableArrow(Sprite_t *playableArrow){
    if(CURRARROW == 0){
        ST7735_DrawBitmap(7, 145, leftPressed, 28, 28);
    }
    if(CURRARROW == 1){
        ST7735_DrawBitmap(35, 145, upPressed, 28, 28);
    }
    if(CURRARROW == 2){
        ST7735_DrawBitmap(63, 145, downPressed, 28, 28);
    }
    if(CURRARROW == 3){
        ST7735_DrawBitmap(93, 145, rightPressed, 28, 28);
    }
}


void cpuGraphics(Sprite_t *leftCPUArrow){
    drawLeftCPU(leftCPUArrow, 100);
}



uint32_t Lcheck = 0;
void drawLeftCPU(Sprite_t *leftCPUArrow, uint32_t speed){
    if(leftCPUArrow->alive == 1){
    ST7735_DrawBitmap(7, leftCPUArrow->y, leftCPU, 28, 32);
    leftCPUArrow->y += 5;
    Clock_Delay1ms(speed); //25 smooth
    Lcheck = 0;
    }else if(leftCPUArrow->alive == 0 && Lcheck == 0){
        ST7735_DrawBitmap(7, leftCPUArrow->y, DleftCPU, 28, 32);
        Lcheck++;
    }
}

uint32_t Ucheck = 0;
void drawUpCPU(Sprite_t *UpCPUArrow, uint32_t speed){
    if(UpCPUArrow->alive == 1){
    ST7735_DrawBitmap(35, UpCPUArrow->y, upCPU, 28, 32);
    UpCPUArrow->y += 5;
    Clock_Delay1ms(speed); //25 smooth
    Ucheck = 0;
    }else if(UpCPUArrow->alive == 0 && Ucheck == 0){
        ST7735_DrawBitmap(35, UpCPUArrow->y, DleftCPU, 28, 32);
        Ucheck++;
    }
}

uint32_t Dcheck = 0;
void drawDownCPU(Sprite_t *DownCPUArrow, uint32_t speed){
    if(DownCPUArrow->alive == 1){
    ST7735_DrawBitmap(63, DownCPUArrow->y, downCPU, 28, 32);
    DownCPUArrow->y += 5;
    Clock_Delay1ms(speed); //25 smooth
    Dcheck = 0;
    }else if(DownCPUArrow->alive == 0 && Dcheck == 0){
        ST7735_DrawBitmap(63, DownCPUArrow->y, DleftCPU, 28, 32);
        Dcheck++;
    }
}

uint32_t Rcheck = 0;
void drawRightCPU(Sprite_t *RightCPUArrow, uint32_t speed){
    if(RightCPUArrow->alive == 1){
    ST7735_DrawBitmap(93, RightCPUArrow->y, rightCPU, 28, 32);
    RightCPUArrow->y += 5;
    Clock_Delay1ms(speed); //25 smooth
    Rcheck = 0;
    }else if(RightCPUArrow->alive == 0 && Rcheck == 0){
        ST7735_DrawBitmap(93, RightCPUArrow->y, DleftCPU, 28, 32);
        Rcheck++;
    }
}


void drawGameScore(uint16_t currScore){
    ST7735_SetCursor(0,0);
    printf("%d", currScore);
}







//MENU


void drawMenuL(){

    ST7735_SetCursor(6, 1);
    ST7735_OutString("319 BEATS");
    ST7735_SetCursor(3, 3);
    ST7735_OutString("CHOOSE LANGUAGE");
    ST7735_SetCursor(3, 5);
    ST7735_OutString("<< FOR ENGLISH");
    ST7735_SetCursor(3, 6);
    ST7735_OutString(">> FOR FRENCH");
}

void drawMenuLF(){

    ST7735_SetCursor(6, 1);
    ST7735_OutString("319 BEATS");
    ST7735_SetCursor(0, 3);
    ST7735_OutString("CHOISISSEZ LA LANGUE");
    ST7735_SetCursor(2, 5);
    ST7735_OutString("<< POUR L'ANGLAIS");
    ST7735_SetCursor(1, 6);
    ST7735_OutString(">> POUR LE FRANCAIS");//FRANÇAIS
}

void drawMainE(){

    ST7735_SetCursor(6, 1);
    ST7735_OutString("319 BEATS");
    ST7735_SetCursor(3, 3);
    ST7735_OutString("<< FOR PLAY");
    ST7735_SetCursor(2, 5);
    ST7735_OutString(">> FOR OPTIONS");
    ST7735_SetCursor(7, 9);
    ST7735_OutString("GAME BY");
    ST7735_SetCursor(4, 10);
    ST7735_OutString("ANISH AGARWAL");
    ST7735_SetCursor(4, 11);
    ST7735_OutString("VENTHAN DINESH");
}

void drawMainF(){

    ST7735_SetCursor(6, 1);
    ST7735_OutString("319 BEATS");
    ST7735_SetCursor(3, 3);
    ST7735_OutString("<< POUR JOUER");
    ST7735_SetCursor(1, 5);
    ST7735_OutString(">> POUR LES OPTIONS");
    ST7735_SetCursor(7, 9);
    ST7735_OutString("JEU PAR");
    ST7735_SetCursor(4, 10);
    ST7735_OutString("ANISH AGARWAL");
    ST7735_SetCursor(4, 11);
    ST7735_OutString("VENTHAN DINESH");
}

void drawOptionsE(){

    ST7735_SetCursor(7, 1);
    ST7735_OutString("OPTIONS");
    ST7735_SetCursor(2, 3);
    ST7735_OutString("<< CHANGE LANGUAGE");
    ST7735_SetCursor(3, 5);
    ST7735_OutString(">> CHOOSE LEVEL");
}

void drawOptionsF(){

    ST7735_SetCursor(7, 1);
    ST7735_OutString("OPTIONS");
    ST7735_SetCursor(0, 3);
    ST7735_OutString("<< CHANGER DE LANGUE");
    ST7735_SetCursor(1, 5);
    ST7735_OutString(">> CHOISISSEZ LE");
    ST7735_SetCursor(6, 6);
    ST7735_OutString("NIVEAU");
}

void drawLevelE(){

    ST7735_SetCursor(3, 1);
    ST7735_OutString("LEVEL SELECTION");
    ST7735_SetCursor(4, 3);
    ST7735_OutString("<< FIRST LEVEL");
    ST7735_SetCursor(4, 5);
    ST7735_OutString(">> SECOND LEVEL");
}

void drawLevelF(){

    ST7735_SetCursor(1, 1);
    ST7735_OutString("SELECTION DU NIVEAU"); //SÉLECTION DU NIVEAU
    ST7735_SetCursor(2, 3);
    ST7735_OutString("<< PREMIER NIVEAU");
    ST7735_SetCursor(2, 5);
    ST7735_OutString(">> DEUXIEME NIVEAU"); //DEUXIÈME NIVEAU
}
