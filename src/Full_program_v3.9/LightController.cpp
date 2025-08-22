// #ifndef LIGHTCONTROLLER_H
// #define LIGHTCONTROLLER_H

// #include <Arduino.h>

// // Responsible for all functionality related to modifying the brightness of the LED light
// class LightController {
//   private:
//   // TODO: initialize all vars that need it - may not store ledPin, but take it in via constructor
//     uint8_t ledPin;
//     uint8_t brightness;


//   public:
//     uint8_t getBrightness(); // note: uint8_t is an unsigned int iwth 8 bits, storing values from 0-255
//     void setBrightness(uint8_t b);
//     bool lightIsOn();
//     // void turnLightOff();
// };

// #endif

#include "LightController.h"

// EFFECTS: Initializes LED output pin, resets brightness
LightController::LightController() {
  // TODO: stub
}

// EFFECTS: returns current light brightness
// Getter - no test cases
uint8_t LightController::getBrightness() {
  // TODO: stub
  return 0;
}

// REQUIRES: b in [0, 255]
// MODIFIES: brightness
// EFFECTS: Sets brightness to given value
/*Test cases
- setBrightness(0) --> getBrightness() returns 0
- setBrightness(14) twice --> getBrightness() returns 14
- setBrightness(255) --> getBrightness() returns 255
*/
void LightController::setBrightness(uint8_t b) {
  // TODO: stub
}

// EFFECTS: returns true if brightness is not equal to zero
/*Test cases
- brightness = 0; lightIsOn() --> false
- brightness = 1; lightIsOn() --> true
- brightness = 255; lightIsOn() --> true
*/
bool LightController::lightIsOn() {
  // TODO: stub
  return false;
}