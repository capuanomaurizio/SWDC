#ifndef __TEMP__
#define __TEMP__
#define DHTTYPE DHT11
#include "DHT.h"

class Temp{
    public:  
        Temp(int pin);
        float getTemperature();
    private:
        int pin;
        DTH dth
};

#endif
