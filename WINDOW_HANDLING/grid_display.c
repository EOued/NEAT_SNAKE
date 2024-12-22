#include "grid_display.h"
#include "window.h"
#include <SDL2/SDL_render.h>

SDL_Rect* initBoxes()
{
  SDL_Rect* boxes = malloc(HEIGHT * WIDTH * sizeof(SDL_Rect));
  for (int i = 0; i < HEIGHT * WIDTH; i++)
  {
    boxes[i].h = SQUARE_SIDE;
    boxes[i].w = SQUARE_SIDE;
    boxes[i].x = (SQUARE_SIDE + 1) * (i % WIDTH);
    boxes[i].y = (SQUARE_SIDE + 1) * (int)(i / WIDTH);
  }
  return boxes;
}
void renderBox(SDL_Renderer* renderer, SDL_Rect* boxes, int x, int y, unsigned int color)
{
  int r = (color >> 16) & 0xFF;
  int g = (color >> 8) & 0x00FF;
  int b = color & 0x0000FF;
  SDL_SetRenderDrawColor(renderer, r, g, b, 1);
  SDL_RenderFillRect(renderer, &boxes[y * WIDTH + x]);
  return;
}
