#ifndef _outbreak_h
#define _outbreak_h

#include "main.h"
#include "block.h"
#include "player.h"
#include "ball.h"

#define MAX_BLOCKS 512

#define BLOCK_ROWS 8

#define BLOCK_WIDTH 30
#define BLOCK_HEIGHT 14
#define BLOCK_SPACING 2

#define BLOCKS_X 64
#define BLOCKS_Y 64

#define BACKGROUND_COLOR COLOR_BLACK
#define BLOCK_COLOR COLOR_ORANGE

typedef struct {
  SDL_Surface * screen;
  Block * blocks[MAX_BLOCKS];
  Player * player;
  Ball * ball;
  int num_blocks;
  int quit;
} Outbreak;

void outbreak(SDL_Surface * screen);
void handle_input(Outbreak * outbreak);
void update_gamestate(Outbreak * outbreak);
void render(Outbreak * outbreak);

#endif

