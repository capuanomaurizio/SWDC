#ifndef __SERVO_IMPL__
#define __SERVO_IMPL__

class ServoImpl {
    public:
        ServoImpl(int pin);
        void setPosition(int pos);
        int returnPos();
    private:
        int actualPos;
        int pin;
};
#endif
