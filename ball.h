#ifndef _ball_h
#define _ball_h

#include "main.h"

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
void move_ball_x(Ball * ball);
void move_ball_y(Ball * ball);
void move_back_ball_x(Ball * ball);
void move_back_ball_y(Ball * ball);
void bounce_ball_x(Ball * ball);
void bounce_ball_y(Ball * ball);
float ball_angle(Ball * ball);
float ball_speed(Ball * ball);
void set_ball_vector(Ball * ball, float angle, float speed);
void adjust_ball_angle(Ball * ball, float amount);
void ball_increase_speed(Ball * ball);

#endif

