#ifndef SLIDENAVIGATOR_AXIS_H
#define SLIDENAVIGATOR_AXIS_H

#include <AccelStepper.h>
#include "Arduino.h"

class Axis {

private:
    AccelStepper stepper;
    uint8_t dirPin;
    uint8_t posPin;
    uint8_t enPin;
    uint8_t swPin;

    uint16_t readyPosition;
    uint16_t maxPosition;

    uint16_t const maxSpeedStepper     = 2000;
    uint16_t const accelerationStepper = 1000;

    uint16_t buttonInput = 0;
    String state = ""; // homing, ready, moving, holding
    bool commandFirstRun = false;
    bool invert = false;

    bool switchPressed();

public:
    Axis(
        uint8_t dirPin,
        uint8_t posPin,
        uint8_t enPin,
        uint8_t swPin,
        uint16_t readyPosition,
        uint16_t maxPosition,
        bool invert
    );
    void moveTo(uint16_t pos);
    bool home();
    String getState();
    void firstRun();
};


#endif //SLIDENAVIGATOR_AXIS_H
