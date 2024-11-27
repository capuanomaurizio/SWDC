#ifndef __SCREEN__
#define __SCREEN__

class Screen{
    public:
        Screen(int cols, int rows);
        void write(int cols, int rows, char text[]);
        void clear();
};

#endif