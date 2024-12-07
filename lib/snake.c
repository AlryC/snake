#include "snake.h"
#include "object.h"
#include <stdbool.h>
#include <stdio.h>

Snake newSnake()
{
    Snake python;

    static SnakeLink head = {.base.x = 12, .base.y = 10, .base.type = Snakebody};
    static SnakeLink body = {.base.x = 11, .base.y = 10, .base.type = Snakebody};
    static SnakeLink tail = {.base.x = 10, .base.y = 10, .base.type = Snakebody};
    
    head.next = &body;
    body.prev = &head;
    body.next = &tail;
    tail.prev = &body;

    python.direction = right;
    python.head = &head;
    python.tail = &tail;

    return python;
}

void stepSnake(Snake* snake)
{
    // Undraw tail element
    printObject(&snake->tail->base, true);

    // Copy head coordinates into tail
    snake->tail->base.x = snake->head->base.x;
    snake->tail->base.y = snake->head->base.y;
    
    snake->tail->next = snake->head;

    snake->head->prev = snake->tail;
    snake->tail->prev->next = NULL;
    snake->head = snake->tail;
    snake->tail = snake->tail->prev;
    snake->head->prev = NULL;

    switch (snake->direction) 
    {
        case up: snake->head->base.y--; break;
        case left: snake->head->base.x--; break;
        case down: snake->head->base.y++; break;
        case right: snake->head->base.x++; break;
    }

    // Draw new head element
    printObject(&snake->head->base, false);
}