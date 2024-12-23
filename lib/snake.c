#include "snake.h"
#include "object.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

enum ObjectType headColision(int x, int y, Object*** fieldPtr);

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
    printObject(fieldPtr[head.yKey][head.xKey], 1); 
    printObject(fieldPtr[body.yKey][body.xKey], 1); 
    printObject(fieldPtr[tail.yKey][tail.xKey], 1); 

    return python;
}

void stepSnake(Snake* snake, Object*** fieldPtr)
{
    // Undraw tail element
    printObject(fieldPtr[snake->tail->yKey][snake->tail->xKey], 0);

    // Copy head coordinates into tail
    //snake->tail->base->x = snake->head->base->x;
    //snake->tail->base->y = snake->head->base->y;
    int newX = snake->head->xKey;
    int newY = snake->head->yKey;

    switch (snake->direction) 
    {
        // case up: snake->head->base->y--; break;
        case up:
            newY--;
            if(newY < 0) newY = FIELD_HEIGHT - 1;
            break;
        case left: 
            newX--;
            if(newX < 0) newX = FIELD_WIDTH - 1;
            break;
        case down:
            newY++;
            if(newY >= FIELD_HEIGHT) newY = 0;
            break;
        case right: 
            newX++; 
            if(newX >= FIELD_WIDTH) newX = 0;
            break;
    }

    enum ObjectType colision = headColision(newX, newY, fieldPtr);

    // If colision is Void or Food or Poison
    if(colision < 3)
    {
        moveObject(fieldPtr[snake->tail->yKey][snake->tail->xKey], newX, newY, fieldPtr);

        int prevX = snake->tail->xKey;
        int prevY = snake->tail->yKey;

        snake->tail->xKey = newX;
        snake->tail->yKey = newY;

        snake->tail->next = snake->head;

        snake->head->prev = snake->tail;
        snake->tail->prev->next = NULL;
        snake->head = snake->tail;
        
        switch (colision) {
            case Void:
                snake->tail = snake->tail->prev;
                break;
            case Food:
                createObject(prevX, prevY, Snakebody, fieldPtr);
                SnakeLink* newTail = malloc(sizeof(SnakeLink));
                newTail->xKey = prevX;
                newTail->yKey = prevY;
                newTail->prev = snake->tail->prev;
                snake->tail = newTail;
                updateScore(1);
                break;
            case Poison:

                break;
            default: exit(33); // If something is wrong then exit with a custom status
        }
        snake->head->prev = NULL;

        // Draw new head element
        printObject(fieldPtr[snake->head->yKey][snake->head->xKey], snake->direction);
        return;
    }

    // End game
    exit(0);
}

enum ObjectType headColision(int x, int y, Object*** fieldPtr)
{
    if(fieldPtr[y][x] == NULL)
    {
        return Void;
    }

    enum ObjectType type = fieldPtr[y][x]->type;
    switch (type)
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
        default: break;
        }

    free(fieldPtr[y][x]);
    return type;
}
