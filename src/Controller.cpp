#include "Controller.h"

Controller::Controller() {
    pinMode(controllerPin, INPUT);
};

bool Controller::newButtonPress() {
    uint16_t buttonInput = analogRead(controllerPin);

    if(buttonInput < 250) {
        filteredButton = 0;
    } else if(buttonInput >= 900 && buttonInput <= 950) {
        filteredButton = 50;
    } else if(buttonInput >= 980 && buttonInput <= 989) {
        filteredButton = 53;
    } else if(buttonInput >= 1001 && buttonInput <= 1008) {
        filteredButton = 54;
    } else if(buttonInput >= 1012) {
        filteredButton = 55;
    } else {
        filteredButton = lastButtonState;
    }

    if (filteredButton != lastButtonState) {
//        Serial.print("millis reset - ");
//        Serial.println(filteredButton);
        lastDebounceTime = millis();
    }

    lastButtonState = filteredButton;

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (filteredButton != buttonState) {
            buttonState = filteredButton;

            if(filteredButton != 0) {
                return true;
            }
        }
    }

    return false;
}

char Controller::getNewCommand() const {
    switch (filteredButton) {
        case 50:
            return 'H';
        case 53:
            return 'P';
        case 54:
            return 'C';
        case 55:
            return 'N';
    }

    return 0;
}