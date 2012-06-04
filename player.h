#ifndef _player_h
#define _player_h

#include "main.h"

typedef struct {
  char * name;
  float x;
  float y;
  float velocity_x;
  int width, height;
} Player;

Player * make_player(const char * name, float x, float y, int width, int height);
void destroy_player(Player * player);
SDL_Rect paddle_rect(Player * player);

#endif

