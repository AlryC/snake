#ifndef SNAKE_H
#define SNAKE_H

#include "object.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct SnakeLink SnakeLink;
typedef struct Snake Snake;
typedef enum Direction {
    up = 1,
    right = 2,
    down = 3,
    left = 4,
} Direction;

struct SnakeLink
{
    int xKey, yKey;
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