#include "player.h"

Player * make_player(const char * name, int x, int y, int width, int height) {
  Player * player = (Player *)malloc(sizeof(Player));

  player->name = (char *)malloc(strlen(name) + 1);
  strcpy(player->name, name);

  player->paddle.x = x;
  player->paddle.y = y;
  player->paddle.w = width;
  player->paddle.h = height;

  return player;
}

void destroy_player(Player * player) {
  free(player->name);
  player->name = NULL;

  free(player);
  player = NULL;
}

