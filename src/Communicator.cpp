#include "Communicator.h"

Communicator::Communicator() : controller() {};

bool Communicator::hasNewCommand() {
    // If there is a current command, don't look for new one
    if(currentCommand != 0) {
        return false;
    }

    // Check Manual Controller First
    if (controller.newButtonPress()) {
        currentCommand = controller.getNewCommand();
        confirmReceived();
        return true;
    } else if(Serial.available() > 0) {
        currentCommand = Serial.read();
        confirmReceived();
        return true;
    }

    return false;
}

void Communicator::confirmReceived() {
    Serial.println(String("<") + currentCommand + String(" Received>"));
}

void Communicator::confirmComplete() {
    Serial.println(String("<") + currentCommand + String(" Complete>"));

    currentCommand = 0;
}