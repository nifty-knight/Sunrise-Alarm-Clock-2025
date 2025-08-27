#include "LightController.h"

// EFFECTS: Initializes LED output pin, resets brightness
LightController::LightController(uint8_t ledPin) : ledPin(ledPin) {
  pinMode(ledPin, OUTPUT);
}

// EFFECTS: returns current light brightness
// Getter - no test cases
uint8_t LightController::getBrightness() {
  return brightness;
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
  brightness = b;
  analogWrite(ledPin, brightness);
}

// EFFECTS: returns true if brightness is not equal to zero
/*Test cases
- brightness = 0; lightIsOn() --> false
- brightness = 1; lightIsOn() --> true
- brightness = 255; lightIsOn() --> true
*/
bool LightController::lightIsOn() {
  return brightness != 0;
}