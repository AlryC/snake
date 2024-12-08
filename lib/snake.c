#include "snake.h"
#include "object.h"
#include <stdbool.h>
#include <stdio.h>

Snake newSnake(Object*** fieldPtr)
{
    Snake python;

    static SnakeLink head; //= {.base.x = 12, .base.y = 10, .base.type = Snakebody};
    static SnakeLink body; //= {.base.x = 11, .base.y = 10, .base.type = Snakebody};
    static SnakeLink tail; //= {.base.x = 10, .base.y = 10, .base.type = Snakebody};
    
    head.base = createObject(12, 10, Snakebody, fieldPtr);
    body.base = createObject(11, 10, Snakebody, fieldPtr);
    tail.base = createObject(10, 10, Snakebody, fieldPtr);

    head.next = &body;
    body.prev = &head;
    body.next = &tail;
    tail.prev = &body;

    python.direction = right;
    python.head = &head;
    python.tail = &tail;

    // Draw the snake
    printObject(&head.base, false); 
    printObject(&body.base, false);
    printObject(&tail.base, false);

    return python;
}

void stepSnake(Snake* snake, Object*** fieldPtr)
{
    // Undraw tail element
    printObject(&snake->tail->base, true);

    // Copy head coordinates into tail
    //snake->tail->base->x = snake->head->base->x;
    //snake->tail->base->y = snake->head->base->y;
    int newX = snake->head->base.x;
    int newY = snake->head->base.y;

    switch (snake->direction) 
    {
        // case up: snake->head->base->y--; break;
        case up: newY--; break;
        // case left: snake->head->base->x--; break;
        case left: newX--; break;
        // case down: snake->head->base->y++; break;
        case down: newY++; break;
        // case right: snake->head->base->x++; break;
        case right: newX++; break;
    }

    moveObject(&snake->tail->base, newX, newY, fieldPtr);

    snake->tail->next = snake->head;

    snake->head->prev = snake->tail;
    snake->tail->prev->next = NULL;
    snake->head = snake->tail;
    snake->tail = snake->tail->prev;
    snake->head->prev = NULL;

       // Draw new head element
    printObject(&snake->head->base, false);
}