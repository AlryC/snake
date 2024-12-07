#ifndef OBJECT_H
#define OBJECT_H

#include "../main.h"
#include "stdbool.h"

enum ObjectType
{
    Snakebody,
    Food,
    Poison,
    Wall,
};

typedef struct {
    int x;
    int y;
    enum ObjectType type;
} Object;

Object* createObject(int x, int y, enum ObjectType type, short** fieldPtr);
void printObject(Object* obj, bool hide);

#endif