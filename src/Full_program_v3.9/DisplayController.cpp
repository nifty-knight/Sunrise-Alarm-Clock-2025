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

}
