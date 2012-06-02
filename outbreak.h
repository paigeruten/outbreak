#ifndef _outbreak_h
#define _outbreak_h

#include "main.h"

typedef struct {
  SDL_Surface * screen;
  int quit;
} Outbreak;

void outbreak(SDL_Surface * screen);
void handle_input(Outbreak * outbreak);
void update_gamestate(Outbreak * outbreak);
void render(Outbreak * outbreak);

#endif

