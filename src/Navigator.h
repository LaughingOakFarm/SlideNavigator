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

    uint8_t zoomLevel = 100;
    uint16_t xSlideMin = 600;
    uint16_t xSlideMax = 1800;
    uint16_t ySlideMin = 40;
    uint16_t ySlideMax = 850;
    uint16_t viewWidth = 17;
    uint16_t viewHeight = 13;
    uint16_t currentViewX = 0;
    uint16_t currentViewY = 0;
    uint16_t totalXViews;
    uint16_t totalYViews;
    String navState = "";
    bool navReady = false;

    bool firstRun = false;
    uint8_t testCount = 0;
    char activeCommand = 0;
    char nextCommand = 0;
    bool hasHomed = false;

    void setFirstRun();
    void checkHome();
    bool homeNav();
    void moveAxis();
    void checkFirstMove();
    bool continueMoving();

public:
    Navigator();
    void loop();
    bool runCommand();

    bool home();
    bool initializePoint();
    bool next();
    bool previous();
    bool capture();
    bool test();
    bool move();
    bool adjustZoom(int newZoomLevel = 40);
};


#endif //SLIDENAVIGATOR_NAVIGATOR_H
