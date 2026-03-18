#include <Arduino.h>

#define pinButton 4
#define pinLed 2

void setup() {
    Serial.begin(115200);
    Serial.println("Starting ...");

    pinMode(pinButton, INPUT_PULLUP); // Set the button pin as input with pull-up resistor
    pinMode(pinLed, OUTPUT);

    Serial.println("Setup complete");
}

void loop() {
    // The button is active low, so we need to invert the read value
    bool digitalReadButton = !digitalRead(pinButton);


    if (digitalReadButton == HIGH) {
        Serial.println("Button pressed");
        digitalWrite(pinLed, HIGH);
    } else {
        Serial.println("Button not pressed");
        digitalWrite(pinLed, LOW);
    }

    delay(50); // Add a small delay to avoid flooding the serial output
}