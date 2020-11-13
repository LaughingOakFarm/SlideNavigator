#include "Navigator.h"

Navigator navigator = Navigator();

void setup() {
    Serial.begin(115200);
}

void loop() {
    navigator.loop();
}