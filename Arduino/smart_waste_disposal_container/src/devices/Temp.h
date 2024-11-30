#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__

class Temp{
    public:
        Temp(int tempPin);
        float getTemperature();
    private:
        int pin;
};

#endif