#include <Adafruit_SH1106.h>
#include <Arduino.h>
#include <RCSwitch.h>
#include <Wire.h>

#define pinReceiver 13
#define pinButton 4
#define pinLed 2

RCSwitch mySwitch = RCSwitch();

int code = 0;
bool ledStatus = false;

#define i2C_ADDRESS 0x3C
Adafruit_SH1106 display;

void resetScreen() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 10);
    display.println("Alarm system");
    display.println("activated");
    display.display();
}

void alarmScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.println("Motion!");
    display.display();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting receiver...");

    pinMode(pinButton, INPUT_PULLUP);
    pinMode(pinLed, OUTPUT);

    mySwitch.enableReceive(pinReceiver); 

    display.begin(SH1106_SWITCHCAPVCC, i2C_ADDRESS);
    display.setTextColor(WHITE);
    resetScreen();

    display.display();

    Serial.println("Setup complete");
}

void loop() {
    digitalWrite(pinLed, ledStatus);
    bool digitalReadButton = !digitalRead(pinButton);

    if (digitalReadButton == HIGH) {
        resetScreen();
    }

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
            alarmScreen();
        }

        mySwitch.resetAvailable();
    }
}