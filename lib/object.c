#include "object.h"
#include "../main.h"
#include <stdio.h>

Object createObject(int x, int y, enum ObjectType type, Object*** fieldPtr)
{
    Object obj;
    obj.x = x;
    obj.y = y;
    obj.type = type;

    // Assign object to the field via reference
    fieldPtr[y][x] = &obj;

    return obj;
}

void moveObject(Object* obj, int x, int y, Object*** fieldPtr)
{
    // Remove object reference from the field
    fieldPtr[obj->y][obj->y] = NULL;

    obj->x = x;
    obj->y = y;

    // Assign object to the field via reference
    fieldPtr[y][x] = obj;   
}

void printObject(Object* obj, bool hide)
{
    printf("\e[%d;%dH", obj->y+1, obj->x+1);
    if(!hide)
    {
        switch (obj->type) {
        case Snakebody:
            setForegroundColor(Green);
            printf("@");
            break;
        case Food:
            setForegroundColor(Red);
            printf("&");
            break;
        case Poison:
            setForegroundColor(Magenta);
            printf("$");
            break;
        case Wall:
            setForegroundColor(Gray);
            printf("X");
            break;
        default:
            break;
        }
    }
    else 
    { 
        printf(" ");
    }
    fflush(stdout);
}