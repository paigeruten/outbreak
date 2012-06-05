#ifndef _object_h
#define _object_h

#include "main.h"
#include "palette.h"

typedef struct {
  float x, y;
  float velocity_x, velocity_y;
  float acceleration_x, acceleration_y;
  float width, height;
  Color color;
  SDL_Surface * image;
} Object;

// getters
float object_x(void * object);
float object_y(void * object);
float object_velocity_x(void * object);
float object_velocity_y(void * object);
float object_acceleration_x(void * object);
float object_acceleration_y(void * object);
float object_width(void * object);
float object_height(void * object);
Color object_color(void * object);
SDL_Surface * object_image(void * object);
float object_angle(void * object);
float object_speed(void * object);
Direction object_direction_x(void * object);
Direction object_direction_y(void * object);

// setters
void init_object(void * object);
void set_object_x(void * object, float x);
void set_object_y(void * object, float y);
void set_object_position(void * object, float x, float y);
void set_object_velocity_x(void * object, float velocity_x);
void set_object_velocity_y(void * object, float velocity_y);
void set_object_velocity(void * object, float velocity_x, float velocity_y);
void set_object_acceleration_x(void * object, float acceleration_x);
void set_object_acceleration_y(void * object, float acceleration_y);
void set_object_acceleration(void * object, float acceleration_x, float acceleration_y);
void set_object_width(void * object, float width);
void set_object_height(void * object, float height);
void set_object_size(void * object, float width, float height);
void set_object_color(void * object, Color color);
void set_object_image(void * object, SDL_Surface * image);
void set_object_angle(void * object, float angle);
void set_object_speed(void * object, float speed);
void set_object_vector(void * object, float angle, float speed);

// helpers and predicates
SDL_Rect object_rect(void * object);
void object_render(void * object, SDL_Surface * surface);
int object_collision(void * object1, void * object2);
int object_offscreen(void * object);

// updaters
void object_update_x(void * object);
void object_update_y(void * object);
void object_update_position(void * object);
void object_rollback_x(void * object);
void object_rollback_y(void * object);
void object_rollback_position(void * object);
void object_update_velocity_x(void * object);
void object_update_velocity_y(void * object);
void object_update_velocity(void * object);
void object_update(void * object);
void object_bounce_x(void * object);
void object_bounce_y(void * object);

#endif
