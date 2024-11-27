#ifndef __BUTTON__
#define __BUTTON__

class Button{
    public: 
        Button(int pin);
        bool isClicked();

    private:
        int pin;
        bool clicked;
};

#endif
