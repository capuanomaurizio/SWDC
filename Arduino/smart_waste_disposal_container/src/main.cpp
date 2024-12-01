#include <Arduino.h>

#include "config.h"

#include "devices/Led.h"
#include "devices/ServoImpl.h"
#include "devices/Pir.h"
#include "devices/Button.h" 
#include "devices/Screen.h"
#include "devices/Sonar.h"
#include "devices/Temp.h"
#include "serial/CommManager.h"

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
const int MAXTEMP = 50;
const int MAXTEMPTIME = 5000;
const int T1 = 7000;
const int T2 = 4000;
const int T3 = 3000;
const long TIME_TO_SLEEP = 10000;
const int MAX_FULLNESS = 10; // sarebbero 10 cm
enum State { IDLE, WAITING_WASTE, SPILLING, FULL, TEMP_ALARM, EMPTYING, SLEEPING };
State currentState = IDLE;

volatile bool buttonOpenPressed = false;
bool userDetected = false;
long lastUserDetection = 0;
long startSpillingTime = 0;
long tempAlarmStart = 0;

void initialScreen();
void doneScreen();
void fullScreen();
void problemScreen();
void emptyScreen();
int readSonar();
float readTemperature();
void goToSleep();
void wakeUp();
void openServo();
void closeServo();
void emptyContainer();
void handleTempAlarm();
void screenSpilling();

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

void loop() {
    // bisogna trovare un modo intelligente di gestire lo user detected
    if(currentState != TEMP_ALARM && readTemperature() > MAXTEMP){
        currentState = TEMP_ALARM;
        tempAlarmStart = millis();
    }

    else{

        if(currentState != SLEEPING && !userDetected()){
            lastUserDetection = millis();
        }

        if(currentState != SLEEPING && millis() - lastUserDetection > TIME_TO_SLEEP){
            goToSleep();
        }
    }

    switch (currentState){

        case SLEEPING:
            if(userDetected){
                wakeUp();
            }

        case IDLE:
                initialScreen();
                currentState = WAITING_WASTE;

        
        case WAITING_WASTE:
            if(buttonOpen->isClicked()){
                openServo();
                screenSpilling();
                startSpillingTime = millis();
                currentState = SPILLING;
            }
        
        case SPILLING:
            if(buttonClose->isClicked() || checkSpillingTime){
                closeServo();
                doneScreen();
                if (readSonar()>MAX_FULLNESS){             
                    fullScreen();
                    currentState = FULL;
                }
                else{
                    currentState = IDLE;
                }
            }

        // metto il break perchè andrebbe gestito dalla gui
        case FULL:
            emptyScreen();
            emptyContainer();
            

        case TEMP_ALARM:
            if(millis() - tempAlarmStart > MAXTEMP){
                handleTempAlarm();
            }
        
    }
    
}

bool checkSpillingTime(){
    return ((millis() - startSpillingTime) > T1);
}

// dato che il pir è un pulsante non è proprio esatto isClicked così
// bisognerebbe tenere sempre premuto il pulsante del pir
bool userDetected(){
    return pir->isClicked();
}

void initialScreen(){
    screen->clear();
    screen->write(0,0, "PRESS OPEN TO");
    screen->write(0,1, "ENTER WASTE");
}

void doneScreen(){
    screen->clear();
    screen->write(0, 0, "WASTE RECEIVED");
    delay(T2);
}

void fullScreen(){
    screen->clear();
    screen->write(0, 0, "CONTAINER FULL");
    ledGreen->switchOff();
    ledRed->switchOn();
}

void problemScreen(){
    screen->clear();
    screen->write(0, 0, "PROBLEM");
    screen->write(0, 1, "DETECTED");
}

void empyScreen(){
    screen->clear();
    screen->write(0, 0, "EMPTYING...");
}

void acceptingWaste(){
    initialScreen();
    ledGreen->switchOn();
    servo->setPosition(CLOSE_SERVO);
}

int readSonar(){
    return sonar->getDistance();
}

float readTemperature(){
    return temp->getTemperature();
}

void goToSleep(){
    screen->clear();
    screen->write(0, 0, "SLEEPING...");
    ledGreen->switchOff();
    currentState = SLEEPING;
}

void wakeUp(){
    initialScreen();
    ledGreen->switchOn();
    currentState = IDLE;
}

void openServo(){
    servo->setPosition(OPEN_SERVO);
}

void closeServo(){
    servo->setPosition(CLOSE_SERVO);
}

// non so se ci sia qualcosa da collegare alla parte in java
void empyContainer(){
    screen->clear();
    servo->setPosition(EMPTY_SERVO);
    delay(T3);
    servo->setPosition(CLOSE_SERVO);
    currentState = IDLE;
    initialScreen();
    ledGreen->switchOn();
    ledRed->switchOff();
}

void handleTempAlarm(){
    problemScreen();
    ledGreen->switchOff();
    ledRed->switchOn();
    closeServo();
    tempAlarmStart = 0;
    currentState = IDLE;
}
 
void screenSpilling(){
    screen->clear();
    screen->write(0,0, "PRESS CLOSE");
    screen->write(0,1, "WHEN DONE");
}
