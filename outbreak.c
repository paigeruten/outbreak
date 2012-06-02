#include "outbreak.h"
#include "palette.h"
#include "mathy.h"
#include "controls.h"

void outbreak(SDL_Surface * screen) {
  Outbreak outbreak;
  outbreak.screen = screen;
  outbreak.player = make_player("Jeremy", (float)SCREEN_WIDTH / 2.0f - (float)PADDLE_WIDTH / 2.0f, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT);
  outbreak.ball = make_ball((float)SCREEN_WIDTH / 2.0f - (float)BALL_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f - (float)BALL_HEIGHT / 2.0f, BALL_WIDTH, BALL_HEIGHT);
  outbreak.quit = FALSE;

  outbreak.ball->velocity_x = BALL_VELOCITY;
  outbreak.ball->velocity_y = BALL_VELOCITY;

  while (!outbreak.quit) {
    handle_input(&outbreak);
    update_gamestate(&outbreak);
    render(&outbreak);

    SDL_Delay(1);
  }

  destroy_ball(outbreak.ball);
  outbreak.ball = NULL;

  destroy_player(outbreak.player);
  outbreak.player = NULL;
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

  if (outbreak->player->x < 0) {
    outbreak->player->x = 0;
  }

  if (outbreak->player->x > SCREEN_WIDTH - outbreak->player->width) {
    outbreak->player->x = SCREEN_WIDTH - outbreak->player->width;
  }

  outbreak->ball->x += outbreak->ball->velocity_x;
  if (outbreak->ball->x < 0) {
    outbreak->ball->x = 0;
    outbreak->ball->velocity_x = -outbreak->ball->velocity_x;
  } else if (outbreak->ball->x > SCREEN_WIDTH - outbreak->ball->width) {
    outbreak->ball->x = SCREEN_WIDTH - outbreak->ball->width;
    outbreak->ball->velocity_x = -outbreak->ball->velocity_x;
  }

  outbreak->ball->y += outbreak->ball->velocity_y;
  if (outbreak->ball->y < 0) {
    outbreak->ball->y = 0;
    outbreak->ball->velocity_y = -outbreak->ball->velocity_y;
  } else if (outbreak->ball->y > SCREEN_HEIGHT - outbreak->ball->height) {
    outbreak->quit = TRUE;
  }

  if (overlap(paddle_rect(outbreak->player), ball_rect(outbreak->ball))) {
    outbreak->ball->velocity_y = -outbreak->ball->velocity_y;
  }
}

void render(Outbreak * outbreak) {
  // clear screen
  SDL_FillRect(outbreak->screen, NULL, BACKGROUND_COLOR);

  // draw paddle
  SDL_Rect paddle = paddle_rect(outbreak->player);
  SDL_FillRect(outbreak->screen, &paddle, PADDLE_COLOR);

  // draw ball
  SDL_Rect ball = ball_rect(outbreak->ball);
  SDL_FillRect(outbreak->screen, &ball, BALL_COLOR);

  SDL_UpdateRect(outbreak->screen, 0, 0, 0, 0);
}

