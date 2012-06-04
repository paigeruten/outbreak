#include "block.h"

const Color BLOCK_COLOR_CYCLE[BLOCK_MAX_HEALTH + 1] = {
  BACKGROUND_COLOR,
  COLOR_RED,
  COLOR_ORANGE,
  COLOR_YELLOW,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_MAGENTA
};

Block * make_block(float x, float y, float width, float height, int health) {
  Block * block = (Block *)malloc(sizeof(Block));
  init_object(block);

  block->health = health;

  set_object_position(block, x, y);
  set_object_size(block, width, height);
  set_object_color(block, BLOCK_COLOR_CYCLE[block->health]);

  return block;
}

void destroy_block(Block * block) {
  free(block);
  block = NULL;
}

void hit_block(Block * block) {
  if (block->health > 0) {
    block->health--;
    set_object_color(block, BLOCK_COLOR_CYCLE[block->health]);
  }
}