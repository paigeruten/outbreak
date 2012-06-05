#ifndef _resources_h
#define _resources_h

#include "main.h"

typedef struct {
  SDL_Surface * paddle_bmp;
  SDL_Surface * ball_bmp;
} Resources;

extern Resources resources;

void load_resources(const char * path_to_resources);
void error_loading_resource(const char * file);
SDL_Surface * load_image(const char * path_to_resources, const char * filename);

#endif
