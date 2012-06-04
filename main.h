#ifndef _main_h
#define _main_h

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>

#define TRUE 1
#define FALSE 0

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 8

// controls
#define CONTROLS_RIGHT SDLK_RIGHT
#define CONTROLS_LEFT SDLK_LEFT

// blocks
#define MAX_BLOCKS 512
#define BLOCK_ROWS 8
#define BLOCK_WIDTH 30
#define BLOCK_HEIGHT 14
#define BLOCK_SPACING 2
#define BLOCKS_X 64
#define BLOCKS_Y 64

// ball
#define BALL_WIDTH 5
#define BALL_HEIGHT 5
#define BALL_VELOCITY 2
#define BALL_VELOCITY_PERCENT_INCREASE 0.0001

// paddle
#define PADDLE_WIDTH 64
#define PADDLE_HEIGHT 8
#define PADDLE_MARGIN_Y 64
#define PADDLE_Y (SCREEN_HEIGHT - PADDLE_HEIGHT - PADDLE_MARGIN_Y)
#define PADDLE_VELOCITY 5

// colors
#define BACKGROUND_COLOR COLOR_BLACK
#define BLOCK_COLOR COLOR_ORANGE
#define PADDLE_COLOR COLOR_WHITE
#define BALL_COLOR COLOR_WHITE

#endif

