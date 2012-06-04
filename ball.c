#include "ball.h"

Ball * make_ball(float x, float y, float width, float height, Color color) {
  Ball * ball = (Ball *)malloc(sizeof(Ball));
  init_object(ball);

  set_object_position(ball, x, y);
  set_object_size(ball, width, height);
  set_object_color(ball, color);

  return ball;
}

void destroy_ball(Ball * ball) {
  free(ball);
  ball = NULL;
}
