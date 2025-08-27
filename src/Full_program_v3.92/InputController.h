#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

// #include "Observer.cpp" // TODO: change these includes to be .h files
#include "InputEvent.h"
#include <Arduino.h>
// #include "Subject.h"

// Responsible for processing user input and informing registered clients/observers
class InputController {
  private:
    // TODO: initialize all vars that need it
    // const int delayTime; // note: should not need this line of code- use edge detection instead
    // TODO: probably should put the variables in a list for easier access when writing update()
    const uint8_t timeButtonPin; // note: same as displayButtonPin
    const uint8_t selectButtonPin;
    const uint8_t xPin; // joystick x pin
    const uint8_t yPin; // joystick y pin
    bool timePinState;
    bool selectPinState;
    InputEvent joystickState;

    bool pressed(uint8_t pin, bool& pinState);
    InputEvent joystickMoved();

  public:
    InputController(uint8_t timeButtonPin, uint8_t selectButtonPin, uint8_t xPin, uint8_t yPin);
    InputEvent update();
};

#endif