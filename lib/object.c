#include "object.h"
#include "../main.h"
#include <stdio.h>

//To do: add objectMutate? function to change both the object and the field at the same time

Object* createObject(int x, int y, enum ObjectType type, short** fieldPtr)
{
    // To do: add object creation to tie objects with the field
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
        }
    }
    else 
    { 
        printf(" ");
    }
    fflush(stdout);
}