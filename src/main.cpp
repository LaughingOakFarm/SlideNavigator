#include <AccelStepper.h>

uint8_t controlPin = A0;
uint8_t xEnablePin = 5;
uint8_t yEnablePin = 8;
uint8_t zEnablePin = 2;
uint8_t xHomePin = A1;
uint8_t yHomePin = A2;
uint8_t zHomePin = A3;

AccelStepper xStepper = AccelStepper(1, 7, 6);
AccelStepper yStepper = AccelStepper(1, 10, 9);
AccelStepper zStepper = AccelStepper(1, 4, 3);

uint16_t maxSpeedStepper     = 2000;
uint16_t accelerationStepper = 1000;

int buttonInput;

void setup() {
    zStepper.setMaxSpeed(maxSpeedStepper);
    zStepper.setAcceleration(accelerationStepper);

    yStepper.setMaxSpeed(maxSpeedStepper);
    yStepper.setAcceleration(accelerationStepper);

    xStepper.setMaxSpeed(maxSpeedStepper);
    xStepper.setAcceleration(accelerationStepper);

    Serial.begin(115200);

    pinMode(controlPin, INPUT);
    pinMode(xEnablePin, OUTPUT);
    pinMode(yEnablePin, OUTPUT);
    pinMode(zEnablePin, OUTPUT);
    pinMode(xHomePin, INPUT_PULLUP);
    pinMode(yHomePin, INPUT_PULLUP);
    pinMode(zHomePin, INPUT_PULLUP);
}

void loop() {
    Serial.print("  X Switch: ");
    buttonInput = analogRead(xHomePin);
    buttonInput = map(buttonInput, 0, 1023, 0, 2);
    Serial.print(buttonInput);

    Serial.print("  Y Switch: ");
    buttonInput = analogRead(yHomePin);
    buttonInput = map(buttonInput, 0, 1023, 0, 2);
    Serial.print(buttonInput);

    Serial.print("  Z Switch: ");
    buttonInput = analogRead(zHomePin);
    buttonInput = map(buttonInput, 0, 1023, 0, 2);
    Serial.print(buttonInput);

    Serial.print("  Control Input: ");
    buttonInput = analogRead(controlPin);
    buttonInput = map(buttonInput, 0, 1023, 0, 56);
    Serial.println(buttonInput);

    delay(250);

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