#include "UTILS/errors.h"
#include "UTILS/linkedList.h"
#include "WINDOW_HANDLING/grid_display.h"
#include "WINDOW_HANDLING/window.h"
#include "snake.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main()
{
  srand(time(NULL));

  SDL_Window* g_main_window;
  SDL_Renderer* g_main_renderer;
  if (!init(&g_main_window, &g_main_renderer)) sendError("Failed to load window", 1);
  snake* snake;

  doublyLinkedList* grid;
  if (!(grid = initList())) sendError("Failed to initialise grid", 1);

  for (int i = 0; i < HEIGHT * WIDTH; i++) append(grid, i % WIDTH, i / WIDTH, 0);

  if (!(snake = initSnake(grid))) sendError("Failed to initialise snake", 1);

  SDL_Event event;

  doublyLinkedList* movesList;
  if (!(movesList = initList())) sendError("Failed to initialise moves list", 1);

  SDL_Rect* boxes;
  if (!(boxes = initBoxes())) sendError("Failed to initialise boxes", 1);

  // Representation of the grid

  SDL_Surface* im         = IMG_Load("sprite.png");
  SDL_Texture* im_texture = SDL_CreateTextureFromSurface(g_main_renderer, im);
  if (!im_texture) sendError("Failed to create texture", 1);

  struct timeval oldTime, actualTime, startTime;
  gettimeofday(&oldTime, NULL);
  gettimeofday(&startTime, NULL);

  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++) renderBox(g_main_renderer, boxes, x, y, BACKGROUND);

  int frames = 0;

  int running = 1;
  generateApple(snake, grid);
  SDL_Rect rect;
  rect.w = SPRITE_SIDE;
  rect.h = SPRITE_SIDE;
  SDL_Rect dest_rect;
  dest_rect.w = SQUARE_SIDE;
  dest_rect.h = SQUARE_SIDE;
  while (running)
  {
    gettimeofday(&actualTime, NULL);
    long elapsedMicroseconds =
        (actualTime.tv_sec - oldTime.tv_sec) * 1000000L + (actualTime.tv_usec - oldTime.tv_usec);

    if (elapsedMicroseconds > 17000)
    {
      frames++;
      gettimeofday(&oldTime, NULL);
      // SDL_RenderCopy(g_main_renderer, im_texture, &rect, &rect);
      SDL_RenderPresent(g_main_renderer);
    }

    if (frames > 8 && snake->alive)
    {
      // Game events
      if (movesList->size)
      {
        switch (movesList->start->x)
        {
        case Up: MoveUp(snake); break;
        case Down: MoveDown(snake); break;
        case Left: MoveLeft(snake); break;
        case Right: MoveRight(snake); break;
        default: break;
        }
        deleteStart(movesList);
      }
      frames = 0;
      moveSnake(snake, grid);
      // Render events
      if (snake->snake->end->before)
      {
        dest_rect.x = snake->snake->end->before->x * (SQUARE_SIDE + 1);
        dest_rect.y = snake->snake->end->before->y * (SQUARE_SIDE + 1);
        rect.x      = snakeBodySpriteX(snake) * SPRITE_SIDE;
        rect.y      = snakeBodySpriteY(snake) * SPRITE_SIDE;

        SDL_RenderCopy(g_main_renderer, im_texture, &rect, &dest_rect);
      }
      dest_rect.x = snake->snake->end->x * (SQUARE_SIDE + 1);
      dest_rect.y = snake->snake->end->y * (SQUARE_SIDE + 1);
      rect.x      = snakeHeadSpriteX(snake) * SPRITE_SIDE;
      rect.y      = snakeHeadSpriteY(snake) * SPRITE_SIDE;
      SDL_RenderCopy(g_main_renderer, im_texture, &rect, &dest_rect);
      renderBox(g_main_renderer, boxes, snake->delX, snake->delY, BACKGROUND);
      if (snake->renderApple)
      {
        rect.x      = APPLE_X * SPRITE_SIDE;
        rect.y      = APPLE_Y * SPRITE_SIDE;
        dest_rect.x = snake->appleX * (SQUARE_SIDE + 1);
        dest_rect.y = snake->appleY * (SQUARE_SIDE + 1);
        SDL_RenderCopy(g_main_renderer, im_texture, &rect, &dest_rect);
      }
    }
    if (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
      {
        running = 0;
        break;
      }
      case SDL_KEYDOWN:
      {
        running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
        if (event.key.keysym.scancode == SDL_SCANCODE_W) append(movesList, Up, 0, 0);
        if (event.key.keysym.scancode == SDL_SCANCODE_A) append(movesList, Left, 0, 0);
        if (event.key.keysym.scancode == SDL_SCANCODE_S) append(movesList, Down, 0, 0);
        if (event.key.keysym.scancode == SDL_SCANCODE_D) append(movesList, Right, 0, 0);
      }
      default: break;
      }
    }
  }

  free(boxes);
  freeList(snake->snake);
  free(snake);
  freeList(grid);
  freeList(movesList);
  SDL_FreeSurface(im);
  printf("All data freed\n");
  SDL_DestroyTexture(im_texture);

  SDL_DestroyWindow(g_main_window);
  SDL_DestroyRenderer(g_main_renderer);
  SDL_Quit();
  printf("Exiting...\n");

  return 0;
}
