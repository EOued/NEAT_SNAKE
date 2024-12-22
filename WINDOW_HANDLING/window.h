#ifndef WINDOW_H
#define WINDOW_H

#include "grid_display.h"
#include <SDL2/SDL.h>

#define SQUARE_SIDE 30

#define WINDOW_WIDTH (SQUARE_SIDE + 1) * WIDTH
#define WINDOW_HEIGHT (SQUARE_SIDE + 1) * HEIGHT

int init(SDL_Window** g_main_window, SDL_Renderer** g_main_renderer);
void ClearScreen(SDL_Renderer** renderer);

#endif
