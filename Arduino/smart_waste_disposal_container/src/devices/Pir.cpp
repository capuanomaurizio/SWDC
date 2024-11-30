#include "Pir.h"
#include "Arduino.h"

Pir::Pir(int pirPin){
    this->pin = pirPin;
    pinMode(this->pin, INPUT);     
} 

bool Pir::isDetected(){
    int detected = digitalRead(this->pin);
    if (detected == HIGH){
        return true;
    }
    return false;
}