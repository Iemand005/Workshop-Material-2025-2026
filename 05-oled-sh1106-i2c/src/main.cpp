#include <Arduino.h>

/*
OLED Pin	ESP32 Pin
VCC	      3.3V
GND	      GND
SDA	      GPIO 21
SCL	      GPIO 22
*/

// include libraries
#include <Adafruit_SH1106.h>
#include <Wire.h>

#define i2C_ADDRESS 0x3C
Adafruit_SH1106 display;

void setup() {
  display.begin(SH1106_SWITCHCAPVCC, i2C_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Look here, text!");
  display.display();
}

void loop() {
}