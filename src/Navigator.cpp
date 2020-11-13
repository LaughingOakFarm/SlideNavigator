#include "Navigator.h"

Navigator::Navigator() :
    communicator(),
    xAxis(6,7,5, A1, 50, 10000, false),
    yAxis(9,10,8, A2, 400, 450, false),
    zAxis(3,4,2, A3, 100, 10000, true) {}

void Navigator::loop() {
    if(communicator.getCommand() == 0) {
        if(communicator.hasNewCommand()) {
//            Serial.println("New Command:");
//            Serial.println(communicator.getCommand());
//            Serial.println(communicator.getCommandPram());
            firstRun = true;
        }
    }

    // run the current command, non-blocking
    runCommand();
    firstRun = false;
}

void Navigator::runCommand() {
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
    if(firstRun) {
        xAxis.firstRun();
        yAxis.firstRun();
        zAxis.firstRun();
    }

    bool x = xAxis.home();
    bool y = yAxis.home();
    bool z = zAxis.home();

    if(x && y && z) {
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
