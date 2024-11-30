#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
//#include "devices/TempSensor.h"
#include "devices/Led.h"
#include "devices/ServoImpl.h"

class SmartWasteDisposal{


public:
    SmartWasteDisposal();

    void init();

    void openServo();
    void closeServo();
    void readyToAccept();

    bool isIDLE();
    void goToSleep();
    void wakeUp();

    void readyToOpen();
    bool isReadyToOpen();

    void spilling();
    void isSpllingCompleted();

    // e tutte le varie funzioni


private:

    // variabili ipotetiche

    enum{STATI1, STATO2, IDLE} state;

    Led* LedGreen;
    Led* LedRed;
    
    Sonar* Sonar;
    Pir* Pir;
 //   TempSensor* TempSensor;
    ServoImpl* Servo;  

};