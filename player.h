#ifndef _player_h
#define _player_h

#include "main.h"
#include "object.h"
#include "palette.h"

typedef struct {
  Object object;
  char * name;
} Player;

Player * make_player(const char * name, float x, float y, float width, float height, SDL_Surface * image);
void destroy_player(Player * player);

#endif

