#ifndef SLIDENAVIGATOR_CONTROLLER_H
#define SLIDENAVIGATOR_CONTROLLER_H

#include <Arduino.h>

class Controller {
    private:
        int controllerPin = A0;
        uint16_t buttonInput;
        uint16_t lastButtonState;
        int buttonState;
        unsigned long lastDebounceTime = 0;
        unsigned long debounceDelay = 25;

    public:
        Controller();
        bool Controller::newButtonPress();
        char getNewCommand() const;
};


#endif //SLIDENAVIGATOR_CONTROLLER_H
