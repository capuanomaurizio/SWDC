#ifndef __SONAR__
#define __SONAR__

class Sonar{
    public:  
        Sonar(int echoPin, int trigPin);
        float getDistance();

    private:
        int echoPin;
        int trigPin;    
};

#endif