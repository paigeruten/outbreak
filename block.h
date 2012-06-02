#ifndef _block_h
#define _block_h

#include "main.h"
#include "palette.h"

typedef struct {
  int x;
  int y;
  int width;
  int height;
  Color color;
} Block;

Block * make_block(int x, int y, int width, int height, Color color);
void destroy_block(Block * block);
SDL_Rect block_rect(Block * block);

#endif
