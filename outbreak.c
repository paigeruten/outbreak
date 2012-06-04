#include "outbreak.h"
#include "palette.h"
#include "mathy.h"
#include "level.h"

void outbreak(SDL_Surface * screen) {
  Outbreak outbreak;
  init_outbreak(&outbreak, screen);

  while (!outbreak.quit) {
    handle_input(&outbreak);
    update_gamestate(&outbreak);
    render(&outbreak);

    SDL_Delay(1);
  }

  cleanup_outbreak(&outbreak);
}

void init_outbreak(Outbreak * outbreak, SDL_Surface * screen) {
  outbreak->screen = screen;
  outbreak->player = make_player("Jeremy", INITIAL_PADDLE_X, INITIAL_PADDLE_Y, INITIAL_PADDLE_WIDTH, INITIAL_PADDLE_HEIGHT);
  outbreak->ball = make_ball(INITIAL_BALL_X, INITIAL_BALL_Y, INITIAL_BALL_WIDTH, INITIAL_BALL_HEIGHT);
  outbreak->quit = FALSE;

  outbreak->ball->velocity_x = INITIAL_BALL_VELOCITY;
  outbreak->ball->velocity_y = INITIAL_BALL_VELOCITY;

  outbreak->num_blocks = generate_level(outbreak->blocks, MAX_BLOCKS);
}

void cleanup_outbreak(Outbreak * outbreak) {
  int i;
  for (i = 0; i < outbreak->num_blocks; i++) {
    destroy_block(outbreak->blocks[i]);
    outbreak->blocks[i] = NULL;
  }
  outbreak->num_blocks = 0;

  destroy_ball(outbreak->ball);
  outbreak->ball = NULL;

  destroy_player(outbreak->player);
  outbreak->player = NULL;
}

void add_block(Outbreak * outbreak, Block * block) {
  if (outbreak->num_blocks < MAX_BLOCKS) {
    outbreak->blocks[outbreak->num_blocks] = block;
    outbreak->num_blocks++;
  }
}

void remove_block(Outbreak * outbreak, Block * block) {
  int i;
  for (i = 0; i < outbreak->num_blocks; i++) {
    if (outbreak->blocks[i] == block) {
      int j;
      for (j = i; j < outbreak->num_blocks - 1; j++) {
        outbreak->blocks[j] = outbreak->blocks[j + 1];
      }
      outbreak->num_blocks--;
      break;
    }
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
  move_paddle(outbreak->player);

  move_ball_x(outbreak->ball);
  if (overlap(paddle_rect(outbreak->player), ball_rect(outbreak->ball))) {
    move_back_ball_x(outbreak->ball);
    bounce_ball_x(outbreak->ball);
  } else {
    int i;
    for (i = 0; i < outbreak->num_blocks; i++) {
      if (overlap(ball_rect(outbreak->ball), block_rect(outbreak->blocks[i]))) {
        remove_block(outbreak, outbreak->blocks[i]);
        move_back_ball_x(outbreak->ball);
        bounce_ball_x(outbreak->ball);
        break;
      }
    }
  }

  move_ball_y(outbreak->ball);
  if (outbreak->ball->y >= SCREEN_HEIGHT) {
    outbreak->quit = TRUE;
  } else if (overlap(paddle_rect(outbreak->player), ball_rect(outbreak->ball))) {
    move_back_ball_y(outbreak->ball);
    bounce_ball_y(outbreak->ball);
    adjust_ball_angle(outbreak->ball, ((outbreak->ball->x - outbreak->player->x) - (outbreak->player->width + outbreak->ball->width) / 2.0f) * PADDLE_CURVINESS);
  } else {
    int i;
    for (i = 0; i < outbreak->num_blocks; i++) {
      if (overlap(ball_rect(outbreak->ball), block_rect(outbreak->blocks[i]))) {
        remove_block(outbreak, outbreak->blocks[i]);
        move_back_ball_y(outbreak->ball);
        bounce_ball_y(outbreak->ball);
        break;
      }
    }
  }

  ball_increase_speed(outbreak->ball);
}

void render(Outbreak * outbreak) {
  // clear screen
  SDL_FillRect(outbreak->screen, NULL, BACKGROUND_COLOR);

  // draw paddle
  SDL_Rect paddle = paddle_rect(outbreak->player);
  SDL_FillRect(outbreak->screen, &paddle, PADDLE_COLOR);

  // draw blocks
  int i;
  SDL_Rect block;
  for (i = 0; i < outbreak->num_blocks; i++) {
    block = block_rect(outbreak->blocks[i]);
    SDL_FillRect(outbreak->screen, &block, outbreak->blocks[i]->color);
  }

  // draw ball
  SDL_Rect ball = ball_rect(outbreak->ball);
  SDL_FillRect(outbreak->screen, &ball, BALL_COLOR);

  SDL_UpdateRect(outbreak->screen, 0, 0, 0, 0);
}

