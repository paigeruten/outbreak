#include "object.h"
#include "mathy.h"

// getters

float object_x(void * object) {
  return ((Object *)object)->x;
}

float object_y(void * object) {
  return ((Object *)object)->y;
}

float object_velocity_x(void * object) {
  return ((Object *)object)->velocity_x;
}

float object_velocity_y(void * object) {
  return ((Object *)object)->velocity_y;
}

float object_acceleration_x(void * object) {
  return ((Object *)object)->acceleration_x;
}

float object_acceleration_y(void * object) {
  return ((Object *)object)->acceleration_y;
}

float object_width(void * object) {
  return ((Object *)object)->width;
}

float object_height(void * object) {
  return ((Object *)object)->height;
}

Color object_color(void * object) {
  return ((Object *)object)->color;
}

SDL_Surface * object_image(void * object) {
  return ((Object *)object)->image;
}

float object_angle(void * object) {
  return atan2(-object_velocity_y(object), object_velocity_x(object));
}

float object_speed(void * object) {
  return sqrt(square(object_velocity_y(object)) + square(object_velocity_x(object)));
}

Direction object_direction_x(void * object) {
  if (object_velocity_x(object) < 0) {
    return DIRECTION_LEFT;
  } else if (object_velocity_x(object) > 0) {
    return DIRECTION_RIGHT;
  } else {
    return DIRECTION_NONE;
  }
}

Direction object_direction_y(void * object) {
  if (object_velocity_y(object) < 0) {
    return DIRECTION_UP;
  } else if (object_velocity_y(object) > 0) {
    return DIRECTION_DOWN;
  } else {
    return DIRECTION_NONE;
  }
}

// setters

void init_object(void * object) {
  set_object_position(object, 0, 0);
  set_object_velocity(object, 0, 0);
  set_object_acceleration(object, 0, 0);
  set_object_size(object, 1, 1);
  set_object_color(object, BACKGROUND_COLOR);
  set_object_image(object, NULL);
}

void set_object_x(void * object, float x) {
  ((Object *)object)->x = x;
}

void set_object_y(void * object, float y) {
  ((Object *)object)->y = y;
}

void set_object_position(void * object, float x, float y) {
  set_object_x(object, x);
  set_object_y(object, y);
}

void set_object_velocity_x(void * object, float velocity_x) {
  ((Object *)object)->velocity_x = velocity_x;
}

void set_object_velocity_y(void * object, float velocity_y) {
  ((Object *)object)->velocity_y = velocity_y;
}

void set_object_velocity(void * object, float velocity_x, float velocity_y) {
  set_object_velocity_x(object, velocity_x);
  set_object_velocity_y(object, velocity_y);
}

void set_object_acceleration_x(void * object, float acceleration_x) {
  ((Object *)object)->acceleration_x = acceleration_x;
}

void set_object_acceleration_y(void * object, float acceleration_y) {
  ((Object *)object)->acceleration_y = acceleration_y;
}

void set_object_acceleration(void * object, float acceleration_x, float acceleration_y) {
  set_object_acceleration_x(object, acceleration_x);
  set_object_acceleration_y(object, acceleration_y);
}

void set_object_width(void * object, float width) {
  ((Object *)object)->width = width;
}

void set_object_height(void * object, float height) {
  ((Object *)object)->height = height;
}

void set_object_size(void * object, float width, float height) {
  set_object_width(object, width);
  set_object_height(object, height);
}

void set_object_color(void * object, Color color) {
  set_object_image(object, NULL);
  ((Object *)object)->color = color;
}

void set_object_image(void * object, SDL_Surface * image) {
  ((Object *)object)->image = image;
}

void set_object_angle(void * object, float angle) {
  set_object_vector(object, angle, object_speed(object));
}

void set_object_speed(void * object, float speed) {
  set_object_vector(object, object_angle(object), speed);
}

void set_object_vector(void * object, float angle, float speed) {
  set_object_velocity_x(object, cos(angle) * speed);
  set_object_velocity_y(object, -sin(angle) * speed);
}

// helpers and predicates

SDL_Rect object_rect(void * object) {
  SDL_Rect rect;

  rect.x = (int)object_x(object);
  rect.y = (int)object_y(object);
  rect.w = (int)object_width(object);
  rect.h = (int)object_height(object);

  return rect;
}

void object_render(void * object, SDL_Surface * surface) {
  SDL_Rect rect = object_rect(object);

  if (object_image(object) == NULL) {
    SDL_FillRect(surface, &rect, object_color(object));
  } else {
    SDL_BlitSurface(object_image(object), NULL, surface, &rect);
  }
}

int object_collision(void * object1, void * object2) {
  return overlap(object_rect(object1), object_rect(object2));
}

int object_offscreen(void * object) {
  return !contains(SCREEN_RECT, object_rect(object));
}

// updaters

void object_update_x(void * object) {
  set_object_x(object, object_x(object) + object_velocity_x(object));
}

void object_update_y(void * object) {
  set_object_y(object, object_y(object) + object_velocity_y(object));
}

void object_update_position(void * object) {
  object_update_x(object);
  object_update_y(object);
}

void object_rollback_x(void * object) {
  set_object_x(object, object_x(object) - object_velocity_x(object));
}

void object_rollback_y(void * object) {
  set_object_y(object, object_y(object) - object_velocity_y(object));
}

void object_rollback_position(void * object) {
  object_rollback_x(object);
  object_rollback_y(object);
}

void object_update_velocity_x(void * object) {
  set_object_velocity_x(object, object_velocity_x(object) + object_acceleration_x(object));
}

void object_update_velocity_y(void * object) {
  set_object_velocity_y(object, object_velocity_y(object) + object_acceleration_y(object));
}

void object_update_velocity(void * object) {
  object_update_velocity_x(object);
  object_update_velocity_y(object);
}

void object_update(void * object) {
  object_update_position(object);
  object_update_velocity(object);
}

void object_bounce_x(void * object) {
  set_object_velocity_x(object, -object_velocity_x(object));
}

void object_bounce_y(void * object) {
  set_object_velocity_y(object, -object_velocity_y(object));
}
