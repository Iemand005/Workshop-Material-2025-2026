#include <Arduino.h>

// this pin is internally connected to the on-board LED on the ESP32, so we can use it to test our code
#define LED_BUILTIN 2

/**
 * @brief runs once at startup
 * 
 */
void setup() {
  // configure the pin for the built-in LED as an output pin
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * @brief runs repeatedly as long as the board is powered
 * 
 */
void loop() {
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  // wait for a second
  delay(1000);
}