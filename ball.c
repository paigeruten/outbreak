#include "ball.h"

Ball * make_ball(float x, float y, float width, float height, SDL_Surface * image) {
  Ball * ball = (Ball *)malloc(sizeof(Ball));
  init_object(ball);

  set_object_position(ball, x, y);
  set_object_size(ball, width, height);
  set_object_image(ball, image);

  return ball;
}

void destroy_ball(Ball * ball) {
  free(ball);
  ball = NULL;
}

void launch_ball(Ball * ball) {
  ball->magnetized = FALSE;
  set_object_vector(ball, INITIAL_BALL_ANGLE, INITIAL_BALL_SPEED);
}

void magnetize_ball(Ball * ball) {
  ball->magnetized = TRUE;
  set_object_velocity(ball, 0, 0);
}

int ball_magnetized(Ball * ball) {
  return ball->magnetized;
}
