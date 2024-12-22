#ifndef GRID_DISPLAY_H
#define GRID_DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#define HEIGHT 16
#define WIDTH 16

SDL_Rect* initBoxes();
void renderBox(SDL_Renderer* renderer, SDL_Rect* boxes, int x, int y, unsigned int color);

#endif
