#include "Navigator.h"
#include "math.h"

Navigator::Navigator() :
    communicator(),
    xAxis('X', 6,7,5, A1, 50, 2000, false, 8000),
    yAxis('Y', 9,10,8, A2, 40, 850, false, 6000),
    zAxis('Z', 3,4,2, A3, 585, 850, true, 2000) {

    adjustZoom(40);
}

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
        case 'I':
            return initializePoint();
        case 'N':
            return next();
        case 'P':
            return previous();
        case 'C':
            return capture();
        case 'T':
            return test();
        case 'A':
            return adjustZoom(communicator.getCommandPram());
        case 'X':
        case 'Y':
        case 'Z':
            return move();
    }

    return false;
}

bool Navigator::home() {
    if(communicator.getCommandPram() == 0) {
        bool x = xAxis.home();
        bool y = yAxis.home();
        bool z = zAxis.home();

        if(x && y && z) {
            hasHomed = true;
            Serial.println("<Homed>");
            navReady = false;
            return true;
        }

        return false;
    } else {
        bool axis;

        if(communicator.getCommandPram() == 1) {
            axis = xAxis.home();
        } else if(communicator.getCommandPram() == 2) {
            axis = yAxis.home();
        } else if(communicator.getCommandPram() == 3) {
            axis = zAxis.home();
        } else {
            Serial.println("<Bad Home Pram>");
            return true;
        }

        if(axis) {
            hasHomed = true;
            Serial.println("<Homed>");
            navReady = false;
            return true;
        }

        return false;
    }
}

bool Navigator::initializePoint() {
    if(communicator.getCommandPram() == 0) {
        Serial.println("<No InitPoint Selected>");
        return true;
    }

    if(navState == "moving") {
        return continueMoving();
    }

    uint8_t xMargin = 5;
    uint8_t yMargin = 3;

    switch (communicator.getCommandPram()) {
        case 1:
            currentViewX = xMargin;
            currentViewY = yMargin;
            break;
        case 2:
            currentViewX = floor(totalXViews / 2);
            currentViewY = yMargin;
            break;
        case 3:
            currentViewX = totalXViews - xMargin;
            currentViewY = yMargin;
            break;
        case 4:
            currentViewX = xMargin;
            currentViewY = floor(totalYViews / 2);
            break;
        case 5:
            currentViewX = floor(totalXViews / 2);
            currentViewY = floor(totalYViews / 2);
            break;
        case 6:
            currentViewX = totalXViews - xMargin;
            currentViewY = floor(totalYViews / 2);
            break;
        case 7:
            currentViewX = xMargin;
            currentViewY = totalYViews - yMargin;
            break;
        case 8:
            currentViewX = floor(totalXViews / 2);
            currentViewY = totalYViews - yMargin;
            break;
        case 9:
            currentViewX = totalXViews - xMargin;
            currentViewY = totalYViews - yMargin;
            break;
    }

    moveAxis();
    return false;
}

bool Navigator::next() {
    checkFirstMove();

    if(navState == "homing") {
        if(homeNav()) {
            navState = "ready";
        }
    } else if(navState == "moving") {
        return continueMoving();
    } else if(currentViewX < totalXViews) {
        // if there is more room to move on the X, do it
        currentViewX++;
        moveAxis();
    } else if(currentViewY == totalYViews && currentViewX == totalXViews) {
        // is the end of the slide
        // if x is max and y is max, then home, clear status
        if(homeNav()) {
            currentViewX = 0;
            currentViewY = 0;
            navState = "";
            navReady = false;
            Serial.println("<Navigate Complete>");
        }
    } else if(currentViewX == totalXViews) {
        // if it is on the last slide on the X, home x & y, y++, x = 1
        if(homeNav()) {
            currentViewX = 1;
            currentViewY++;
            moveAxis();
        }
    } else {
        // this should never happen.
        Serial.println("<Nav Error!>");
    }

    return false;
}

bool Navigator::previous() {
    // Add logic to back going back if not nav is not ready or it is at zero view num
    checkFirstMove();

    if (navState == "homing") {
        if (homeNav()) {
            navState = "ready";
        }
    } else if (navState == "moving") {
        return continueMoving();
    } else if (currentViewX > 0) {
        // if there is more room to move on the X, do it
        currentViewX--;
        moveAxis();
    } else if (currentViewY == 0 && currentViewX == 0) {
        // then we are back at the beginning, re-home
        if (homeNav()) {
            navState = "ready";
            return true;
        }
    } else if (currentViewX == 0) {
        // if it the first x view, re-home, max x, subtract 1 from y
        if (homeNav()) {
            currentViewX = totalXViews;
            currentViewY--;
            moveAxis();
        }
    } else {
        // this should never happen.
        Serial.println("<Nav Error!>");
    }

    return false;
}

bool Navigator::capture() {
    // All this does is post <New Command:X> to the computer
    // for it to read.
    return true;
}

bool Navigator::test() {
    bool x, y, z;
    navReady = false;

    if (testCount < communicator.getCommandPram()) {
        x = xAxis.moveRandom();
        y = yAxis.moveRandom();
        z = zAxis.moveRandom();

        if(x && y && z) {
            Serial.println(String("<Test Position ")+testCount+String(">"));
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
    navReady = false;

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
}

bool Navigator::homeNav() {    bool x = xAxis.home();
    bool y = yAxis.home();

    return x && y;

}

void Navigator::moveAxis() {
    xAxis.firstRun();
    xAxis.moveTo((currentViewX*viewWidth)+xSlideMin);

    yAxis.firstRun();
    yAxis.moveTo((currentViewY*viewHeight)+ySlideMin);

    navState = "moving";
    Serial.println(String("<Moving: ")+currentViewX+String(",")+currentViewY+String(">"));
}

void Navigator::checkFirstMove() {
    if (!navReady) {
        totalXViews = floor((xSlideMax - xSlideMin) / viewWidth);
        totalYViews = floor((ySlideMax - ySlideMin) / viewHeight);
        navState = "homing";
        navReady = true;
        currentViewX = 0;
        currentViewY = 0;

        Serial.println(String("<Max: ")+totalXViews+String(",")+totalYViews+String(">"));
    }
}

bool Navigator::continueMoving() {
    bool x = xAxis.run();
    bool y = yAxis.run();

    if (x && y) {
        navState = "ready";
        return true;
    }

    return false;
}

bool Navigator::adjustZoom(int newZoomLevel) {
    if(newZoomLevel == 100) {
        if(zoomLevel == 40) {
            zoomLevel = 100;
            viewWidth = 17;
            viewHeight = 13;
        } else {
            Serial.println("<All ready at zoom 100x>");
        }
    } else if(newZoomLevel == 40 && zoomLevel == 100) {
        if(zoomLevel == 100) {
            zoomLevel = 40;
            viewWidth = 44;
            viewHeight = 32;
        } else {
            Serial.println("<All ready at zoom 40x>");
        }
    } else {
        Serial.println("<Only Use Zoom Levels: 40x or 100x>");
    }

    navReady = false;
    checkFirstMove();

    return true;
}

