#include "resources.h"

Resources resources;

void load_resources(const char * path_to_resources) {
  if ((resources.paddle_bmp = load_image(path_to_resources, "paddle.bmp")) == NULL) {
    error_loading_resource("paddle.bmp");
  }
  if ((resources.ball_bmp = load_image(path_to_resources, "ball.bmp")) == NULL) {
    error_loading_resource("ball.bmp");
  }
}

void error_loading_resource(const char * file) {
  fprintf(stderr, "Can't load image %s: %s\n", file, SDL_GetError());
  exit(1);
}

SDL_Surface * load_image(const char * path_to_resources, const char * filename) {
  char * path = (char *)malloc(strlen(path_to_resources) + strlen(filename) + 2);
  strcpy(path, path_to_resources);
  if (path[strlen(path) - 1] != '/') {
    strcat(path, "/");
  }
  strcat(path, filename);

  SDL_Surface * image = SDL_LoadBMP(path);

  free(path);
  path = NULL;

  return image;
}