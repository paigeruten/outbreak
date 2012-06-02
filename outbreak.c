#include "outbreak.h"
#include "palette.h"

void outbreak(SDL_Surface * screen) {
  Outbreak outbreak;
  outbreak.screen = screen;
  outbreak.player = make_player("Jeremy", SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT);
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
  // clear screen
  SDL_FillRect(outbreak->screen, NULL, BACKGROUND_COLOR);

  // draw paddle
  SDL_FillRect(outbreak->screen, &outbreak->player->paddle, PADDLE_COLOR);

  SDL_UpdateRect(outbreak->screen, 0, 0, 0, 0);
}

