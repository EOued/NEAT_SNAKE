#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include "window.h"

void SDLError(char* message) { printf("%s : %s\n", message, SDL_GetError()); }

int init(SDL_Window** g_main_window, SDL_Renderer** g_main_renderer)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    SDLError("Unable to init SDL");
    return EXIT_FAILURE;
  }

  *(g_main_window) =
      SDL_CreateWindow("A SDL2 Basic Window (512x284)", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

  if (*(g_main_window) == NULL)
  {
    SDLError("Unable to create main window");
    SDL_Quit();
    return EXIT_FAILURE;
  }

  *(g_main_renderer) = SDL_CreateRenderer(*g_main_window, -1, SDL_RENDERER_SOFTWARE);

  return 1;
}

void ClearScreen(SDL_Renderer** renderer)
{
  SDL_SetRenderDrawColor(*(renderer), 0, 0, 0, 1);
  SDL_RenderClear(*(renderer));
}
