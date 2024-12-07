#include "snake.h"
#include <stdio.h>

Snake newSnake()
{
    Snake python;

    static Link head = {.x = 12, .y = 10};
    static Link body = {.x = 11, .y = 10};
    static Link tail = {.x = 10, .y = 10};
    
    head.next = &body;
    body.prev = &head;
    body.next = &tail;
    tail.prev = &body;

    python.direction = right;
    python.head = &head;
    python.tail = &tail;

    return python;
}

void stepSnake(Snake* snake, void (*updateLinkFunc)(Link*, bool))
{
    // printf("frog");
    // Undraw tail element
    (*updateLinkFunc)(snake->tail, false);

    // Copy head coordinates into tail
    snake->tail->x = snake->head->x;
    snake->tail->y = snake->head->y;
    
    snake->tail->next = snake->head;

    snake->head->prev = snake->tail;
    snake->tail->prev->next = NULL;
    snake->head = snake->tail;
    snake->tail = snake->tail->prev;
    snake->head->prev = NULL;

    switch (snake->direction) 
    {
        case up: snake->head->y--; break;
        case left: snake->head->x--; break;
        case down: snake->head->y++; break;
        case right: snake->head->x++; break;
    }

    // Draw new head element
    (*updateLinkFunc)(snake->head, true);
}