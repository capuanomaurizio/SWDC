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
enum State { IDLE, WAITING_WASTE, SPILLING, FULL, TEMP_ALARM, SLEEPING };
State currentState = IDLE;

volatile bool buttonOpenPressed = false;
volatile long lastUserDetection = 0;
long startSpillingTime = 0;
long tempAlarmStart = 0;
bool tempProbDetected = false;
bool emptying = false, restoring = false;

void doneScreen();
void fullScreen();
void problemScreen();
void emptyScreen();
int readSonar();
float readTemperature();
void goToSleep();
void userDetected();
void wakeUp();
void openDoor();
void closeDoor();
void emptyContainer();
void handleTempAlarm();
void screenSpilling();
void checkSerialComm();
void acceptingWaste();
void startSpilling();
bool checkSpillingTime();

void setup() {
    ledGreen = new Led(LED_GREEN);
    ledRed = new Led(LED_RED);
    servo = new ServoImpl(SERVO);
    //pir = new Pir(PIR_PIN);
    pir = new Button(PIR_PIN);
    buttonOpen = new Button(BUTTON_OPEN);
    buttonClose = new Button(BUTTON_CLOSE);
    screen = new Screen(16, 4);
    sonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN);
    temp = new Temp(TEMP_PIN);
    commManager = new CommManager();
    requiredAction = "";
    attachInterrupt(digitalPinToInterrupt(2), userDetected, RISING); 
}

void loop() {
    if(readTemperature() > MAXTEMP){
        if (tempProbDetected) {
            if(currentState != TEMP_ALARM && ((millis() - tempAlarmStart) > MAXTEMPTIME)){
                currentState = TEMP_ALARM;
                problemScreen();
            }
        } else {
            tempAlarmStart = millis();
            tempProbDetected = true;
        } 
    }
    else{
        tempProbDetected = false;
    }
    if(currentState == WAITING_WASTE && ((millis() - lastUserDetection) > TIME_TO_SLEEP)){
        goToSleep();
    }
    checkSerialComm();
    switch (currentState){
        case SLEEPING:
            break;
        case IDLE:
            acceptingWaste();
            break;
        case WAITING_WASTE:
            if(buttonOpen->isClicked()){
                openDoor();
                startSpilling();
            }
            break;
        case SPILLING:
            if(buttonClose->isClicked() || checkSpillingTime()){
                closeDoor();
                doneScreen();
                currentState = IDLE;
            }
            if (readSonar() < FULL_THRESHOLD){ 
                closeDoor();           
                fullScreen();
                currentState = FULL;
            }
            lastUserDetection = millis();
            break;
        case FULL:
            if (emptying) {
                emptyScreen();
                emptyContainer();
            }
            lastUserDetection = millis();
            break;
        case TEMP_ALARM:
            if (restoring) {
                handleTempAlarm();
            }
            lastUserDetection = millis();
            break;
    }   
}

void checkSerialComm(){
    requiredAction = commManager->checkReceived();
    if(requiredAction != ""){
        if(requiredAction == "check") {
            commManager->sendPercentageTemperature((CAPACITY - sonar->getDistance())*100/(CAPACITY - FULL_THRESHOLD), temp->getTemperature());
        } else if (requiredAction == "empty") {
            emptying = true;
        } else if (requiredAction == "restore") {
            restoring = true;
        }
    }
}

bool checkSpillingTime(){
    return ((millis() - startSpillingTime) > T1);
}

void userDetected(){
    lastUserDetection = millis();
    if(currentState == SLEEPING)
        wakeUp();
}

void acceptingWaste(){
    ledGreen->switchOn();
    servo->setPosition(CLOSE_SERVO);
    currentState = WAITING_WASTE;
    screen->clear();
    screen->write(0,0, "PRESS OPEN TO");
    screen->write(0,1, "ENTER WASTE");
}
 
void startSpilling(){
    screen->clear();
    screen->write(0,0, "PRESS CLOSE");
    screen->write(0,1, "WHEN DONE");
    startSpillingTime = millis();
    currentState = SPILLING;
}

void doneScreen(){
    screen->clear();
    screen->write(0, 0, "WASTE RECEIVED");
    delay(T2);
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
    currentState = IDLE;
}

void openDoor(){
    servo->setPosition(OPEN_SERVO);
}

void closeDoor(){
    servo->setPosition(CLOSE_SERVO);
}

void emptyScreen(){
    screen->clear();
    screen->write(0, 0, "EMPTYING...");
}

void emptyContainer(){
    servo->setPosition(EMPTY_SERVO);
    delay(T3);
    servo->setPosition(CLOSE_SERVO);
    currentState = IDLE;
    ledRed->switchOff();
    emptying = false;
}

void handleTempAlarm(){
    tempAlarmStart = 0;
    tempProbDetected = false;
    currentState = IDLE;
    ledRed->switchOff();
    restoring = false;
}

void fullScreen(){
    screen->clear();
    screen->write(0, 0, "CONTAINER FULL");
    ledGreen->switchOff();
    ledRed->switchOn();
    commManager->sendEmptyContainer();
}

void problemScreen(){
    screen->clear();
    screen->write(0, 0, "PROBLEM");
    screen->write(0, 1, "DETECTED");
    ledGreen->switchOff();
    ledRed->switchOn();
    closeDoor();
    commManager->sendRestoreContainer();
}