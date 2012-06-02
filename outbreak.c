#include "outbreak.h"
#include "palette.h"

void outbreak(SDL_Surface * screen) {
  int quit = FALSE;

  SDL_FillRect(screen, NULL, COLOR_WHITE);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

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

