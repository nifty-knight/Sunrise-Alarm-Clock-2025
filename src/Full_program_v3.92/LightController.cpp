#include "LightController.h"

// EFFECTS: Initializes LED output pin, resets brightness
LightController::LightController(uint8_t ledPin) : ledPin(ledPin) {
  pinMode(ledPin, OUTPUT);
  brightness = 0;
  this->setBrightness(brightness);
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

// MODIFIES: brightness
// EFFECTS: If brightness is less than 255, increase the brightness of the light by 1
// TODO: not the best here with resetting brightness and all that; might make setBrightness private
//       and add a public turnLightOff function
void LightController::increaseBrightness() {
  if (brightness < 255) {
    brightness++;
    setBrightness(brightness);
  }
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