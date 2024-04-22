/*
 * Graphics.h
 *
 *  Created on: Apr 14, 2024
 *      Author: Anish Agarwal's Dell
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

void graphicsUpdater(Sprite_t *playerSelector, Sprite_t *playerArrows);

void drawplayerArrows(Sprite_t *playerArrows);

void drawSelector(Sprite_t *playerSelector);

void drawplayableArrow(Sprite_t *playableArrow);


//CPU STUFF
void cpuGraphics(Sprite_t *leftCPUArrow);

void drawLeftCPU(Sprite_t *leftCPUArrow, uint32_t speed);
void drawUpCPU(Sprite_t *UpCPUArrow, uint32_t speed);
void drawDownCPU(Sprite_t *DownCPUArrow, uint32_t speed);
void drawRightCPU(Sprite_t *RightCPUArrow, uint32_t speed);


void drawGameScore(uint16_t currScore);

void drawMenuL();
void drawMenuLF();

void drawMainE();
void drawMainF();

void drawOptionsE();
void drawOptionsF();

void drawLevelE();
void drawLevelF();


#endif /* GRAPHICS_H_ */
