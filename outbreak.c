#include "outbreak.h"
#include "palette.h"
#include "controls.h"

void outbreak(SDL_Surface * screen) {
  Outbreak outbreak;
  outbreak.screen = screen;
  outbreak.player = make_player("Jeremy", (float)SCREEN_WIDTH / 2.0f - (float)PADDLE_WIDTH / 2.0f, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT);
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
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == CONTROLS_RIGHT) {
          outbreak->player->velocity_x = PADDLE_VELOCITY;
        } else if (event.key.keysym.sym == CONTROLS_LEFT) {
          outbreak->player->velocity_x = -PADDLE_VELOCITY;
        }
        break;

      case SDL_KEYUP:
        if (event.key.keysym.sym == CONTROLS_RIGHT) {
          if (outbreak->player->velocity_x > 0) {
            outbreak->player->velocity_x = 0;
          }
        } else if (event.key.keysym.sym == CONTROLS_LEFT) {
          if (outbreak->player->velocity_x < 0) {
            outbreak->player->velocity_x = 0;
          }
        }
        break;

      case SDL_QUIT:
        outbreak->quit = TRUE;
        break;
    }
  }
}

void update_gamestate(Outbreak * outbreak) {
  outbreak->player->x += outbreak->player->velocity_x;
}

void render(Outbreak * outbreak) {
  // clear screen
  SDL_FillRect(outbreak->screen, NULL, BACKGROUND_COLOR);

  // draw paddle
  SDL_Rect paddle = paddle_rect(outbreak->player);
  SDL_FillRect(outbreak->screen, &paddle, PADDLE_COLOR);

  SDL_UpdateRect(outbreak->screen, 0, 0, 0, 0);
}

