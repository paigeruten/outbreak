#include "ball.h"

Ball * make_ball(float x, float y, int width, int height) {
  Ball * ball = (Ball *)malloc(sizeof(Ball));

  ball->x = x;
  ball->y = y;
  ball->velocity_x = 0;
  ball->velocity_y = 0;
  ball->width = width;
  ball->height = height;

  return ball;
}

void destroy_ball(Ball * ball) {
  free(ball);
  ball = NULL;
}

SDL_Rect ball_rect(Ball * ball) {
  SDL_Rect b;

  b.x = (int)ball->x;
  b.y = (int)ball->y;
  b.w = ball->width;
  b.h = ball->height;

  return b;
}

