#include <Arduino.h>
#include <Wire.h>

/*
Connect any I2C devices to the SDA and SCL pins, VCC and GND.
Then run this sketch. It will scan the I2C bus for devices and print their addresses to the Serial Monitor.

    Arduino Nano    ESP32
SDA A4              21
SCL A5              22
*/

void setup() {
    Wire.begin();
    Serial.begin(115200);
    Serial.println("\nI2C Scanner");
}

void loop() {
    byte error, address;
    int nDevices;
    Serial.println("Scanning...");
    nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        } else if (error == 4) {
            Serial.print("Unknow error at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
    } else {
        Serial.println("done\n");
    }
    delay(5000);
}