#include "Controller.h"

Controller::Controller() {
    pinMode(controllerPin, INPUT);
};

bool Controller::newButtonPress() {
    buttonInput = analogRead(controllerPin);
    buttonInput = map(buttonInput, 0, 1023, 0, 56);

    if (buttonInput != lastButtonState) {
        lastDebounceTime = millis();
    }

    lastButtonState = buttonInput;

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (buttonInput != buttonState) {
            buttonState = buttonInput;

            if(buttonInput != 0) {
                return true;
            }
        }
    }

    return false;
}

char Controller::getNewCommand() const {
    switch (buttonInput) {
        case 50:
            return "H";
        case 53:
            return "P";
        case 54:
            return "C";
        case 55:
            return "N";
    }

    return "";
}