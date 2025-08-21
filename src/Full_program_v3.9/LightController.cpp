#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <Arduino.h>

// Responsible for all functionality related to modifying the brightness of the LED light
class LightController {
  private:
  // TODO: initialize all vars that need it - may not store ledPin, but take it in via constructor
    uint8_t ledPin;
    uint8_t brightness;


  public:
    uint8_t getBrightness(); // note: uint8_t is an unsigned int iwth 8 bits, storing values from 0-255
    void setBrightness(uint8_t b);
    bool lightIsOn();
    // void turnLightOff();
};

#endif

// uint8_t LightController::LightController getBrightness() {
//   return 1;
// }