#ifndef SLIDENAVIGATOR_AXIS_H
#define SLIDENAVIGATOR_AXIS_H

#include <AccelStepper.h>
#include "Arduino.h"

class Axis {

private:
    AccelStepper stepper;
    char label;
    uint8_t swPin;

    short readyPosition;
    short maxPosition;

    short buttonInput = 0;
    String state = ""; // homing, ready, moving, holding
    bool commandFirstRun = false;
    bool invert = false;
    short randomNum = 0;
    short maxSpeed;

    bool switchPressed();
    short check(short demandPos, bool allowNeg = false);

public:
    Axis(
        char label,
        uint8_t dirPin,
        uint8_t posPin,
        uint8_t enPin,
        uint8_t swPin,
        uint16_t readyPosition,
        uint16_t maxPosition,
        bool invert,
        short maxSpeed
    );
    bool moveTo(uint16_t pos);
    bool moveRandom();
    bool home();
    void firstRun();
};


#endif //SLIDENAVIGATOR_AXIS_H
