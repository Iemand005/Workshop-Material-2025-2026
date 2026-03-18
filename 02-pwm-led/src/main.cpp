#include <Arduino.h>

#define ledPin 2

void setup() {
    pinMode(ledPin, OUTPUT);

    analogWrite(ledPin, 255);  // Set duty cycle to 100% (255 out of 255)
    delay(1000);               // Wait for 1 second
    analogWrite(ledPin, 0);    // Set duty cycle to 0% (0 out of 255)
    delay(1000);
    analogWrite(ledPin, 126);  // Set duty cycle to 50% (126 out of 255)
    delay(1000);
}

void loop() {
    // increase the LED brightness
    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
        analogWrite(ledPin, dutyCycle);
        delay(5);
    }

    // decrease the LED brightness
    for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
        analogWrite(ledPin, dutyCycle);
        delay(5);
    }
}