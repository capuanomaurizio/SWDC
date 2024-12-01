#ifndef __COMMMANAGER__
#define __COMMMANAGER__

#include "Arduino.h"
#include "MsgService.h"

class CommManager {
    public:
        CommManager();
        String checkReceived();
        void sendPercentageTemperature(int perc, int temp);
        void sendEmptyContainer();
        void sendRestoreContainer();
};

#endif
