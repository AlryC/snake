#include "event.h"
#include "object.h"
#include "stdlib.h"

typedef enum {
    EvTypeFoodSpawn,
    EvTypePosionSpawn,
    EvTypeWallSpawn,
    EvTypeLength,
} EventTypes;

struct EventData {
    short stepsUntilFoodSpawn;
    short stepsUntilPoisonSpawn;
    short stepsUntilWallSpawn;
} static eventData;

void stepGenEvent(Object*** fieldPtr)
{
    if(eventData.stepsUntilFoodSpawn > 0)   {eventData.stepsUntilFoodSpawn--;}
    if(eventData.stepsUntilPoisonSpawn > 0) {eventData.stepsUntilPoisonSpawn--;}
    if(eventData.stepsUntilWallSpawn > 0)   {eventData.stepsUntilWallSpawn--;}

    EventTypes event = rand() % EvTypeLength;
    unsigned short x, y;

    switch (event) 
    {
        case EvTypeFoodSpawn:
            if(eventData.stepsUntilFoodSpawn > 0) return;
            x = rand() % FIELD_WIDTH;
            y = rand() % FIELD_HEIGHT;
            createObject(x, y, Food, fieldPtr);
            printObject(fieldPtr[y][x], false);
            eventData.stepsUntilFoodSpawn = rand() % 13 + 7;
            break;
        default:
            break;
    }
}