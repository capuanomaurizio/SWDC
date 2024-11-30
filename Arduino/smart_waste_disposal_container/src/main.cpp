#include <Arduino.h>

#include "devices/Led.h"
#include "devices/ServoImpl.h"
#include "devices/Pir.h"
#include "devices/Button.h" 
#include "devices/Screen.h"
#include "devices/Sonar.h"
#include "devices/Temp.h"
#include "serial/CommManager.h"

#define LED_GREEN 7
#define LED_RED 8
#define BUTTON_OPEN 3
#define BUTTON_CLOSE 4
#define PIR_PIN 2
#define SERVO 9
#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13
#define TEMP_PIN A0

#define CLOSE_SERVO 90
#define OPEN_SERVO 180
#define EMPTY_SERVO 0

Led* ledGreen;
Led* ledRed;
ServoImpl* servo;
// Pir* pir;
Button* pir;
Button* buttonOpen;
Button* buttonClose;
Screen* screen;
CommManager* commManager;
Sonar* sonar;
Temp* temp;
String requiredAction; //"check" "empty" "restore" are the possible messages

void acceptingWaste();
void initialScreen();
void checkSerialComm();
void screenSpilling();
void spillingWaste();

void setup() {
    ledGreen = new Led(LED_GREEN);
    ledRed = new Led(LED_RED);
    servo = new ServoImpl(SERVO);
    //pir = new Pir(PIR_PIN);
    pir = new Button(PIR_PIN);
    buttonOpen = new Button(BUTTON_OPEN);
    buttonOpen = new Button(BUTTON_CLOSE);
    screen = new Screen(16, 4);
    sonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN);
    temp = new Temp(TEMP_PIN);
    //commManager = new CommManager();
    requiredAction = "";
}

void loop() {
    
}


void checkSerialComm(){
    requiredAction = commManager->checkReceived();
    if(requiredAction != ""){
        if(requiredAction == "check") {
            commManager->sendPercentageTemperature(random(0,100), random(10, 60));
        } else if (requiredAction == "empty") {
            ledGreen->switchOn();
            delay(200);
            ledGreen->switchOff();
            commManager->endEmptyContainer();
        } else if (requiredAction == "restore") {
            ledRed->switchOn();
            delay(200);
            ledRed->switchOff();
            commManager->endRestoreContainer();
        }
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

void spillingWaste(){
    screenSpilling();
    servo->setPosition(OPEN_SERVO);
}

void screenSpilling(){
    screen->clear();
    screen->write(0,0, "PRESS CLOSE");
    screen->write(0,1, "WHEN DONE");
}