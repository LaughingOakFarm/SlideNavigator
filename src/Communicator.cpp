#include "Communicator.h"

Communicator::Communicator() : controller() {};

bool Communicator::hasNewCommand() {
    // If there is a current command, don't look for new one
    if(currentCommand != 0) {
        return false;
    }

    if (controller.newButtonPress()) {
        currentCommand = controller.getNewCommand();
        commandPram = 0;
        readingCommand = false;

        return true;
    }

    if (Serial.available() > 0) {
        rx_byte = Serial.read();

        if ((rx_byte >= '0') && (rx_byte <= '9')) {
            Serial.print("Number received: ");
            Serial.println(rx_byte);
        }
        else if (rx_byte == '\n') {
            Serial.println("Newline");
        }
        else {
            Serial.println("Not a number.");
            Serial.println(rx_byte);
        }
    }

    // Check Manual Controller First
    if(Serial.available() > 0) {
        currentCommand = Serial.read();
        return true;
    }

    return false;
}

void Communicator::confirmComplete() {
    Serial.println(String("<") + currentCommand + String(" Complete>"));

    currentCommand = 0;
}