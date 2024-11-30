#include "Temp.h"
#include "Arduino.h"

#define VCC ((float)5)
#define SCART 32
#define DIVIDEND 0.55

Temp::Temp(int tempPin){
    this->pin = tempPin;
    pinMode(this->pin, INPUT);
}

float Temp::getTemperature(){
    int value = analogRead(this->pin);
    float valueInVolt = value*VCC/1023;  
    float valueInCelsius = (valueInVolt/0.01 - SCART) * DIVIDEND;
    return valueInCelsius;
}