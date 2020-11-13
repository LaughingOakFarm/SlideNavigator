#ifndef SLIDENAVIGATOR_NAVIGATOR_H
#define SLIDENAVIGATOR_NAVIGATOR_H

#include "Communicator.h"
#include "Axis.h"

class Communicator;

class Navigator {

private:
    Communicator communicator;
    Axis xAxis;
    Axis yAxis;
    Axis zAxis;

    uint16_t sideWidth = 10000;
    uint16_t sideHeight = 10000;
    uint8_t viewX = 0;
    uint8_t viewY = 0;
    uint16_t viewNum = 0;

    bool firstRun = false;

public:
    Navigator();
    void loop();
    void runCommand();
    void home();
    void next();
    void previous();
    void capture();
    void kill();
    void focus();
};


#endif //SLIDENAVIGATOR_NAVIGATOR_H
