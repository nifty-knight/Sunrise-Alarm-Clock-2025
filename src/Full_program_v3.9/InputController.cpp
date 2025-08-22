#include "InputController.h"

// EFFECTS: Initializes input pins for input devices
InputController::InputController() {

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
*/
void InputController::addObserver(Observer &o) {
  // TODO: stub
}

// EFFECTS: Returns true if the given input 
bool InputController::pressed(uint8_t pin) {
  // TODO: stub
  return false;
}

// EFFECTS: Returns a pointer to observer at the given index in list
// Note: This is a helper function for testing purposes
Observer* InputController::getObserver(int index) {
  // TODO: stub
}