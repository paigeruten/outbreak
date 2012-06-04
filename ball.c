#include "ball.h"
#include "mathy.h"

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

void move_ball_x(Ball * ball) {
  ball->x += ball->velocity_x;

  // check for ball collisions with edges of screen
  if (!contains(SCREEN_RECT, ball_rect(ball))) {
    ball->x = (ball->x < SCREEN_WIDTH / 2) ? 0 : SCREEN_WIDTH - ball->width;
    bounce_ball_x(ball);
  }
}

void move_ball_y(Ball * ball) {
  ball->y += ball->velocity_y;

  if (ball->y < 0) {
    ball->y = 0;
    bounce_ball_y(ball);
  }
}

void move_back_ball_x(Ball * ball) {
  ball->x -= ball->velocity_x;
}

void move_back_ball_y(Ball * ball) {
  ball->y -= ball->velocity_y;
}

void bounce_ball_x(Ball * ball) {
  ball->velocity_x = -ball->velocity_x;
}

void bounce_ball_y(Ball * ball) {
  ball->velocity_y = -ball->velocity_y;
}

float ball_angle(Ball * ball) {
  return atan2(ball->velocity_y, ball->velocity_x);
}

float ball_speed(Ball * ball) {
  return sqrt(square(ball->velocity_y) + square(ball->velocity_x));
}

void set_ball_vector(Ball * ball, float angle, float speed) {
  ball->velocity_x = cos(angle) * speed;
  ball->velocity_y = sin(angle) * speed;
}

void adjust_ball_angle(Ball * ball, float amount) {
  set_ball_vector(ball, ball_angle(ball) + amount, ball_speed(ball));
}

void ball_increase_speed(Ball * ball) {
  ball->velocity_x += ball->velocity_x * BALL_VELOCITY_PERCENT_INCREASE;
  ball->velocity_y += ball->velocity_y * BALL_VELOCITY_PERCENT_INCREASE;
}
