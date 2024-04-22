

#ifndef GAME_H_
#define GAME_H_


struct Sprite
{
  uint8_t x;
  uint8_t y;
  uint32_t *image; // pointer to image
  uint8_t h, w;    // height and width of sprite
  int8_t speed;
  int8_t orientation;


  int8_t alive;
  int8_t dead;
};
typedef struct Sprite Sprite_t;

void playerArrowsInit(Sprite_t *player);

void selectorInit(Sprite_t *selector);

void updateSelectorCoords(Sprite_t *Sprite);




void cpuInit(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU); //CPU STUFF

void collisionChecker(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU);

void levelOne(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU);

void levelTwo(Sprite_t *leftCPU, Sprite_t *upCPU, Sprite_t *downCPU, Sprite_t *rightCPU);




void noteSelector();

void menuHandler();

void menuSelection();

#endif /* GAME_H_ */
