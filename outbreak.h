#ifndef _outbreak_h
#define _outbreak_h

#include "main.h"
#include "block.h"
#include "player.h"
#include "ball.h"

typedef struct {
  SDL_Surface * screen;
  Block * blocks[MAX_BLOCKS];
  Player * player;
  Ball * ball;
  int num_blocks;
  int paused;
  int quit;
} Outbreak;

void outbreak(SDL_Surface * screen);
void init_outbreak(Outbreak * outbreak, SDL_Surface * screen);
void cleanup_outbreak(Outbreak * outbreak);
void add_block(Outbreak * outbreak, Block * block);
void remove_block(Outbreak * outbreak, Block * block);
void handle_input(Outbreak * outbreak);
void update_gamestate(Outbreak * outbreak);
void render(Outbreak * outbreak);

#endif

