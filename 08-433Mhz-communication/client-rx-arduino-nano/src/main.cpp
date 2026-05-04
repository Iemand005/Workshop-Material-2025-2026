#include <Arduino.h>
#include <RCSwitch.h>

// Receiver on Arduino pin 2

#define pinLed 4 // LED on pin 4 to indicate received codes

RCSwitch mySwitch = RCSwitch();

int code = 0;
bool ledStatus = false;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting receiver...");

    pinMode(pinLed, OUTPUT);

    mySwitch.enableReceive(0);  // Receiver on interrupt 0 (= pin 2)

    Serial.println("Setup complete");
}

void loop() {
    digitalWrite(pinLed, ledStatus);

    if (mySwitch.available()) {
        unsigned long receivedCode = mySwitch.getReceivedValue();

        if (receivedCode == 0) {
            Serial.println("Unknown encoding");
        } else {
            ledStatus = !ledStatus;  // Toggle LED status on each received code
            Serial.print("Received code: ");
            Serial.print(receivedCode);
            Serial.print(" / bitlength: ");
            Serial.print(mySwitch.getReceivedBitlength());
            Serial.print(" / delay: ");
            Serial.print(mySwitch.getReceivedDelay());
            Serial.print(" / protocol: ");
            Serial.println(mySwitch.getReceivedProtocol());
        }

        mySwitch.resetAvailable();
    }
}