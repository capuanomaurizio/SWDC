#include "CommManager.h"

CommManager::CommManager(){
    MsgService.init();
}

String CommManager::checkReceived() {
    if (MsgService.isMsgAvailable()){
        Msg* msg = MsgService.receiveMsg();  
        String message = msg->getContent();
        /* NOT TO FORGET: msg deallocation */
        delete msg;
        return message; 
    } else {
        return "";
    }
}

void CommManager::sendPercentageTemperature(int perc, int temp){
    MsgService.sendMsg((String)perc+":"+temp); 
}

void CommManager::sendEmptyContainer(){
    MsgService.sendMsg("emptied");
}

void CommManager::sendRestoreContainer(){
    MsgService.sendMsg("restored");
}