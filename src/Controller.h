#ifndef SLIDENAVIGATOR_CONTROLLER_H
#define SLIDENAVIGATOR_CONTROLLER_H

#include <Arduino.h>

class Controller {
    private:
        int const controllerPin = A0;
        uint16_t filteredButton = 0;
        uint16_t lastButtonState = 0;
        int buttonState = 0;
        unsigned long lastDebounceTime = 0;
        unsigned long debounceDelay = 25;

    public:
        Controller();
        bool newButtonPress();
        char getNewCommand() const;
};


#endif //SLIDENAVIGATOR_CONTROLLER_H
