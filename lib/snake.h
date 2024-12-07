#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Link Link;
typedef struct Snake Snake;
typedef enum Direction {
    up, right, down, left
} Direction;

struct Link
{
    int x;
    int y;
    Link *next;
    Link *prev;
};

struct Snake
{
    Direction direction;
    Link *head;
    Link *tail;
};

void stepSnake(Snake* snake, void (*updateDestroyedLinkFunc)(Link*, bool));
void destroyLink(Link* link);
Snake newSnake();
#endif