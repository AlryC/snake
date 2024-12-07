#ifndef MAIN_H
#define MAIN_H

#define FIELD_WIDTH  60
#define FIELD_HEIGHT 20

#define ESC_COLOR_WHITE   "\e[0m"
#define ESC_COLOR_GRAY    "\e[0;30m"
#define ESC_COLOR_GREEN   "\e[0;32m"
#define ESC_COLOR_RED     "\e[0;31m"
#define ESC_COLOR_MAGENTA "\e[0;35m"


enum Color {
    White,
    Gray,
    Green,
    Red,
    Magenta,
};

void  setForegroundColor(enum Color color);

#endif