#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);     
} 

bool Pir::isDetected(){
    int detected = digitalRead(pin);
    if (detected == HIGH){
        return true;
    }
    return false;
}