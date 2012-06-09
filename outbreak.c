#include "outbreak.h"
#include "palette.h"
#include "mathy.h"
#include "level.h"
#include "object.h"
#include "resources.h"

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
  outbreak->player = make_player("Jeremy", INITIAL_PADDLE_X, INITIAL_PADDLE_Y, INITIAL_PADDLE_WIDTH, INITIAL_PADDLE_HEIGHT, resources.paddle_bmp);
  outbreak->ball = make_ball(INITIAL_BALL_X, INITIAL_BALL_Y, INITIAL_BALL_WIDTH, INITIAL_BALL_HEIGHT, resources.ball_bmp);
  outbreak->paused = FALSE;
  outbreak->quit = FALSE;

  set_object_vector(outbreak->ball, INITIAL_BALL_ANGLE, INITIAL_BALL_SPEED);

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
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == CONTROLS_PAUSE) {
      outbreak->paused = !outbreak->paused;
    } else if (event.type == SDL_QUIT) {
      outbreak->quit = TRUE;
    }

    if (!outbreak->paused) {
      switch(event.type) {
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == CONTROLS_RIGHT) {
            set_object_velocity_x(outbreak->player, PADDLE_VELOCITY);
          } else if (event.key.keysym.sym == CONTROLS_LEFT) {
            set_object_velocity_x(outbreak->player, -PADDLE_VELOCITY);
          }
          break;

        case SDL_KEYUP:
          if (event.key.keysym.sym == CONTROLS_RIGHT) {
            if (object_direction_x(outbreak->player) == DIRECTION_RIGHT) {
              set_object_velocity_x(outbreak->player, 0);
            }
          } else if (event.key.keysym.sym == CONTROLS_LEFT) {
            if (object_direction_x(outbreak->player) == DIRECTION_LEFT) {
              set_object_velocity_x(outbreak->player, 0);
            }
          }
          break;

        case SDL_MOUSEMOTION:
          set_object_velocity_x(outbreak->player, 0);
          set_object_x(outbreak->player, event.motion.x - object_width(outbreak->player) / 2);
          if (object_offscreen(outbreak->player)) {
            set_object_x(outbreak->player, object_x(outbreak->player) < 0 ? 0 : SCREEN_WIDTH - object_width(outbreak->player));
          }
          break;
      }
    }
  }
}

void update_gamestate(Outbreak * outbreak) {
  if (!outbreak->paused) {
    object_update_position(outbreak->player);
    if (object_offscreen(outbreak->player)) {
      set_object_x(outbreak->player, (object_direction_x(outbreak->player) == DIRECTION_LEFT) ? 0 : SCREEN_WIDTH - object_width(outbreak->player));
    }

    object_update_x(outbreak->ball);
    if (object_offscreen(outbreak->ball)) {
      set_object_x(outbreak->ball, (object_direction_x(outbreak->ball) == DIRECTION_LEFT) ? 0 : SCREEN_WIDTH - object_width(outbreak->ball));
      object_bounce_x(outbreak->ball);
    } else if (object_collision(outbreak->player, outbreak->ball)) {
      object_rollback_x(outbreak->ball);
      object_bounce_x(outbreak->ball);
    } else {
      int i;
      for (i = 0; i < outbreak->num_blocks; i++) {
        if (object_collision(outbreak->ball, outbreak->blocks[i])) {
          hit_block(outbreak->blocks[i]);
          if (outbreak->blocks[i]->health == 0) {
            remove_block(outbreak, outbreak->blocks[i]);
          }
          object_rollback_x(outbreak->ball);
          object_bounce_x(outbreak->ball);
          break;
        }
      }
    }

    object_update_y(outbreak->ball);
    if (object_y(outbreak->ball) >= SCREEN_HEIGHT) {
      outbreak->quit = TRUE;
    } else if (object_y(outbreak->ball) < 0) {
      set_object_y(outbreak->ball, 0);
      object_bounce_y(outbreak->ball);
    } else if (object_collision(outbreak->player, outbreak->ball)) {
      object_rollback_y(outbreak->ball);
      object_bounce_y(outbreak->ball);
      set_object_angle(outbreak->ball, object_angle(outbreak->ball) + ((object_x(outbreak->ball) - object_x(outbreak->player)) - (object_width(outbreak->player) + object_width(outbreak->ball)) / 2.0f) * PADDLE_CURVINESS);
    } else {
      int i;
      for (i = 0; i < outbreak->num_blocks; i++) {
        if (object_collision(outbreak->ball, outbreak->blocks[i])) {
          hit_block(outbreak->blocks[i]);
          if (outbreak->blocks[i]->health == 0) {
            remove_block(outbreak, outbreak->blocks[i]);
          }
          object_rollback_y(outbreak->ball);
          object_bounce_y(outbreak->ball);
          break;
        }
      }
    }

    set_object_speed(outbreak->ball, object_speed(outbreak->ball) + BALL_ACCELERATION);
  }
}

void render(Outbreak * outbreak) {
  if (!outbreak->paused) {
    // clear screen
    SDL_FillRect(outbreak->screen, NULL, BACKGROUND_COLOR);

    // draw paddle
    object_render(outbreak->player, outbreak->screen);

    // draw blocks
    int i;
    for (i = 0; i < outbreak->num_blocks; i++) {
      object_render(outbreak->blocks[i], outbreak->screen);
    }

    // draw ball
    object_render(outbreak->ball, outbreak->screen);
  }

  SDL_UpdateRect(outbreak->screen, 0, 0, 0, 0);
}

