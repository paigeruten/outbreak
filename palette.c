#include "palette.h"

void init_palette(SDL_Surface * screen) {
  SDL_Color colors[NUM_COLORS];

  colors[COLOR_BLACK] = (SDL_Color){ 0x00, 0x00, 0x00 };
  colors[COLOR_WHITE] = (SDL_Color){ 0xFF, 0xFF, 0xFF };

  SDL_SetColors(screen, colors, 0, NUM_COLORS);
}

