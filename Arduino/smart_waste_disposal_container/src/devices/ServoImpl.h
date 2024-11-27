#ifndef __SERVO_IMPL__
#define __SERVO_IMPL__

#include <Servo.h>

class ServoImpl {
    public:
        ServoImpl(int pin);
        void setPosition(int pos);
        int returnPos();
    private:
        int actualPos;
        int pin;
        Servo servo;
};
#endif
