#ifndef _ball_h
#define _ball_h

#include "main.h"
#include "object.h"
#include "palette.h"

typedef struct {
  Object object;
  int magnetized;
} Ball;

Ball * make_ball(float x, float y, float width, float height, SDL_Surface * image);
void destroy_ball(Ball * ball);
void launch_ball(Ball * ball);
void magnetize_ball(Ball * ball);
int ball_magnetized(Ball * ball);

#endif

