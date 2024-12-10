#ifndef OBJECT_H
#define OBJECT_H

#include "../main.h"
#include "stdbool.h"

enum ObjectType
{
    Void,
    Food,
    Poison,
    Wall,
    Snakebody,
};

typedef struct {
    int x;
    int y;
    enum ObjectType type;
} Object;

void createObject(int x, int y, enum ObjectType type, Object*** fieldPtr);
void printObject(Object* obj, bool hide);
void moveObject(Object* obj, int x, int y, Object*** fieldPtr);

#endif