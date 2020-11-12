#include "Communicator.h"

Communicator::Communicator() : controller() {};

bool Communicator::hasNewCommand() {
    // If there is a current command, don't look for new one
    if(currentCommand != 0) {
        Serial.println(String("<Currently Running Command:")+currentCommand+String(">"));
        return false;
    }

    if (controller.newButtonPress()) {
        if(setNewCommand(controller.getNewCommand(), 1)) {
            return true;
        }
    }

    if (Serial.available() > 0) {
        String newCommand = Serial.readStringUntil(':');
        newCommand.toUpperCase();
        int newPram = Serial.readStringUntil('\n').toInt();

        if(setNewCommand(newCommand[0], newPram)) {
            return true;
        }
    }

    return false;
}

bool Communicator::setNewCommand(char newCommand, int newPram) {
    if(commands.indexOf(newCommand) == -1) {
        Serial.println(String("<Command Not Found:")+newCommand+String(">"));
        return false;
    }

    currentCommand = newCommand;
    commandPram = newPram;

    return true;
}

void Communicator::commandComplete() {
    Serial.println(String("<Complete>"));

    currentCommand = 0;
    commandPram = 0;
}

char Communicator::getCommand() {
    return currentCommand;
}

int Communicator::getCommandPram() {
    return commandPram;
}
