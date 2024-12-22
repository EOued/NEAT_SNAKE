#include "snake.h"
#include <stdint.h>
#include <stdlib.h>

#include "UTILS/linkedList.h"
#include "WINDOW_HANDLING/grid_display.h"

snake* initSnake(doublyLinkedList* grid)
{
  snake* s;

  if (!(s = malloc(sizeof(snake)))) return NULL;
  s->direction = Right;
  if (!(s->snake = initList())) return NULL;
  prepend(s->snake, 4, 4);
  deleteElement(grid, 4 * WIDTH + 4, 0);
  s->alive       = 1;
  s->appleX      = -1;
  s->appleY      = -1;
  s->renderApple = 0;
  s->appleEaten  = 0;
  return s;
}

void moveSnake(snake* snake, doublyLinkedList* grid)
{
  if (!snake || !snake->snake || isEmpty(snake->snake)) return;
  int x = snake->snake->end->x;
  int y = snake->snake->end->y;

  switch (snake->direction)
  {
  case Right: x++; break;
  case Left: x--; break;
  case Up: y--; break;
  case Down: y++; break;
  default: break;
  }
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
  {
    // Killing snake
    snake->alive = 0;
    return;
  }
  if (!searchInList(grid, x, y))
  {
    // For rendering
    append(snake->snake, x, y);
    deleteStart(snake->snake);
    // Killing snake
    snake->alive = 0;
    return;
  }
  deleteElement(grid, x, y);
  append(grid, snake->snake->start->x, snake->snake->start->y);

  snake->delX = snake->snake->start->x;
  snake->delY = snake->snake->start->y;
  append(snake->snake, x, y);
  if (!snake->appleEaten) deleteStart(snake->snake);
  snake->appleEaten = 0;
  return;
}

void generateApple(snake* snake, doublyLinkedList* grid)
{
  int rdmIdx        = rand() % grid->size;
  struct Node* node = getNthElement(grid, rdmIdx);
  if (!node)
  {
    printf("The generation of the apple failed");
    return;
  }
  snake->appleX      = node->x;
  snake->appleY      = node->y;
  snake->renderApple = 1;
  return;
}
void eatApple(snake* snake, doublyLinkedList* grid)
{
  snake->appleEaten = 1;
  generateApple(snake, grid);
  return;
}
