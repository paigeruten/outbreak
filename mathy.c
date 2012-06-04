#include "mathy.h"

int overlap(SDL_Rect a, SDL_Rect b) {
  return (b.x >= a.x - b.w && b.x <= a.x + a.w && b.y >= a.y - b.h && b.y <= a.y + a.h);
}

int contains(SDL_Rect a, SDL_Rect b) {
  return (b.x >= a.x && b.x + b.w <= a.x + a.w && b.y >= a.y && b.y + b.h <= a.y + a.h);
}

float square(float a) {
  return a * a;
}
