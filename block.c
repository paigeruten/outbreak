#include "block.h"

Block * make_block(float x, float y, float width, float height, Color color) {
  Block * block = (Block *)malloc(sizeof(Block));
  init_object(block);

  set_object_position(block, x, y);
  set_object_size(block, width, height);
  set_object_color(block, color);

  return block;
}

void destroy_block(Block * block) {
  free(block);
  block = NULL;
}
