#include "outbreak.h"
#include "palette.h"
#include "mathy.h"
#include "controls.h"

void outbreak(SDL_Surface * screen) {
  Outbreak outbreak;
  outbreak.screen = screen;
  outbreak.player = make_player("Jeremy", (float)SCREEN_WIDTH / 2.0f - (float)PADDLE_WIDTH / 2.0f, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT);
  outbreak.ball = make_ball(outbreak.player->x + (float)outbreak.player->width / 2.0f - (float)BALL_WIDTH / 2.0f, outbreak.player->y - BALL_HEIGHT - 1, BALL_WIDTH, BALL_HEIGHT);
  outbreak.quit = FALSE;

  outbreak.ball->velocity_x = BALL_VELOCITY;
  outbreak.ball->velocity_y = BALL_VELOCITY;

  outbreak.num_blocks = 0;

  // make a simple wall-of-bricks level
  int block_x;
  int block_y;
  for (block_y = BLOCKS_Y; block_y < BLOCKS_Y + (BLOCK_HEIGHT + BLOCK_SPACING) * BLOCK_ROWS && outbreak.num_blocks < MAX_BLOCKS; block_y += BLOCK_HEIGHT + BLOCK_SPACING) {
    for (block_x = BLOCKS_X; block_x < SCREEN_WIDTH - BLOCK_WIDTH - BLOCKS_X && outbreak.num_blocks < MAX_BLOCKS; block_x += BLOCK_WIDTH + BLOCK_SPACING) {
      outbreak.blocks[outbreak.num_blocks] = make_block(block_x, block_y, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_COLOR);
      outbreak.num_blocks++;
    }
  }

  while (!outbreak.quit) {
    handle_input(&outbreak);
    update_gamestate(&outbreak);
    render(&outbreak);

    SDL_Delay(1);
  }

  int i;
  for (i = 0; i < outbreak.num_blocks; i++) {
    destroy_block(outbreak.blocks[i]);
    outbreak.blocks[i] = NULL;
  }
  outbreak.num_blocks = 0;

  destroy_ball(outbreak.ball);
  outbreak.ball = NULL;

  destroy_player(outbreak.player);
  outbreak.player = NULL;
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
  } else if (overlap(paddle_rect(outbreak->player), ball_rect(outbreak->ball))) {
    outbreak->ball->x -= outbreak->ball->velocity_x;
    outbreak->ball->velocity_x = -outbreak->ball->velocity_x;
  } else {
    int i;
    for (i = 0; i < outbreak->num_blocks; i++) {
      if (overlap(ball_rect(outbreak->ball), block_rect(outbreak->blocks[i]))) {
        remove_block(outbreak, outbreak->blocks[i]);
        outbreak->ball->x -= outbreak->ball->velocity_x;
        outbreak->ball->velocity_x = -outbreak->ball->velocity_x;
        break;
      }
    }
  }

  outbreak->ball->y += outbreak->ball->velocity_y;
  if (outbreak->ball->y < 0) {
    outbreak->ball->y = 0;
    outbreak->ball->velocity_y = -outbreak->ball->velocity_y;
  } else if (outbreak->ball->y > SCREEN_HEIGHT - outbreak->ball->height) {
    outbreak->quit = TRUE;
  } else if (overlap(paddle_rect(outbreak->player), ball_rect(outbreak->ball))) {
    outbreak->ball->y -= outbreak->ball->velocity_y;
    outbreak->ball->velocity_y = -outbreak->ball->velocity_y;

    float ball_angle = atan2(outbreak->ball->velocity_y, outbreak->ball->velocity_x);
    float ball_magnitude = sqrt(square(outbreak->ball->velocity_y) + square(outbreak->ball->velocity_x));

    ball_angle += ((outbreak->ball->x - outbreak->player->x) - (float)(outbreak->player->width + outbreak->ball->width) / 2.0f) / 64.0f;

    outbreak->ball->velocity_x = cos(ball_angle) * ball_magnitude;
    outbreak->ball->velocity_y = sin(ball_angle) * ball_magnitude;
  } else {
    int i;
    for (i = 0; i < outbreak->num_blocks; i++) {
      if (overlap(ball_rect(outbreak->ball), block_rect(outbreak->blocks[i]))) {
        remove_block(outbreak, outbreak->blocks[i]);
        outbreak->ball->y -= outbreak->ball->velocity_y;
        outbreak->ball->velocity_y = -outbreak->ball->velocity_y;
        break;
      }
    }
  }

  // gradually speed up ball
  outbreak->ball->velocity_x += outbreak->ball->velocity_x * BALL_VELOCITY_PERCENT_INCREASE;
  outbreak->ball->velocity_y += outbreak->ball->velocity_y * BALL_VELOCITY_PERCENT_INCREASE;
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

