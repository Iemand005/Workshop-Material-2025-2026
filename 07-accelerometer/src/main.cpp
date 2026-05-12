#include <Arduino.h>
#include <Wire.h>

/*
MPU-9265  Arduino Nano
VCC       3.3V
GND       GND
SDA       A4
SCL       A5
*/

#define pinLed 4

// MPU-9265 I2C address
#define MPU_ADDR 0x68

// MPU-9265 registers
#define REG_PWR_MGMT_1 0x6B
#define REG_ACCEL_CONFIG 0x1C
#define REG_ACCEL_XOUT_H 0x3B
#define REG_WHO_AM_I 0x75

// Threshold for movement detection (tune as needed)
const int threshold = 1;

// Three-axis baseline values for resting position
int16_t baseX, baseY, baseZ;

struct Vec3I {
    int16_t x, y, z;
};

Vec3I lastPos{0,0,0};

/**
 * @brief Write a byte to a specific register on the MPU-9265
 * 
 * @param reg 
 * @param value 
 */
void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

/**
 * @brief Read accelerometer data from the MPU-9265 and return it as three 16-bit integers
 * 
 * @param x 
 * @param y 
 * @param z 
 */
Vec3I readAccel() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(REG_ACCEL_XOUT_H);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 6);

    // MPU-9265 data is big-endian (high byte first)
    Vec3I pos;
    pos.x = (Wire.read() << 8) | Wire.read();
    pos.y = (Wire.read() << 8) | Wire.read();
    pos.z = (Wire.read() << 8) | Wire.read();
    return pos;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Starting MPU-9265 accelerometer example...");

    pinMode(pinLed, OUTPUT);
    Wire.begin();

    // Wake up MPU-9265 (clear sleep bit)
    writeRegister(REG_PWR_MGMT_1, 0x00);
    // Set accelerometer range to +/-2g
    writeRegister(REG_ACCEL_CONFIG, 0x00);

    delay(100);

    // Read baseline (resting position)
    auto pos = readAccel();
    baseX = pos.x, baseY= pos.y, baseZ= pos.z;
    Serial.print("Baseline - X: "); Serial.print(baseX);
    Serial.print(" Y: "); Serial.print(baseY);
    Serial.println(" Z: "); Serial.println(baseZ);

    Serial.println("Setup complete");
}

void loop() {
    auto currentPos = readAccel();
    
    // Calculate difference from baseline
    int16_t dx = currentPos.x - lastPos.x;
    int16_t dy = currentPos.y - lastPos.y;
    int16_t dz = currentPos.z - lastPos.z;

    
    // Use sum of absolute differences as movement magnitude
    int magnitude = abs(dx) + abs(dy) + abs(dz);

    magnitude -= 1000;
    magnitude /= 200;

    if (magnitude > 255) magnitude = 255;
    if (magnitude < 0) magnitude = 0;
    
    if (magnitude > threshold) {
        // digitalWrite(pinLed, HIGH);
        analogWrite(pinLed, 10);
        Serial.print("Movement detected! Magnitude: ");
        Serial.println(magnitude);
    } else {
        digitalWrite(pinLed, LOW);
    }

    lastPos = currentPos;
    
    // don't read too fast to avoid overwhelming the serial output and to give the LED time to respond
    delay(50); // Adjust delay as needed for responsiveness
}