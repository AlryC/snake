#include "snake.h"
#include "object.h"
#include <stdbool.h>
#include <stdio.h>

void headColision(int x, int y, Object*** fieldPtr);

Snake newSnake(Object*** fieldPtr)
{
    Snake python;

    static SnakeLink head = {.xKey = 12, .yKey = 10};
    static SnakeLink body = {.xKey = 11, .yKey = 10};
    static SnakeLink tail = {.xKey = 10, .yKey = 10};
    
    createObject(head.xKey, head.yKey, Snakebody, fieldPtr);
    createObject(body.xKey, body.yKey, Snakebody, fieldPtr);
    createObject(tail.xKey, tail.yKey, Snakebody, fieldPtr);

    head.next = &body;
    body.prev = &head;
    body.next = &tail;
    tail.prev = &body;

    python.direction = right;
    python.head = &head;
    python.tail = &tail;

    // Draw the snake
    printObject(fieldPtr[head.yKey][head.xKey], false); 
    printObject(fieldPtr[body.yKey][body.xKey], false); 
    printObject(fieldPtr[tail.yKey][tail.xKey], false); 

    return python;
}

void stepSnake(Snake* snake, Object*** fieldPtr)
{
    // Undraw tail element
    printObject(fieldPtr[snake->tail->yKey][snake->tail->xKey], true);

    // Copy head coordinates into tail
    //snake->tail->base->x = snake->head->base->x;
    //snake->tail->base->y = snake->head->base->y;
    int newX = snake->head->xKey;
    int newY = snake->head->yKey;

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

    headColision(newX, newY, fieldPtr);
    moveObject(fieldPtr[snake->tail->yKey][snake->tail->xKey], newX, newY, fieldPtr);
    snake->tail->xKey = newX;
    snake->tail->yKey = newY;

    snake->tail->next = snake->head;

    snake->head->prev = snake->tail;
    snake->tail->prev->next = NULL;
    snake->head = snake->tail;
    snake->tail = snake->tail->prev;
    snake->head->prev = NULL;

       // Draw new head element
    printObject(fieldPtr[snake->head->yKey][snake->head->xKey], false);
}

void headColision(int x, int y, Object*** fieldPtr)
{
    if(fieldPtr[y][x] != NULL)
    {
        switch (fieldPtr[y][x]->type)
        {
            case Food:
                printf("\e[0;0H Food detected");
                break;
            case Poison:
                printf("\e[0;0H Poison detected");
                break;
            case Wall:
                printf("\e[0;0H Wall detected");
                break;
            case Snakebody:
                printf("\e[0;0H Snakebody detected");
                break;
            
        }
    }
}