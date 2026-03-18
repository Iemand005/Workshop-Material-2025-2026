#include <Arduino.h>

/*
Make sure you use a voltage divider to step down the voltage from the sensor to a safe level for the ESP32 ADC input (0-5V).
Use a 10kΩ resistor in series with the sensor output.
*/

#define pinSensor 36
#define pinLed 2
const int threshold = 2000; // Example threshold value for the sensor

void setup() {
    Serial.begin(115200);
    Serial.println("Starting ...");

    pinMode(pinSensor, INPUT); // Set the sensor pin as input
    pinMode(pinLed, OUTPUT);

    Serial.println("Setup complete");
}

void loop() {
    int sensorValue = analogRead(pinSensor); // range 0 - 4095 for 12-bit ADC

    Serial.print("Sensor value: ");
    Serial.println(sensorValue);

    if (sensorValue > threshold) {
        digitalWrite(pinLed, LOW); // Turn the LED off
        Serial.println("LED OFF");
    } else {
        digitalWrite(pinLed, HIGH); // Turn the LED on
        Serial.println("LED ON");
    }

  delay(100);
}