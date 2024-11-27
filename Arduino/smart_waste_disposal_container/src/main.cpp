#include <Arduino.h>

#include "devices/Led.h"
#include "devices/ServoImpl.h"
#include "devices/Pir.h"
#include "devices/Button.h" 
#include "devices/Screen.h"
#include "serial/MsgService.h"

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
  MsgService.init();
}

void loop() {
  // if(pir->isDetected()){
  //   Serial.println("SIIII");
  // }
  // else{
  //   Serial.println("NOOOO");
  // }
  // ledGreen->switchOn();
  // delay(1000);
  // ledGreen->switchOff();
  // delay(1000);
  int temp = 0, perc = 0;
  if (MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();    
    if (msg->getContent() == "check"){
      temp = random(10, 60);
      perc = random(0,100);
      MsgService.sendMsg((String)perc+":"+temp); 
    } else if (msg->getContent() == "empty") {
      ledGreen->switchOn();
      delay(1000);
      ledGreen->switchOff();
      MsgService.sendMsg("emptied");
    } else if (msg->getContent() == "restore") {
      ledRed->switchOn();
      delay(1000);
      ledRed->switchOff();
      MsgService.sendMsg("restored");
    }
    /* NOT TO FORGET: msg deallocation */
    delete msg;
  }
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