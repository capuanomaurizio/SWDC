#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int echo, int trig){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  this->echoPin = echo;
  this->trigPin = trig;
}

float Sonar::getDistance(){
  digitalWrite(this->trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(this->trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin,LOW);
    
    long duration = pulseIn(this->echoPin, HIGH);
    return duration * 0.034 / 2;

}
