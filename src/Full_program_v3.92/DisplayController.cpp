#include "DisplayController.h"

// EFFECTS: initializes needed variables + output pin for LED
DisplayController::DisplayController(int readTime, int noActivityTime, uint8_t backlightPin) : readTime(readTime), noActivityTime(noActivityTime), backlightPin(backlightPin) {
    // TODO: stub    
}

// MODIFIES: index, startTime, 
// EFFECTS: Updates LCD display depending on user event
/*Test cases - NOTE: may not fully use unit tests for this function
- None: checks if noActivityTime amount of time has passed since startTime - if so, turn off LCD; else, do nothing
- TimeButtonPressed: display current time, which should turn off automatically after 5 secs
- SelectButtonPressed: 
- 
*/
void DisplayController::update(InputEvent i) {
  // TODO: stub
}

// MODIFIES: displayOn
// EFFECTS: Turns on the lcd backlight and display
/*Test cases - must be hardware tested
- when it is called, display and backlight both turn on
*/
void DisplayController::on() {
  // TODO: stub
}

// MODIFIES: displayOn
// EFFECTS: Turns off the lcd backlight and display
/*Test cases - must be hardware tested
- when it is called, display and backlight both turn off
*/
void DisplayController::off() {
  // TODO: stub
}

// EFFECTS: sets the backlight on or off based on bool given (true = on, false = off)
/*Test cases - must be hardware tested
- setBacklight(true) --> backlight on
- setBacklight(false) --> backlight off
*/
void DisplayController::setBacklight(bool s) {
  // TODO: stub
}

// EFFECTS: prints an arrow on the lcd display at the current cursor location
/*Test cases - must be hardware tested
- Check that each direction arrow prints out correctly
*/
void DisplayController::printArrow(Direction d) {
  // TODO: stub
}