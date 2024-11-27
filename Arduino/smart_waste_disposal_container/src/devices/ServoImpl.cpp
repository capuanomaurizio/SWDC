#include "ServoImpl.h"
#include <Servo.h>
#include "Arduino.h"

Servo servo;

ServoImpl::ServoImpl(int pin){
    this->pin = pin;
    servo.attach(pin);
    servo.write(0);
    this->actualPos = 0;
}

void ServoImpl::setPosition(int pos){
    servo.write(pos);
}

int ServoImpl::returnPos(){
    return this->actualPos;
}
