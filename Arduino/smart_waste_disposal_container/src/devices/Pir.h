#ifndef __PRESENCE__
#define __PRESENCE__

class Pir{
    public:
        Pir(int pin);
        bool isDetected();
    private:
        int pin;
        bool detected;
};

#endif
