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

#define R3D (1 << 17)
#define YEL (1 << 28)
#define GRN (1 << 31)

#define UP (1<<24)
#define DWN (1<<26)
#define LFT (1<<25)
#define RT (1<<27)
#define SP (1<<16)

#define A03  1855   // 440 Hz
#define E   1238   // 659.3 Hz
#define F   1169   // 698.5 Hz
#define G    1041   // 784 Hz
#define C03  1560   // 523.3 Hz
#define D   1390   // 587.3 Hz
#define A    928   // 880 Hz
#define C    780   // 1046.5 Hz
#define B 855
#define C2 2389
#define D2 2255
#define E2 1896
#define G2 1594


uint8_t SELECTORUPDATE;
uint32_t CURRARROW;

 uint16_t score;
 uint8_t combo;
 uint8_t maxCombo;

 uint32_t sPos;


 extern uint8_t FMENUE; //first menu AND language selection menu
 extern uint8_t FMENUF;
 extern uint8_t MMENUE; //main menu
 extern uint8_t MMENUF;
 extern uint8_t OMENUE;//options menu
 extern uint8_t OMENUF;
 extern uint8_t LMENUE;//level menu
 extern uint8_t LMENUF;
 extern uint32_t switchData;

 extern uint8_t START;
 extern uint8_t MENU;
 extern uint8_t LANG; //1 for french and 0 for english
 extern uint8_t LEVEL;




void playerArrowsInit(Sprite_t *player){  //Initializes player
    player->x = 150;
    player->y = 0;
    player->h = 128;
    player->w = 32;
}

void selectorInit(Sprite_t *selector){  //Initializes selector
    selector->x = 155;
    selector->y = 9;
    selector->h = 26;
    selector->w = 3;
}


void updateSelectorCoords(Sprite_t *Sprite){

    uint32_t currPos = Sprite -> y;

    uint32_t Data = ADCin();
    sPos = Convert(Data);

    // sPos should go from 200 to 2100

    if((0 <= sPos) && (sPos < 675) && (currPos != 9)){
        Sprite->y = 9;
        SELECTORUPDATE =1;
        CURRARROW = 0;
    }
    else if((675 <= sPos) && (sPos < 1150) && (currPos != 37)){
        Sprite->y = 37;
        SELECTORUPDATE =1;
        CURRARROW = 1;
    }
    else if((1150 <= sPos) && (sPos < 1625) && (currPos != 68)){
        Sprite->y = 68;
        SELECTORUPDATE =1;
        CURRARROW = 2;
    }
    else if((1625 <= sPos) && (currPos != 98)){
        Sprite->y = 98;
        SELECTORUPDATE =1;
        CURRARROW = 3;
    }
    else{
        SELECTORUPDATE =0;
    }

}



void cpuInit(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU){
    leftCPU->y = 0;
    leftCPU->alive = 1;
    upCPU->y = 0;
    upCPU->alive = 1;
    downCPU->y = 0;
    downCPU->alive = 1;
    rightCPU->y = 0;
    rightCPU->alive = 1;
}


uint16_t onlyOnce = 0;

void collisionChecker(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU){



    if(CURRARROW == 0 && switchData == UP && (leftCPU->y <= 150 && leftCPU->y >= 144)){
        leftCPU->alive = 0;
        score++;
        Clock_Delay1ms(100);
    }
    if(leftCPU->y >= 200){
        leftCPU->alive = 0;
    }
    if(CURRARROW == 1 && switchData == UP && (upCPU->y <= 150 && upCPU->y >= 144)){
        upCPU->alive = 0;
        score++;
        Clock_Delay1ms(100);
    }
    if(upCPU->y >= 200){
        upCPU->alive = 0;
    }
    if(CURRARROW == 2 && switchData == UP && (downCPU->y <= 150 && downCPU->y >= 144)){
        downCPU->alive = 0;
        score++;
        Clock_Delay1ms(100);
    }
    if(downCPU->y >= 200){
        downCPU->alive = 0;
    }
    if(CURRARROW == 3 && switchData == UP && (rightCPU->y <= 150 && rightCPU->y >= 144)){
        rightCPU->alive = 0;
        score++;
        Clock_Delay1ms(100);
    }
    if(rightCPU->y >= 200){
        rightCPU->alive = 0;
    }





}





uint32_t phase = 0;
uint32_t goAgain = 0;
void levelOne(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU){

    if(switchData == LFT){ //RESETS DATA IF LEFT BUTTON PRESSED
            ST7735_FillScreen(ST7735_BLACK);
                        START = 0;
                        LANG = 0;
                        LEVEL = 1;
                        Sound_Stop();
                        MENU = 1;

                        FMENUE =1;
                        FMENUF =0;
                        MMENUE =0;
                        MMENUF=0;
                        OMENUE=0;
                        OMENUF=0;
                        LMENUE=0;
                        LMENUF=0;

                        phase = 0;
                        goAgain = 0;
                        score = 0;
                        leftCPU->y = 0;
                        leftCPU->alive = 1;
                        upCPU->y = 0;
                        upCPU->alive = 1;
                        downCPU->y = 0;
                        downCPU->alive = 1;
                        rightCPU->y = 0;
                        rightCPU->alive = 1;
        }

    if(phase == 0 && leftCPU->alive ==1){
        drawLeftCPU(leftCPU, 100);
    }else if(phase == 0 && leftCPU->alive == 0 ){
        phase++;
        if(phase == 1){
            leftCPU->alive = 1;
            leftCPU->y = 0;
            phase++;
        }
    }
    if(phase == 2 && (leftCPU->alive ==1 || upCPU->alive ==1)){
            drawLeftCPU(leftCPU,25);
            if(leftCPU->y > 50) drawUpCPU(upCPU, 50);
    }else if(phase == 2 && (leftCPU->alive == 0)){
        phase++;
        leftCPU->alive = 1;
        leftCPU->y = 0;
    }
    if(phase == 3 && (leftCPU->alive ==1 || upCPU->alive ==1)){
        drawUpCPU(upCPU, 50);
        if(upCPU->y > 50) drawLeftCPU(leftCPU,50);
    }
    if(phase == 3 && (leftCPU->alive ==0)){
        phase++;
        leftCPU->y = 0;
        leftCPU->alive = 1;
        upCPU->y = 0;
        upCPU->alive = 1;
        downCPU->y = 0;
        downCPU->alive = 1;
        rightCPU->y = 0;
        rightCPU->alive = 1;
    }
    if(phase == 4 && (downCPU->alive ==1 ||rightCPU->alive ==1 )){
        drawDownCPU(downCPU, 60);
        if(downCPU->alive ==1){
        if(downCPU->y > 50) drawRightCPU(rightCPU,30);
        }else{
            drawRightCPU(rightCPU,60);
        }
    }

    if(phase == 4 && (downCPU->alive ==0 && rightCPU->alive ==0 )){
        phase++;
    }

    if(phase == 5 && goAgain == 0){
        phase = 0;
        goAgain++;
    }



    if(goAgain == 1 && phase ==5){
        goAgain++;
        phase = 6;
        leftCPU->y = 0;
        leftCPU->alive = 1;
        upCPU->y = 0;
        upCPU->alive = 1;
        downCPU->y = 0;
        downCPU->alive = 1;
        rightCPU->y = 0;
        rightCPU->alive = 1;
    }
    if(phase == 6 && leftCPU->alive == 1){
        drawLeftCPU(leftCPU,30);
    }else if(phase == 6 && leftCPU->alive == 0){
        phase++;
        leftCPU->alive = 1;
        leftCPU->y = 0;
    }

    if(phase == 7 && leftCPU->alive == 1){
        drawLeftCPU(leftCPU,30);
    }else if(phase == 7 && leftCPU->alive == 0){
        phase++;
        leftCPU->alive = 1;
        leftCPU->y = 0;
    }

    if(phase == 8 && leftCPU->alive == 1){
        drawLeftCPU(leftCPU,30);
    }else if(phase == 8 && leftCPU->alive == 0){
        phase++;
        leftCPU->y = 0;
        leftCPU->alive = 1;
        upCPU->y = 0;
        upCPU->alive = 1;
        downCPU->y = 0;
        downCPU->alive = 1;
        rightCPU->y = 0;
        rightCPU->alive = 1;
    }

    if(phase == 9 && (upCPU->alive == 1 || downCPU->alive == 1)){
        drawUpCPU(upCPU, 50);
        if(upCPU->y > 50) drawDownCPU(downCPU,25);
    }else if(phase == 9 && (upCPU->alive == 0 && downCPU->alive == 0)){
        phase++;
    }

    if(phase == 10){
        if(LANG == 0){
        ST7735_SetCursor(6, 1);
        ST7735_OutString("GAME OVER");
        ST7735_SetCursor(6, 3);
        printf("Score: %d", score);
        ST7735_SetCursor(3, 5);
        ST7735_OutString("Press Any Button");
        ST7735_SetCursor(5, 6);
        ST7735_OutString("To Restart");
        }
        else if(LANG == 1){
            ST7735_SetCursor(6, 1);
            ST7735_OutString("JEU TERMINE");
            ST7735_SetCursor(6, 3);
            printf("Score: %d", score);
            ST7735_SetCursor(4, 5);
            ST7735_OutString("Appuyer Sur Un");
            ST7735_SetCursor(1, 6);
            ST7735_OutString("Bouton Recommencer");
        }


        if(switchData != 0){
            ST7735_FillScreen(ST7735_BLACK);
            START = 0;
            LANG = 0;
            LEVEL = 1;
            Sound_Stop();
            MENU = 1;

            FMENUE =1;
            FMENUF =0;
            MMENUE =0;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            phase = 0;
            goAgain = 0;
            score = 0;
            leftCPU->y = 0;
            leftCPU->alive = 1;
            upCPU->y = 0;
            upCPU->alive = 1;
            downCPU->y = 0;
            downCPU->alive = 1;
            rightCPU->y = 0;
            rightCPU->alive = 1;
        }
    }






    /*
    drawLeftCPU(leftCPU);
    if(leftCPU->y > 50) drawDownCPU(downCPU);
    if(downCPU->y > 50) drawUpCPU(upCPU);
    if(upCPU->y > 50) drawRightCPU(rightCPU);
    */

}




uint32_t phase2 = 0;
uint32_t repeat3 = 0;
void levelTwo(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU){

    if(switchData == LFT){ //RESETS DATA IF LEFT BUTTON PRESSED
        ST7735_FillScreen(ST7735_BLACK);
                    START = 0;
                    LANG = 0;
                    LEVEL = 1;
                    Sound_Stop();
                    MENU = 1;

                    FMENUE =1;
                    FMENUF =0;
                    MMENUE =0;
                    MMENUF=0;
                    OMENUE=0;
                    OMENUF=0;
                    LMENUE=0;
                    LMENUF=0;

                    phase = 0;
                    goAgain = 0;
                    score = 0;
                    leftCPU->y = 0;
                    leftCPU->alive = 1;
                    upCPU->y = 0;
                    upCPU->alive = 1;
                    downCPU->y = 0;
                    downCPU->alive = 1;
                    rightCPU->y = 0;
                    rightCPU->alive = 1;
    }



    if (phase2 == 0 && (downCPU->alive == 1 || upCPU->alive == 1 || leftCPU->alive == 1)) {
        drawDownCPU(downCPU, 100);
        if (downCPU->y > 50) { drawUpCPU(upCPU, 50); }
        if (upCPU->y > 50) { drawLeftCPU(leftCPU, 30); }
    } else if(phase2 == 0 && downCPU->alive == 0 && leftCPU->alive == 0 && upCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
        upCPU->alive = 1;
        upCPU->y = 0;
        leftCPU->alive = 1;
        leftCPU->y = 0;
    }
    if (phase2 == 1 && (downCPU->alive == 1 || upCPU->alive == 1)) {
            drawUpCPU(upCPU, 120);
            if (upCPU->y > 50) { drawDownCPU(downCPU, 60); }
    } else if (phase2 == 1 && downCPU->alive == 0 && upCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
        upCPU->alive = 1;
        upCPU->y = 0;
    }
    if (phase2 == 2 && downCPU->alive == 1) {
        drawDownCPU(downCPU, 100);
    }
    if (phase2 == 2 && downCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
    }
    if (phase2 == 3 && downCPU->alive == 1) {
        drawDownCPU(downCPU, 100);
    }
    if (phase2 == 3 && downCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
    }

    if (phase2 == 4 && upCPU->alive == 1) {
        drawUpCPU(upCPU, 100);
    }
    if (phase2 == 4 && upCPU->alive == 0) {
        phase2++;
        upCPU->alive = 1;
        upCPU->y = 0;
    }
    if (phase2 == 5 && upCPU->alive == 1) {
        drawUpCPU(upCPU, 100);
    }
    if (phase2 == 5 && upCPU->alive == 0) {
        phase2++;
        upCPU->alive = 1;
        upCPU->y = 0;
    }
    if (phase2 == 6 && (upCPU->alive == 1 || downCPU->alive == 1 || rightCPU->alive == 1)) {
        drawUpCPU(upCPU, 100);
        if (upCPU->y > 50) { drawDownCPU(downCPU, 30); }
        if (downCPU->y > 50) { drawRightCPU(rightCPU, 30); }
    }
    if (phase2 == 6 && upCPU->alive == 0 && downCPU->alive == 0 && rightCPU->alive == 0 ) {
        phase2++;
        upCPU->alive = 1;
        upCPU->y = 0;
        downCPU->alive = 1;
        downCPU->y = 0;
        rightCPU->alive = 1;
        rightCPU->y = 0;
    }
    if (phase2 == 7 && rightCPU->alive == 1) {
        drawRightCPU(rightCPU, 100);
    }
    if (phase2 == 7 && rightCPU->alive == 0) {
        phase2++;
        rightCPU->alive = 1;
        rightCPU->y = 0;
    }

    if (phase2 == 8 && (downCPU->alive == 1 || upCPU->alive == 1 || leftCPU->alive == 1)) {
        drawDownCPU(downCPU, 100);
        if (downCPU->y > 50) { drawUpCPU(upCPU, 50); }
        if (upCPU->y > 50) { drawLeftCPU(leftCPU, 30); }
    } else if(phase2 == 8 && downCPU->alive == 0 && leftCPU->alive == 0 && upCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
        upCPU->alive = 1;
        upCPU->y = 0;
        leftCPU->alive = 1;
        leftCPU->y = 0;
    }
    if (phase2 == 9 && (downCPU->alive == 1 || upCPU->alive == 1)) {
            drawUpCPU(upCPU, 120);
            if (upCPU->y > 50) { drawDownCPU(downCPU, 60); }
    } else if (phase2 == 9 && downCPU->alive == 0 && upCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
        upCPU->alive = 1;
        upCPU->y = 0;
    }
    if (phase2 == 10 && downCPU->alive == 1) {
        drawDownCPU(downCPU, 100);
    }
    if (phase2 == 10 && downCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
    }
    if (phase2 == 11 && downCPU->alive == 1) {
        drawDownCPU(downCPU, 100);
    }
    if (phase2 == 11 && downCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
    }

    if (phase2 == 12 && (downCPU->alive == 1 || upCPU->alive == 1)) {
        drawDownCPU(downCPU, 100);
        if (downCPU->y > 50) { drawUpCPU(upCPU, 50); }
    }
    if (phase2 == 12 && downCPU->alive == 0 && upCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
        upCPU->alive = 1;
        upCPU->y = 0;
    }
    if (phase2 == 13 && (downCPU->alive == 1 || upCPU->alive == 1)) {
        drawUpCPU(upCPU, 100);
        if (upCPU->y > 50) { drawDownCPU(downCPU, 50); }
    }
    if (phase2 == 13 && downCPU->alive == 0 && upCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
        upCPU->alive = 1;
        upCPU->y = 0;
    }
    if (phase2 == 14 && (downCPU->alive == 1 || upCPU->alive == 1 || leftCPU->alive == 1)) {
        drawUpCPU(upCPU, 100);
        if (upCPU->y > 50) { drawDownCPU(downCPU, 50); }
        if (downCPU->y > 50) { drawLeftCPU(leftCPU, 50); }
    }
    if (phase2 == 14 && downCPU->alive == 0 && upCPU->alive == 0 && leftCPU->alive == 0) {
        phase2++;
        downCPU->alive = 1;
        downCPU->y = 0;
        upCPU->alive = 1;
        upCPU->y = 0;
        leftCPU->alive = 1;
        leftCPU->y = 0;
    }

    if(phase2 == 15){
        if(LANG == 0){
        ST7735_SetCursor(6, 1);
        ST7735_OutString("GAME OVER");
        ST7735_SetCursor(6, 3);
        printf("Score: %d", score);
        ST7735_SetCursor(3, 5);
        ST7735_OutString("Press Any Button");
        ST7735_SetCursor(5, 6);
        ST7735_OutString("To Restart");
        }
        else if(LANG == 1){
            ST7735_SetCursor(6, 1);
            ST7735_OutString("JEU TERMINE");
            ST7735_SetCursor(6, 3);
            printf("Score: %d", score);
            ST7735_SetCursor(4, 5);
            ST7735_OutString("Appuyer Sur Un");
            ST7735_SetCursor(1, 6);
            ST7735_OutString("Bouton Recommencer");
        }


        if(switchData != 0){
            ST7735_FillScreen(ST7735_BLACK);
            START = 0;
            LANG = 0;
            LEVEL = 1;
            Sound_Stop();
            MENU = 1;

            FMENUE =1;
            FMENUF =0;
            MMENUE =0;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            phase = 0;
            goAgain = 0;
            score = 0;
            leftCPU->y = 0;
            leftCPU->alive = 1;
            upCPU->y = 0;
            upCPU->alive = 1;
            downCPU->y = 0;
            downCPU->alive = 1;
            rightCPU->y = 0;
            rightCPU->alive = 1;
        }

    }
}



//SELECTION OF SOUND

void noteSelector(){
    if (LEVEL == 1) {
        if(CURRARROW == 0){
            Sound_Start(G);
        }else if(CURRARROW == 1){
            Sound_Start(A);
        }else if(CURRARROW == 2){
            Sound_Start(C);
        }else if(CURRARROW == 3){
            Sound_Start(B);
        }
    } else if (LEVEL == 2) {
        if(CURRARROW == 0){
            Sound_Start(C);
        }else if(CURRARROW == 1){
            Sound_Start(D);
        }else if(CURRARROW == 2){
            Sound_Start(E);
        }else if(CURRARROW == 3){
            Sound_Start(G);
        }
    }

}








//MENU


uint8_t checker = 1;

void menuHandler(){
    if(MENU == 0){
        ST7735_FillScreen(ST7735_BLACK);
    }

    if(FMENUE){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawMenuL();
        Clock_Delay1ms(250);
    }
    else if(FMENUF){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawMenuLF();
        Clock_Delay1ms(250);
    }
    else if(MMENUE){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawMainE();
        Clock_Delay1ms(250);
    }
    else if(MMENUF){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawMainF();
        Clock_Delay1ms(250);
    }
    else if(OMENUE){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawOptionsE();
        Clock_Delay1ms(250);
    }
    else if(OMENUF){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawOptionsF();
        Clock_Delay1ms(250);
    }
    else if(LMENUE){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawLevelE();
        Clock_Delay1ms(250);
    }
    else if(LMENUF){
        if(checker == 1){
        ST7735_FillScreen(ST7735_BLACK);
        checker--;
        }
        drawLevelF();
        Clock_Delay1ms(250);
    }
}




void menuSelection(){
    if(FMENUE){
        if(switchData == UP){//FRENCH
            FMENUE =0;
            FMENUF =0;
            MMENUE =0;
            MMENUF=1;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            LANG = 1;

            checker = 1;
        }
        if(switchData == LFT){//ENGLISH
            FMENUE =0;
            FMENUF =0;
            MMENUE =1;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            checker = 1;
        }
    }
    else if(FMENUF){
        if(switchData == UP){//FRENCH
            FMENUE =0;
            FMENUF =0;
            MMENUE =0;
            MMENUF=1;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            checker = 1;
        }
        if(switchData == LFT){//ENGLISH
            FMENUE =0;
            FMENUF =0;
            MMENUE =1;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            checker = 1;
        }
    }




    else if(MMENUE){
        if(switchData == UP){
            FMENUE =0;
            FMENUF =0;
            MMENUE =0;
            MMENUF=0;
            OMENUE=1;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            checker = 1;
        }
        if(switchData == LFT){                  //PLAYS GAME
            ST7735_FillScreen(ST7735_BLACK);
            MENU = 0;
            START = 1;
        }
    }
    else if(OMENUE){
        if(switchData == UP){
            FMENUE =0;
            FMENUF =0;
            MMENUE =0;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=1;
            LMENUF=0;

            checker = 1;
        }
        if(switchData == LFT){
            FMENUE =1;
            FMENUF =0;
            MMENUE =0;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            checker = 1;
        }
    }
    else if(LMENUE){
        if(switchData == UP){ //ADD LEVEL IMPLEMNTATION
            FMENUE =0;
            FMENUF =0;
            MMENUE =1;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            LEVEL = 2;

            checker = 1;
        }
        if(switchData == LFT){ //ADD LEVEL IMPLEMNTATION
            FMENUE =0;
            FMENUF =0;
            MMENUE =1;
            MMENUF=0;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            LEVEL = 1;

            checker = 1;
        }
    }
    else if(MMENUF){                    //FRENCG MENUES
        if(switchData == UP){
            FMENUE =0;
            FMENUF =0;
            MMENUE =0;
            MMENUF=0;
            OMENUE=0;
            OMENUF=1;
            LMENUE=0;
            LMENUF=0;

            checker = 1;
        }
        if(switchData == LFT){ //PLAYS GAME
            ST7735_FillScreen(ST7735_BLACK);
            MENU = 0;
            START = 1;
        }
    }
    else if(OMENUF){
            if(switchData == UP){
                FMENUE =0;
                FMENUF =0;
                MMENUE =0;
                MMENUF=0;
                OMENUE=0;
                OMENUF=0;
                LMENUE=0;
                LMENUF=1;

                checker = 1;
            }
            if(switchData == LFT){
                FMENUE =0;
                FMENUF =1;
                MMENUE =0;
                MMENUF=0;
                OMENUE=0;
                OMENUF=0;
                LMENUE=0;
                LMENUF=0;

                checker = 1;
            }
    }
    else if(LMENUF){
        if(switchData == UP){ //ADD LEVEL IMPLEMNTATION
            FMENUE =0;
            FMENUF =0;
            MMENUE =0;
            MMENUF=1;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            LEVEL = 2;

            checker = 1;
        }
        if(switchData == LFT){ //ADD LEVEL IMPLEMNTATION
            FMENUE =0;
            FMENUF =0;
            MMENUE =0;
            MMENUF=1;
            OMENUE=0;
            OMENUF=0;
            LMENUE=0;
            LMENUF=0;

            LEVEL = 1;

            checker = 1;
        }
    }






}
