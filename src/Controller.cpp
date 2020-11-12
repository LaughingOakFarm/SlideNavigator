#include "Controller.h"

Controller::Controller() = default;

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

String Controller::getNewCommand() const {
    switch (buttonInput) {
        case 50:
            return "home";
        case 53:
            return "previous";
        case 54:
            return "capture";
        case 55:
            return "next";
    }

    return "";
}