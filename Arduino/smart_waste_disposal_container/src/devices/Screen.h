#ifndef __SCREEN__
#define __SCREEN__

#include "Arduino.h"

class Screen{
    public:
        Screen(int cols, int rows);
        void write(int cols, int rows, String text);
        void clear();
};

#endif