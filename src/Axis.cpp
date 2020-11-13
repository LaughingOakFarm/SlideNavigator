#include "Axis.h"

Axis::Axis(
        uint8_t dirPin,
        uint8_t posPin,
        uint8_t enPin,
        uint8_t swPin,
        uint16_t readyPosition,
        uint16_t maxPosition
    ) :
    stepper(1, dirPin, posPin) {
    this->dirPin = dirPin;
    this->posPin = posPin;
    this->enPin = enPin;
    this->swPin = swPin;
    this->readyPosition = readyPosition;
    this->maxPosition = maxPosition;

    pinMode(enPin, OUTPUT);
    pinMode(swPin, INPUT_PULLUP);

    stepper.setMaxSpeed(maxSpeedStepper);
    stepper.setAcceleration(accelerationStepper);
}

bool Axis::home() {
    state = "homing";

    // do homing sequence

    state = "ready";
}

void Axis::moveTo(uint16_t pos) {
    state = "moving";
    stepper.moveTo(pos);

    // do moving stuff

    state = "holding";
}

bool Axis::readSwitch() {
//    Serial.print("  X Switch: ");
    buttonInput = analogRead(swPin);
    buttonInput = map(buttonInput, 0, 1023, 0, 2);
//    Serial.print(buttonInput);

    return buttonInput == 1;
}

String Axis::getState() {
    return state;
}

