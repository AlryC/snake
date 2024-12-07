#include <pthread.h>     // Multithreading
#include <stdbool.h>     // Booleans
#include <stdio.h>       // Standart Input/Output Library
#include <time.h>        // Clock
#include <termios.h>     // Managing termnial in Linux/MacOS
#include "./lib/snake.h" // Snake ~~~~~~~~~~>

Snake s;
int key;

void updateLink(Link* body, bool created);
void printField();
int  steptime();
void* listenKeyPress();
void* mainWhile();

int main(void)
{

    // Set the terminal into the "raw" mode
    /*---------------------------------------------------*/
    struct termios info;
    tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
    info.c_lflag &= ~(ECHO | ECHONL); // Disable echo
    info.c_lflag &= ~ICANON;      /* disable canonical mode */
    info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
    info.c_cc[VTIME] = 0;         /* no timeout */
    tcsetattr(0, TCSANOW, &info); /* set immediately */
    /*---------------------------------------------------*/

    // Clear the terminal
    printf("\033[2J");
    // Return cursor to the start
    printf("\e[0;0H");

    s = newSnake();
    //clock_t stepdelta = 0;


    printField();

    //printf("\e[;12f");
    //printf("%d\t%d\t%d\t\n", s.direction, s.head->x, s.tail->x);

    updateLink(s.head, true); 
    updateLink(s.head->next, true);
    updateLink(s.tail, true);

    // Hide the cursor
    printf("\e[?25l");
    
    //int* key;
    pthread_t id_key_listener, id_main_while;
    pthread_create(&id_key_listener, NULL, listenKeyPress, NULL);
    pthread_create(&id_main_while, NULL, mainWhile, NULL);

    pthread_join(id_main_while, NULL);
    pthread_join(id_key_listener, NULL);
  
    //printf("\e[21;70H");
    //char c;
    //scanf("%c", &c);
    while(key != 27){}

    // Show the cursor
    printf("\e[?25h");
 
    // Clear the terminal
    printf("\033[2J");

    info.c_lflag |= (ECHO | ECHONL); // Enable echo
    info.c_lflag |= ICANON;      /* enable canonical mode */
    tcsetattr(0, TCSANOW, &info); /* set immediately */

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

            stepSnake(&s, &updateLink);
            stepdelta = steptime();
        }
    }
}

void* listenKeyPress()
{
    while(key != 27)
    {
        key = getchar();
        printf("\e[0;0H%d", key);
    }
}

int steptime()
{
    return clock() / 200000;
}

void updateLink(Link* body, bool created)
{
    printf("\e[%d;%dH", body->y, body->x);
    if(created)
    {
        printf("@");
    }
    else 
    { 
        printf(" ");
    }
    fflush(stdout);
}

void printField()
{
    printf("╔════════════════════════════════════════════════════════════╗\n");
    for(int i = 0; i < 20; i++) 
    {
        printf("║                                                            ║\n");
    } 
    printf("╚════════════════════════════════════════════════════════════╝\n");
}
