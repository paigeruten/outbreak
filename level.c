#include "level.h"

int generate_level(Block * blocks[], int n) {
  // make a simple wall-of-bricks level
  int block_x;
  int block_y;
  int num_blocks = 0;
  for (block_y = BLOCKS_Y; block_y < BLOCKS_Y + (BLOCK_HEIGHT + BLOCK_SPACING) * BLOCK_ROWS && num_blocks < n; block_y += BLOCK_HEIGHT + BLOCK_SPACING) {
    for (block_x = BLOCKS_X; block_x < SCREEN_WIDTH - BLOCK_WIDTH - BLOCKS_X && num_blocks < n; block_x += BLOCK_WIDTH + BLOCK_SPACING) {
      blocks[num_blocks] = make_block(block_x, block_y, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_COLOR);
      num_blocks++;
    }
  }
  return num_blocks;
}
