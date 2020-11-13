#include "Navigator.h"

Navigator::Navigator() :
    communicator(),
    xAxis(6,7,5, A1, 50, 2600, false),
    yAxis(9,10,8, A2, 400, 425, false),
    zAxis(3,4,2, A3, 100, 600, true) {}

void Navigator::loop() {
    if(activeCommand == 0) {
        if(communicator.hasNewCommand()) {
            firstRun = true;
            activeCommand = communicator.getCommand();

            if (activeCommand == 'T') {
                // always re-home for test command
                hasHomed = false;
            }
        }
    }

    // run the current command, non-blocking
    bool done = runCommand();
    firstRun = false;

    if (done) {
        if (nextCommand) {
            activeCommand = nextCommand;
            nextCommand = 0;
            firstRun = true;
        } else {
            activeCommand = 0;
            communicator.commandComplete();
        }
    }
}

bool Navigator::runCommand() {
    setFirstRun();
    checkHome();

    switch (activeCommand) {
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
        case 'T':
            return test();
        case 'X':
        case 'Y':
        case 'Z':
            return move();
    }

    return false;
}

bool Navigator::home() {
    bool x = xAxis.home();
    bool y = yAxis.home();
    bool z = zAxis.home();

    if(x && y && z) {
        hasHomed = true;
        return true;
    }

    return false;
}

bool Navigator::next() {
    return true;
}

bool Navigator::previous() {
    return true;
}

bool Navigator::capture() {
    return true;
}

bool Navigator::kill() {
    return true;
}

bool Navigator::focus() {
    return true;
}

bool Navigator::test() {
    bool x, y, z;

    if (testCount < communicator.getCommandPram()) {
        x = xAxis.moveRandom();
        y = yAxis.moveRandom();
        z = zAxis.moveRandom();

        if(x && y && z) {
            testCount++;
            firstRun = true;
            setFirstRun();
            firstRun = false;
        }
    } else {
        testCount = 0;
        activeCommand = 'H';
        return false;
    }

    return false;
}

bool Navigator::move() {
    bool done = false;

    if(activeCommand == 'X') {
        done = xAxis.moveTo(communicator.getCommandPram());
    } else if(activeCommand == 'Y') {
        done = yAxis.moveTo(communicator.getCommandPram());
    } else if(activeCommand == 'Z') {
        done = zAxis.moveTo(communicator.getCommandPram());
    }

    return done;
}

void Navigator::setFirstRun() {
    if(firstRun) {
        xAxis.firstRun();
        yAxis.firstRun();
        zAxis.firstRun();
    }
}

void Navigator::checkHome() {
    if(!hasHomed && activeCommand && activeCommand != 'H') {
        nextCommand = activeCommand;
        activeCommand = 'H';
        firstRun = true;
    }
};


