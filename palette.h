#ifndef _palette_h
#define _palette_h

#include "main.h"

typedef enum {
  COLOR_BLACK,
  COLOR_WHITE,
  COLOR_RED,
  COLOR_BLUE,
  COLOR_ORANGE,

  NUM_COLORS
} Color;

void init_palette(SDL_Surface * screen);

#endif

