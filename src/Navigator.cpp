#include "Navigator.h"

Navigator::Navigator() :
    communicator(),
    xAxis(7,6,5, A1, 10000, 10000),
    yAxis(10,9,8, A2, 10000, 10000),
    zAxis(4,3,2, A3, 10000, 10000) {}

void Navigator::loop() {
    if(communicator.getCommand() == 0) {
        communicator.hasNewCommand();
    }

    runCommand();
}

void Navigator::runCommand() {
    Serial.println(communicator.getCommand());
    Serial.println(communicator.getCommandPram());

    switch (communicator.getCommand()) {
        case 'H':
            return home();
        case 'N':
            return next();
        case 'P':
            return previous();
        case 'C':
            return capture();
        case 'K':
            return kill();
        case 'F':
            return focus();
    }
}

void Navigator::home() {
    if(xAxis.home() && yAxis.home() && zAxis.home()) {
        communicator.commandComplete();
    }
}

void Navigator::next() {
    communicator.commandComplete();
}

void Navigator::previous() {
    communicator.commandComplete();
}

void Navigator::capture() {
    communicator.commandComplete();
}

void Navigator::kill() {
    communicator.commandComplete();
}

void Navigator::focus() {
    communicator.commandComplete();
};
