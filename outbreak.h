#ifndef _outbreak_h
#define _outbreak_h

#include "main.h"
#include "player.h"

#define BACKGROUND_COLOR COLOR_BLACK

typedef struct {
  SDL_Surface * screen;
  Player * player;
  int quit;
} Outbreak;

void outbreak(SDL_Surface * screen);
void handle_input(Outbreak * outbreak);
void update_gamestate(Outbreak * outbreak);
void render(Outbreak * outbreak);

#endif

