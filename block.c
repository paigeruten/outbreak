#include "block.h"

Block * make_block(int x, int y, int width, int height, Color color) {
  Block * block = (Block *)malloc(sizeof(Block));

  block->x = x;
  block->y = y;
  block->width = width;
  block->height = height;
  block->color = color;

  return block;
}

void destroy_block(Block * block) {
  free(block);
  block = NULL;
}

SDL_Rect block_rect(Block * block) {
  SDL_Rect b;

  b.x = block->x;
  b.y = block->y;
  b.w = block->width;
  b.h = block->height;

  return b;
}
