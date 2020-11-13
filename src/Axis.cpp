#include "Axis.h"

Axis::Axis(
        uint8_t dirPin,
        uint8_t posPin,
        uint8_t enPin,
        uint8_t swPin,
        uint16_t readyPosition,
        uint16_t maxPosition,
        bool invert
    ) :
    stepper(1, posPin, dirPin) {
    this->dirPin = dirPin;
    this->posPin = posPin;
    this->enPin = enPin;
    this->swPin = swPin;
    this->readyPosition = readyPosition;
    this->maxPosition = maxPosition;
    this->invert = invert;

    pinMode(enPin, OUTPUT);
    pinMode(swPin, INPUT_PULLUP);

    stepper.setMaxSpeed(maxSpeedStepper);
    stepper.setAcceleration(accelerationStepper);
}

bool Axis::home() {
    if(commandFirstRun) {
        // Clear the state and re-home
        // Move at a constant speed towards the zero position
        state = "zeroing";
        stepper.setMaxSpeed(500);
        stepper.moveTo(check(-(maxPosition+200)));

        commandFirstRun = false;
    } else if(state == "zeroing") {
        stepper.run();

        // If a limit switch is hit, zero the stepper position
        if(switchPressed()) {
            state = "readying";
            stepper.setCurrentPosition(0);
            stepper.setMaxSpeed(maxSpeedStepper);
            stepper.moveTo(check(readyPosition));
        }
    } else if(state == "readying") {
        // Proceed to the designated ready position
        stepper.run();

        if(stepper.targetPosition() == stepper.currentPosition()) {
            state = "ready";
//            Serial.println(state);
            return true;
        }
    } else if(state == "ready") {
        return true;
    }

    return false;
}

bool Axis::moveTo(uint16_t pos) {
    if(state != "ready" && state != "moving" && state != "holding") {
        Serial.println("<Needs to Home>");
        return true;
    }

    if(commandFirstRun) {
        state = "moving";
        stepper.moveTo(check(pos));
        commandFirstRun = false;
    }

    stepper.run();

    if(stepper.targetPosition() == stepper.currentPosition()) {
        state = "holding";
        return true;
    }

    return false;
}

bool Axis::moveRandom() {
    if(commandFirstRun) {
        randomNum = random(0, maxPosition);
    }

    return moveTo(randomNum);
}

bool Axis::switchPressed() {
//    Serial.print("  X Switch: ");
    buttonInput = analogRead(swPin);
    buttonInput = map(buttonInput, 0, 1023, 0, 2);
//    Serial.print(buttonInput);

    return buttonInput == 1;
}

String Axis::getState() {
    return state;
}

void Axis::firstRun() {
    commandFirstRun = true;
}

short Axis::check(short demandPos) {
    if(demandPos >= 0 && demandPos > maxPosition) {
        demandPos = maxPosition;
    }

    if(invert) {
        if(demandPos > 0) {
            demandPos = demandPos * -1;
        } else {
            demandPos = abs(demandPos);
        }
    }

    return demandPos;
}

