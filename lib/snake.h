#ifndef SNAKE_H
#define SNAKE_H

#include "object.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct SnakeLink SnakeLink;
typedef struct Snake Snake;
typedef enum Direction {
    up, right, down, left
} Direction;

struct SnakeLink
{
    Object base;
    SnakeLink* next;
    SnakeLink* prev;
};

struct Snake
{
    Direction direction;
    SnakeLink* head;
    SnakeLink* tail;
};

void stepSnake(Snake* snake, Object*** fieldPtr);
Snake newSnake(Object*** fieldPtr);
#endif