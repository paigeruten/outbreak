#ifndef _block_h
#define _block_h

#include "main.h"
#include "object.h"
#include "palette.h"

typedef struct {
  Object object;
} Block;

Block * make_block(float x, float y, float width, float height, Color color);
void destroy_block(Block * block);

#endif
