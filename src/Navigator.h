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
    uint8_t testCount = 0;
    char activeCommand = 0;
    char nextCommand = 0;
    bool hasHomed = false;

    void setFirstRun();
    void checkHome();

public:
    Navigator();
    void loop();
    bool runCommand();

    bool home();
    bool next();
    bool previous();
    bool capture();
    bool test();
    bool move();
};


#endif //SLIDENAVIGATOR_NAVIGATOR_H
