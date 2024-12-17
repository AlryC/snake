#include "main.h"        // Custom symbolic names
#include <pthread.h>     // Multithreading
#include <stdbool.h>     // Booleans
#include <stdio.h>       // Standart Input/Output Library
#include <sys/types.h>
#include <time.h>        // Clock
#include <termios.h>     // Managing termnial in Linux/MacOS
#include "./lib/event.h"// Field building blocks
#include "./lib/object.h"// Field building blocks
#include "./lib/snake.h" // Snake ~~~~~~~~~~>

enum Color foregroundColor = White;
//short field[FIELD_HEIGHT][FIELD_WIDTH];
Object*** field;
Snake s;
unsigned int currentStep = 0;
unsigned int points = 0;
int key;

void  printField();
int   steptime();
void* listenKeyPress();
void* mainWhile();

int main(void)
{
    /*--------- Set terminal into the "raw" mode ---------*/
    struct termios info;
    // Get current terminal attirbutes; 0 is the file descriptor for stdin
    tcgetattr(0, &info);          
    info.c_lflag &= ~(ECHO | ECHONL); // Disable echo
    info.c_lflag &= ~ICANON;          // Disable canonical mode
    info.c_cc[VMIN] = 1;              // Wait until at least one keystroke available
    info.c_cc[VTIME] = 0;             // No timeout
    // Set updated terminal attributes;
    tcsetattr(0, TCSANOW, &info);
    /*---------------------------------------------------*/

    // Hide the cursor
    printf("\e[?25l");
    // Clear the terminal
    printf("\033[2J");
    // Return cursor to the start
    printf("\e[0;0H");

    // Print the field out;
    printField();
    
    // Allocate memory for the field 2D array
    field = (Object***)malloc(FIELD_HEIGHT * sizeof(Object**));
    for (int i = 0; i < FIELD_HEIGHT; i++) 
    {
        field[i] = (Object**)malloc(FIELD_WIDTH * sizeof(Object*));
    }

    // Debug
    createObject(50, 10, Food, field);
    createObject(15, 5, Food, field);
    createObject(30, 13, Poison, field);
    createObject(40, 18, Wall, field);
    
    printObject(field[5][15],  1);
    printObject(field[10][50], 1);
    printObject(field[13][30], 1);
    printObject(field[18][40], 1);

    // Initialise seed for rand() function
    srand(time(NULL));

    // Initialise a snake instance
    s = newSnake(field);
        
    // Start 2 threads: 1 for keypresses and 1 for the while game cycle
    pthread_t id_key_listener, id_main_while;
    pthread_create(&id_key_listener, NULL, listenKeyPress, NULL);
    pthread_create(&id_main_while, NULL, mainWhile, NULL);

    pthread_join(id_main_while, NULL);
    pthread_join(id_key_listener, NULL);

    // Pause main function until Esc key is pressed
    while(key != 27){}

    // Show the cursor
    printf("\e[?25h");
    // Clear the terminal
    printf("\033[2J");
    // Return cursor to the start
    printf("\e[0;0H");

    /*------ Return terminal into the original mode -----*/
    info.c_lflag |= (ECHO | ECHONL); // Enable echo
    info.c_lflag |= ICANON;          // Enable canonical mode
    // Set updated terminal attributes;
    tcsetattr(0, TCSANOW, &info);
    /*---------------------------------------------------*/

    return 0;
}

void* mainWhile()
{
    clock_t stepdelta = 0;
    while (key != 27) 
    {
        if(steptime() > stepdelta)
        {
            switch (key) 
            {
                case 97:
                    if(s.direction != right) {s.direction = left;}
                    break;
                case 119:
                    if(s.direction != down) {s.direction = up;}
                    break;
                case 100:
                    if(s.direction != left) {s.direction = right;}
                    break;
                case 115:
                    if(s.direction != up) {s.direction = down;}
                    break;
            }

            stepSnake(&s, field);
            stepGenEvent(field);

            stepdelta = steptime();
        }
    }
    return NULL;
}

void* listenKeyPress()
{
    while(key != 27)
    {
        key = getchar();
        // printf("\e[0;0H%d", key);
    }
    return NULL;
}

int steptime()
{
    return clock() / 100000;
}

void  setForegroundColor(enum Color color)
{
    if(foregroundColor != color)
    {
        foregroundColor = color;
        switch (color) 
        {
            case White:   printf("%s", ESC_COLOR_WHITE);   break;
            case Gray:    printf("%s", ESC_COLOR_GRAY);    break;
            case Green:   printf("%s", ESC_COLOR_GREEN);   break;
            case Red:     printf("%s", ESC_COLOR_RED);     break;
            case Magenta: printf("%s", ESC_COLOR_MAGENTA); break; 
        }
    }
}

void printField()
{
    setForegroundColor(Gray);
    printf("╔");
    for(int j = 0; j < FIELD_WIDTH; j++) { printf("═");}
    printf("╗");
    setForegroundColor(White);
    printf(" Score: 0\n");

    for(int i = 0; i < FIELD_HEIGHT; i++) 
    {
        setForegroundColor(Gray);
        printf("║");
        for(int j = 0; j < FIELD_WIDTH; j++) { printf(" ");}
        printf("║");
        switch(i)
        {
            case 1:
                setForegroundColor(White);
                printf(" Controls:");
                break;
            case 2:
                setForegroundColor(White);
                printf(" W - up");
                break;
            case 3:
                setForegroundColor(White);
                printf(" A - left");
                break;
            case 4:
                setForegroundColor(White);
                printf(" S - down");
                break;
            case 5:
                setForegroundColor(White);
                printf(" D - right");
                break;
        }
        printf("\n");
    }

    printf("╚");
    for(int j = 0; j < FIELD_WIDTH; j++) { printf("═");}
    printf("╝\n");
    setForegroundColor(White);
}

void updateScore(char plusPoints)
{
    points += plusPoints;
    setForegroundColor(White);
    printf("\e[0;71H%d ", points);
}