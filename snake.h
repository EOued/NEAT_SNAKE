#ifndef SNAKE_H
#define SNAKE_H

#include "UTILS/linkedList.h"
#include <stdint.h>

#define BACKGROUND 0xFFE169
#define SNAKE_HEAD 0x76520E
#define SNAKE_BODY 0xC9A227
#define APPLE 0xAF1740
enum directions
{
  Left  = 0,
  Right = 1,
  Up    = 2,
  Down  = 3
};

typedef struct
{
  enum directions direction;
  doublyLinkedList* snake;
  int delX;
  int delY;
  int appleX;
  int appleY;
  int alive;
  int renderApple;
} snake;

snake* initSnake(doublyLinkedList* grid);
void moveSnake(snake* snake, doublyLinkedList* grid);
void generateApple(snake* snake, doublyLinkedList* grid);
#endif
