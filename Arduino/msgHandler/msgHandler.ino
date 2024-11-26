#include "MsgService.h"

int temp = 0, perc = 0;

void setup(){
  MsgService.init();
}

void loop(){
  if (MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();    
    if (msg->getContent() == "check"){
      temp = random(10, 60);
      perc = random(0,100);
      MsgService.sendMsg((String)perc+":"+temp); 
    } else if (msg->getContent() == "empty") {
      //do stuff, then answer
    } else if (msg->getContent() == "restore") {
      //do stuff, then answer
    }
    /* NOT TO FORGET: msg deallocation */
    delete msg;
  }
};
