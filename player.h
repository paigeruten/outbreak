#ifndef _player_h
#define _player_h

#include "main.h"

#define PADDLE_WIDTH 64
#define PADDLE_HEIGHT 8

#define PADDLE_MARGIN_Y 64
#define PADDLE_Y (SCREEN_HEIGHT - PADDLE_HEIGHT - PADDLE_MARGIN_Y)

#define PADDLE_COLOR COLOR_WHITE

typedef struct {
  char * name;
  SDL_Rect paddle;
} Player;

Player * make_player(const char * name, int x, int y, int width, int height);
void destroy_player(Player * player);

#endif

