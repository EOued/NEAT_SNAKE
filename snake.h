#ifndef SNAKE_H
#define SNAKE_H

#include "UTILS/linkedList.h"
#include <stdint.h>

#define BACKGROUND 0xFFE169
#define SNAKE_HEAD 0x76520E
#define SNAKE_BODY 0xC9A227
#define APPLE 0xAF1740

#define SPRITE_SIDE 30
#define SNAKE_HEAD_UP_X 0
#define SNAKE_HEAD_UP_Y 0
#define SNAKE_HEAD_DOWN_X 1
#define SNAKE_HEAD_DOWN_Y 2
#define SNAKE_HEAD_LEFT_X 0
#define SNAKE_HEAD_LEFT_Y 3
#define SNAKE_HEAD_RIGHT_X 2
#define SNAKE_HEAD_RIGHT_Y 4

#define SNAKE_BODY_STRAIGHT_UP_X 0
#define SNAKE_BODY_STRAIGHT_UP_Y 1
#define SNAKE_BODY_STRAIGHT_DOWN_X 1
#define SNAKE_BODY_STRAIGHT_DOWN_Y 1
#define SNAKE_BODY_STRAIGHT_LEFT_X 1
#define SNAKE_BODY_STRAIGHT_LEFT_Y 3
#define SNAKE_BODY_STRAIGHT_RIGHT_X 1
#define SNAKE_BODY_STRAIGHT_RIGHT_Y 4

#define SNAKE_TAIL_STRAIGHT_UP_X 0
#define SNAKE_TAIL_STRAIGHT_UP_Y 2
#define SNAKE_TAIL_STRAIGHT_DOWN_X 1
#define SNAKE_TAIL_STRAIGHT_DOWN_Y 0
#define SNAKE_TAIL_STRAIGHT_LEFT_X 2
#define SNAKE_TAIL_STRAIGHT_LEFT_Y 3
#define SNAKE_TAIL_STRAIGHT_RIGHT_X 0
#define SNAKE_TAIL_STRAIGHT_RIGHT_Y 4

#define SNAKE_BODY_CURVED_DOWN_RIGHT_X 2
#define SNAKE_BODY_CURVED_DOWN_RIGHT_Y 0
#define SNAKE_BODY_CURVED_UP_RIGHT_X 2
#define SNAKE_BODY_CURVED_UP_RIGHT_Y 1
#define SNAKE_BODY_CURVED_UP_LEFT_X 2
#define SNAKE_BODY_CURVED_UP_LEFT_Y 2
#define SNAKE_BODY_CURVED_DOWN_LEFT_X 0
#define SNAKE_BODY_CURVED_DOWN_LEFT_Y 5

#define SNAKE_TAIL_CURVED_RIGHT_X 3
#define SNAKE_TAIL_CURVED_RIGHT_Y 0
#define SNAKE_TAIL_CURVED_UP_X 3
#define SNAKE_TAIL_CURVED_UP_Y 1
#define SNAKE_TAIL_CURVED_LEFT_X 3
#define SNAKE_TAIL_CURVED_LEFT_Y 2
#define SNAKE_TAIL_CURVED_DOWN_X 2
#define SNAKE_TAIL_CURVED_DOWN_Y 5

#define APPLE_X 1
#define APPLE_Y 5

/**
@enum directions
@brief An enumerator for the 4 directions that the snake can take
 */
enum directions
{
  Left  = 0,
  Right = 1,
  Up    = 2,
  Down  = 3
};

/**
@struct snake
@brief Type that represent an instance of a snake
@param direction The direction the snake is headed
@param snake The body of the snake
@param delX The old X position of the last element of the tail
@param delY The old Y position of the last element of the tail
@param appleX The X position of the apple
@param appleY The Y position of the apple
@param alive True is the snake is alive
@param renderApple True if the apple need to be rendered by the renderer]
@param score The number of apple eaten
*/
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
  int score;
} snake;

/**
@brief Initialise the snake at the position (4,4). The corresponding position is removed from the
grid. The score is set to 0, the snake is set to alive, The apple is generated by default and both
positions are set to -1. The delX and delY are left uninitialised. The default direction is set to
Right
@param grid The current grid
@retval snake* An pointer to the snake type with all values initalised.

 */
snake* initSnake(doublyLinkedList* grid);
/**
@brief Move the snake in the direction set in the snake
@param snake The snake
@param grid The grid
 */
void moveSnake(snake* snake, doublyLinkedList* grid);
/**
@brief generate an apple at a random position in the grid. The values are saved in the snake
@param snake The snake
@param grid The grid
 */
void generateApple(snake* snake, doublyLinkedList* grid);
/**
 @brief Set the snake direction to the left if the current direction is not the right direction
 @param snake The snake
*/
void MoveLeft(snake* snake);
/**
 @brief Set the snake direction to the right if the current direction is not the left direction
 @param snake The snake
*/
void MoveRight(snake* snake);
/**
  @brief Set the snake direction to the up if the current direction is not the down direction
  @param snake The snake
*/
void MoveUp(snake* snake);
/**
   @brief Set the snake direction to the down if the current direction is not the up direction
   @param snake The snake
*/
void MoveDown(snake* snake);
int snakeHeadSpriteX(snake* snake);
int snakeHeadSpriteY(snake* snake);
int snakeBodySpriteX(snake* snake);
int snakeBodySpriteY(snake* snake);
#endif
