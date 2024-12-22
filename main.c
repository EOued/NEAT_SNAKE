#include "UTILS/linkedList.h"
#include "WINDOW_HANDLING/grid_display.h"
#include "WINDOW_HANDLING/window.h"
#include "snake.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <termios.h>
#include <time.h>

int main()
{
  srand(time(NULL));

  SDL_Window* g_main_window;
  SDL_Renderer* g_main_renderer;
  if (!init(&g_main_window, &g_main_renderer))
  {
    fprintf(stderr, "Failed to initialise window or renderer\n");
    exit(1);
  }
  snake* snake;

  doublyLinkedList* grid;
  if (!(grid = initList()))
  {
    fprintf(stderr, "Failed to initialise grid");
    exit(1);
  }

  for (int i = 0; i < HEIGHT * WIDTH; i++) append(grid, i % WIDTH, i / WIDTH);

  if (!(snake = initSnake(grid)))
  {
    fprintf(stderr, "Failed to initialise snake");
    exit(1);
  }

  SDL_Event event;

  SDL_Rect* boxes;
  if (!(boxes = initBoxes()))
  {
    fprintf(stderr, "Failed to initialise boxes");
    exit(1);
  }

  // Representation of the grid

  struct timeval oldTime, actualTime, startTime;
  gettimeofday(&oldTime, NULL);
  gettimeofday(&startTime, NULL);

  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++) renderBox(g_main_renderer, boxes, x, y, BACKGROUND);

  int frames = 0;

  int running = 1;
  generateApple(snake, grid);
  while (running)
  {
    gettimeofday(&actualTime, NULL);
    long elapsedMicroseconds =
        (actualTime.tv_sec - oldTime.tv_sec) * 1000000L + (actualTime.tv_usec - oldTime.tv_usec);

    if (elapsedMicroseconds > 17000)
    {
      frames++;
      gettimeofday(&oldTime, NULL);
      SDL_RenderPresent(g_main_renderer);
    }

    if (frames > 8 && snake->alive)
    {
      // Game events
      frames = 0;
      moveSnake(snake, grid);
      if (snake->snake->end->x == snake->appleX && snake->snake->end->y == snake->appleY)
        eatApple(snake, grid);
      // Render events
      if (snake->snake->end->before)
        renderBox(g_main_renderer, boxes, snake->snake->end->before->x,
                  snake->snake->end->before->y, SNAKE_BODY);
      renderBox(g_main_renderer, boxes, snake->snake->end->x, snake->snake->end->y, SNAKE_HEAD);
      renderBox(g_main_renderer, boxes, snake->delX, snake->delY, BACKGROUND);
      if (snake->renderApple)
        renderBox(g_main_renderer, boxes, snake->appleX, snake->appleY, APPLE);
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
        if (event.key.keysym.scancode == SDL_SCANCODE_W && snake->direction != Down)
          snake->direction = Up;
        if (event.key.keysym.scancode == SDL_SCANCODE_A && snake->direction != Right)
          snake->direction = Left;
        if (event.key.keysym.scancode == SDL_SCANCODE_S && snake->direction != Up)
          snake->direction = Down;
        if (event.key.keysym.scancode == SDL_SCANCODE_D && snake->direction != Left)
          snake->direction = Right;
        {
          if (snake->snake->end->before)
            renderBox(g_main_renderer, boxes, snake->snake->end->before->x,
                      snake->snake->end->before->y, SNAKE_BODY);
        }
        break;
      }
      default: break;
      }
    }
  }

  free(boxes);
  freeList(snake->snake);
  free(snake);
  freeList(grid);
  printf("All data freed\n");

  SDL_DestroyWindow(g_main_window);
  SDL_DestroyRenderer(g_main_renderer);
  SDL_Quit();
  printf("Exiting...\n");

  return 0;
}
