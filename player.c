#include "player.h"

Player * make_player(const char * name, float x, float y, float width, float height, Color color) {
  Player * player = (Player *)malloc(sizeof(Player));
  init_object(player);

  player->name = (char *)malloc(strlen(name) + 1);
  strcpy(player->name, name);

  set_object_position(player, x, y);
  set_object_size(player, width, height);
  set_object_color(player, color);

  return player;
}

void destroy_player(Player * player) {
  free(player->name);
  player->name = NULL;

  free(player);
  player = NULL;
}
