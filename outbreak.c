#include "outbreak.h"

void outbreak(SDL_Surface * screen) {
  int quit = FALSE;

  while (!quit) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          quit = TRUE;
          break;
      }
    }

    SDL_Delay(1);
  }
}

