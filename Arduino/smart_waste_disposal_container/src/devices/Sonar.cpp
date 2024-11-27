#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int echoPin, int trigPin){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}

float Sonar::getDistance(){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    /* Receiving the echo */
    long tUS = pulseInLong(echoPin, HIGH);
    return tUS;
}
