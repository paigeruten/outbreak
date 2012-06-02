#include "outbreak.h"
#include "palette.h"

void outbreak(SDL_Surface * screen) {
  Outbreak outbreak;
  outbreak.screen = screen;
  outbreak.quit = FALSE;

  while (!outbreak.quit) {
    handle_input(&outbreak);
    update_gamestate(&outbreak);
    render(&outbreak);

    SDL_Delay(1);
  }
}

void handle_input(Outbreak * outbreak) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        outbreak->quit = TRUE;
        break;
    }
  }
}

void update_gamestate(Outbreak * outbreak) {

}

void render(Outbreak * outbreak) {
  SDL_FillRect(outbreak->screen, NULL, COLOR_WHITE);
  SDL_UpdateRect(outbreak->screen, 0, 0, 0, 0);
}

