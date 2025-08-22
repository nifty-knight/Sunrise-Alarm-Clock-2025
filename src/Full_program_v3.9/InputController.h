#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

// #include "Observer.cpp" // TODO: change these includes to be .h files
#include <Arduino.h>
#include "Subject.h"
#include "DisplayController.h" // TODO: change to be Direction.h if you end up putting it in separate file

// Responsible for processing user input and informing registered clients/observers
class InputController : Subject {
  private:
    // TODO: initialize all vars that need it
    // const int delayTime; // note: should not need this line of code- use edge detection instead
    // TODO: might make button/joystick pin variables constant
    uint8_t timeButtonPin; // note: same as displayButtonPin
    uint8_t selectButtonPin;
    uint8_t xPin; // joystick x pin
    uint8_t yPin; // joystick y pin

    // void dropObserver(Observer o) override;
    void notifyObservers(InputEvent i) override;
    void addObserver(Observer o) override;
    bool pressed(uint8_t pin);
    bool joystickMoved(Direction d);

  public:
    InputController();
    Observer getObserver(int index);

};

#endif