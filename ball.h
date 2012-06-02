#ifndef _ball_h
#define _ball_h

#include "main.h"

#define BALL_WIDTH 5
#define BALL_HEIGHT 5

#define BALL_COLOR COLOR_WHITE

typedef struct {
  float x;
  float y;
  float velocity_x;
  float velocity_y;
  int width;
  int height;
} Ball;

Ball * make_ball(float x, float y, int width, int height);
void destroy_ball(Ball * ball);
SDL_Rect ball_rect(Ball * ball);

#endif

