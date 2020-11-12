#include <AccelStepper.h>
#include "Communicator.h"

//uint8_t xEnablePin = 5;
//uint8_t yEnablePin = 8;
//uint8_t zEnablePin = 2;
//uint8_t xHomePin = A1;
//uint8_t yHomePin = A2;
//uint8_t zHomePin = A3;
//
//AccelStepper xStepper = AccelStepper(1, 7, 6);
//AccelStepper yStepper = AccelStepper(1, 10, 9);
//AccelStepper zStepper = AccelStepper(1, 4, 3);

Communicator communicator = Communicator();

uint16_t maxSpeedStepper     = 2000;
uint16_t accelerationStepper = 1000;

void setup() {
    Serial.begin(115200);

//    zStepper.setMaxSpeed(maxSpeedStepper);
//    zStepper.setAcceleration(accelerationStepper);
//
//    yStepper.setMaxSpeed(maxSpeedStepper);
//    yStepper.setAcceleration(accelerationStepper);
//
//    xStepper.setMaxSpeed(maxSpeedStepper);
//    xStepper.setAcceleration(accelerationStepper);
//
//    pinMode(xEnablePin, OUTPUT);
//    pinMode(yEnablePin, OUTPUT);
//    pinMode(zEnablePin, OUTPUT);
//    pinMode(xHomePin, INPUT_PULLUP);
//    pinMode(yHomePin, INPUT_PULLUP);
//    pinMode(zHomePin, INPUT_PULLUP);
}

void loop() {
    if(communicator.hasNewCommand()) {
        Serial.println(communicator.getCommand());
        Serial.println(communicator.getCommandPram());
        communicator.commandComplete();
    }

//    Serial.print("  X Switch: ");
//    buttonInput = analogRead(xHomePin);
//    buttonInput = map(buttonInput, 0, 1023, 0, 2);
//    Serial.print(buttonInput);
//
//    Serial.print("  Y Switch: ");
//    buttonInput = analogRead(yHomePin);
//    buttonInput = map(buttonInput, 0, 1023, 0, 2);
//    Serial.print(buttonInput);
//
//    Serial.print("  Z Switch: ");
//    buttonInput = analogRead(zHomePin);
//    buttonInput = map(buttonInput, 0, 1023, 0, 2);
//    Serial.print(buttonInput);

//    zStepper.moveTo(400);
//    yStepper.moveTo(400);
//    xStepper.moveTo(400);
//    zStepper.runToPosition();
//    yStepper.runToPosition();
//    xStepper.runToPosition();
//
//    zStepper.moveTo(0);
//    yStepper.moveTo(0);
//    xStepper.moveTo(0);
//    zStepper.runToPosition();
//    yStepper.runToPosition();
//    xStepper.runToPosition();
}