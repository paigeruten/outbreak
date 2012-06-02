#ifndef _palette_h
#define _palette_h

#include "main.h"

enum {
  COLOR_BLACK,
  COLOR_WHITE,

  NUM_COLORS
};

void init_palette(SDL_Surface * screen);

#endif

