#include "block.h"
#include "resources.h"

Block * make_block(float x, float y, float width, float height, int health) {
  Block * block = (Block *)malloc(sizeof(Block));
  init_object(block);

  block->health = health;

  set_object_position(block, x, y);
  set_object_size(block, width, height);
  set_object_image(block, resources.block_bmp[block->health - 1]);

  return block;
}

void destroy_block(Block * block) {
  free(block);
  block = NULL;
}

void hit_block(Block * block) {
  if (block->health > 0) {
    block->health--;
    set_object_image(block, resources.block_bmp[block->health - 1]);
  }
}
