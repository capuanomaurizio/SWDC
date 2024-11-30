#include "Temp.h"
#include "Arduino.h"


Temp::Temp(int pin){
    dht(DHTPIN, DHTTYPE);
    this->pin = pin
}

float Temp::getTemperature(){
    return dht.readTemperature();
}