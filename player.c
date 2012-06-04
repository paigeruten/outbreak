#include "player.h"

Player * make_player(const char * name, float x, float y, int width, int height) {
  Player * player = (Player *)malloc(sizeof(Player));

  player->name = (char *)malloc(strlen(name) + 1);
  strcpy(player->name, name);

  player->x = x;
  player->y = y;
  player->width = width;
  player->height = height;

  return player;
}

void destroy_player(Player * player) {
  free(player->name);
  player->name = NULL;

  free(player);
  player = NULL;
}

SDL_Rect paddle_rect(Player * player) {
  SDL_Rect paddle;

  paddle.x = (int)player->x;
  paddle.y = (int)player->y;
  paddle.w = player->width;
  paddle.h = player->height;

  return paddle;
}

void move_paddle(Player * player) {
  player->x += player->velocity_x;

  // check for paddle collisions with edges of screen
  if (!contains(SCREEN_RECT, paddle_rect(player))) {
    player->x = (player->x < SCREEN_WIDTH / 2) ? 0 : SCREEN_WIDTH - player->width;
  }
}