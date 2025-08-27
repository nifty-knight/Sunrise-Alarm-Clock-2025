#include "InputController.h"

// EFFECTS: Initializes input pins for input devices
InputController::InputController(uint8_t timeButtonPin, uint8_t selectButtonPin, uint8_t xPin, uint8_t yPin) : timeButtonPin(timeButtonPin), selectButtonPin(selectButtonPin), xPin(xPin), yPin(yPin) {
  timePinState = false;
  selectPinState = false;
  joystickState = InputEvent::None;
}

// EFFECTS: Returns the current input event
/*Test cases
- Test all events
- note: must also be tested with hardware for full testing
*/
InputEvent InputController::update() {
  if (pressed(timeButtonPin, timePinState)) { // TODO: this is bad, can I group pin and pinState together into a single data structure?
    return InputEvent::TimeButtonPressed;
  } else if (pressed(selectButtonPin, selectPinState)) {
    return InputEvent::SelectButtonPressed;
  } else {
    return joystickMoved();
  }
}

// REQUIRES: pin is a valid arduino pin number & is set to INPUT
// MODIFIES: previousPinState
// EFFECTS: Returns true if the given input turned from LOW to HIGH (edge detection)
//          & updates the given pinState value
/* Test Cases (for non-inverted buttons)
- pressed(pin, 0) & not pressed --> false, pinState = 0
- pressed(pin, 0) & pressed --> true, pinState = 1
- pressed(pin, 1) & not pressed --> false, pinState = 0
- pressed(pin, 1) & pressed --> false, pinState = 1
- Check that pinState is correctly updated by this function
- note: LOW/HIGH = false/true = 0/1
*/
// FOR NON-INVERTED BUTTONS
// bool InputController::pressed(uint8_t pin, bool& pinState) {
//   bool newState = digitalRead(pin);
//   if (!pinState && newState) {
//     return true;
//   }
//   pinState = newState; // does this work for updating the value outside the scope of the function?
//   return false;
// }

// FOR INVERTED BUTTONS
bool InputController::pressed(uint8_t pin, bool& pinState) {
  bool newState = digitalRead(pin);
  if (pinState && !newState) {
    return true;
  }
  pinState = newState; // does this work for updating the value outside the scope of the function?
  return false;
}

// MODIFIES: xPinState, yPinState
// EFFECTS: Checks if the joystick has moved in a particular direction using edge detection
//          & updates the corresponding pin states
/*Test Cases
- joystickState = NONE, no movement --> NONE, joystickState = NONE
- joystickState = NONE, move LEFT --> LEFT, joystickState = LEFT
- joystickState = LEFT, move LEFT --> NONE, joystickState = LEFT
- joystickState = NONE, move LEFT & UP --> UP, joystickState = UP,
- joystickState = RIGHT, move LEFT --> LEFT, joystickState = LEFT
- joystickState = RIGHT, move DOWN --> DOWN, joystickState = DOWN
- joystickState = UP, no movement/return to middle --> NONE, joystickState = NONE

- Check that function is correctly updating both xPinState and yPinState
- Check function behaviour: what if it is moved in multiple directions at the same time?
  - will only return one direction; prioritizes up & down directions over right/left
*/
InputEvent InputController::joystickMoved() {
  // TODO: lots of repetition in this function, how can I clean it up? Helper function?
  InputEvent newState;
  InputEvent returnState;
  
  if (analogRead(yPin) <= 25) { // up
    newState = InputEvent::JoystickUp;
    if (joystickState != InputEvent::JoystickUp) {
      returnState = InputEvent::JoystickUp;
    } else returnState = InputEvent::None;
  } else if (analogRead(yPin) >- 1000) { // down
    newState = InputEvent::JoystickDown;
    if (joystickState != InputEvent::JoystickDown) {
      returnState = InputEvent::JoystickDown;
    } else returnState = InputEvent::None;
  } else if (analogRead(xPin) <= 15) { // left
    newState = InputEvent::JoystickLeft;
    if (joystickState != InputEvent::JoystickLeft) {
      returnState = InputEvent::JoystickLeft;
    } else returnState = InputEvent::None;
  } else if (analogRead(xPin) >= 1000) { // right
    newState = InputEvent::JoystickRight;
    if (joystickState != InputEvent::JoystickRight) {
      returnState = InputEvent::JoystickRight;
    } else returnState = InputEvent::None;
  } else {
    newState = InputEvent::None;
    returnState = InputEvent::None;
  }

  joystickState = newState;
  return returnState;
}

