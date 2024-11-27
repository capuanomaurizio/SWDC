#include <Arduino.h>

#include "devices/Led.h"
#include "devices/ServoImpl.h"
#include "devices/Pir.h"
#include "devices/Button.h" 
#include "devices/Screen.h"

#define LED_GREEN 7
#define LED_RED 8
#define BUTTON_OPEN 3
#define BUTTON_CLOSE 4
#define PIR_PIN 2
#define SERVO 9
#define PIR 2

#define CLOSE_SERVO 90
#define OPEN_SERVO 180
#define EMPTY_SERVO 0

Led* ledGreen;
Led* ledRed;
ServoImpl* servo;
Pir* pir;
Button* button;
Screen* screen;

void acceptingWaste();
void initialScreen();

void setup() {
  Serial.begin(9600);
  ledGreen = new Led(LED_GREEN);
  ledRed = new Led(LED_RED);
  servo = new ServoImpl(SERVO);
  pir = new Pir(PIR);
  button = new Button(BUTTON_OPEN);
  screen = new Screen(16, 4);
  //acceptingWaste();
}

void loop() {
  // if(pir->isDetected()){
  //   Serial.println("SIIII");
  // }
  // else{
  //   Serial.println("NOOOO");
  // }
  ledGreen->switchOn();
  delay(3000);
  ledGreen->switchOff();
}


void acceptingWaste(){
  initialScreen();
  ledGreen->switchOn();
  servo->setPosition(CLOSE_SERVO);
}

void initialScreen(){
  screen->clear();
  screen->write(0,0, "PRESS OPEN TO");
  screen->write(0,1, "ENTER WASTE");
}
