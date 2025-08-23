#include "InputController.h"

// EFFECTS: Initializes input pins for input devices
InputController::InputController(uint8_t timeButtonPin, uint8_t selectButtonPin, uint8_t xPin, uint8_t yPin) {

}

// EFFECTS: updates each observer in observers
/*Test cases
- Test w/ one in list, multiple in list
- Check that update() is run on ALL observers, not just the first
*/
void InputController::notifyObservers(InputEvent i) {
  // TODO: stub
  // for each observer o: o.update(i);
}

// REQUIRES: observers length < numObservers
// MODIFIES: observers
// EFFECTS: appends observer to observers list 
/*Test cases
- test adding one observer, multiple observers
- check that each added is the one really in the list
- check that each added is in the list in order of adding
- Use getObserver(int index) to check
*/
void InputController::addObserver(Observer &o) {
  // TODO: stub
}

// REQUIRES: pin is a valid arduino pin number & is set to INPUT
// MODIFIES: previousPinState
// EFFECTS: Returns true if the given input turned from LOW to HIGH (edge detection)
//          & updates the given pinState value
/* Test Cases
- pressed(pin, 0) & not pressed --> false, pinState = 0
- pressed(pin, 0) & pressed --> true, pinState = 1
- pressed(pin, 1) & not pressed --> false, pinState = 0
- pressed(pin, 1) & pressed --> false, pinState = 1
- Check that pinState is correctly updated by this function
- note: LOW/HIGH = false/true = 0/1
*/
bool InputController::pressed(uint8_t pin, bool* pinState) {
  // TODO: stub
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

- Check that function is correctly updating both xPinState and yPinState
- Check function behaviour: what if it is moved in multiple directions at the same time?
  - will only return one direction; prioritizes up & down directions over right/left
*/
InputEvent InputController::joystickMoved() {
  // TODO: stub
  return InputEvent::JoystickDown;
}

// EFFECTS: Returns a pointer to observer at the given index in list
// Note: This is a helper function for testing purposes
/*Test Cases
- Test with different indices
- Check that the correct observer is being returned
*/
Observer* InputController::getObserver(int index) {
  // TODO: stub
}