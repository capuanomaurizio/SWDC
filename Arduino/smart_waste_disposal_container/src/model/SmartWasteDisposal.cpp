// #include "model/SmartWasteDisposal.h"
// #include "config.h"
// // serve il file di configurazione dei pin
// #include "devices/Led.h"
// // #include "kernel/Logger.h"
// #include "devices/Pir.h"
// //#include "devices/TempSensorLM35.h"
// #include "devices/ServoImpl.h"

// SmartWasteDisposal::SmartWasteDisposal(){
// }

// void SmartWasteDisposal::init(){
//     Sonar* Sonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 10000);
//     Pir* Pir = new Pir(PIR_PIN);
// //    TempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
//     Led* LedGreen = new Led(LED_GREEN);
//     Led* LedRed = new Led(LED_RED);
//     ServoImpl* Servo = new ServoImpl(SERVO);

//     state = IDLE;
// }

// bool SmartWasteDisposal::isIDLE(){
//     return state == IDLE;
// }

// // seguono tutte le varie funzioni