#include "DisplayController.h"


// EFFECTS: initializes needed variables + output pin for LED
DisplayController::DisplayController(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, int readTime, int noActivityTime, uint8_t backlightPin) : 
        lcd(rs, enable, d4, d5, d6, d7), readTime(readTime), noActivityTime(noActivityTime), backlightPin(backlightPin) {
  index = 0;
  historySize = 0;
  pinMode(backlightPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  this->off();
  lcd.createChar(0, LeftArrow);
  lcd.createChar(1, RightArrow);
  lcd.createChar(2, UpArrow);
  lcd.createChar(3, DownArrow);
}

// TODO: lots of repetition of resetActivityTimer()
// TODO: lots of repetition of if (displayOn); could be refactored to reduce repetition
// TODO: lots of repetition & coupling between InputEvent and Direction; can I combine them somehow?
// MODIFIES: index, startTime, displayOn
// EFFECTS: Updates LCD display depending on user event
/*Test cases - NOTE: may not fully use unit tests for this function
- None: checks if noActivityTime amount of time has passed since startTime - if so, turn off LCD; else, do nothing
- TimeButtonPressed: display current time, which should turn off automatically after 5 secs
- SelectButtonPressed: 
- 
*/
void DisplayController::update(InputEvent i) {
  switch(i) {
    case InputEvent::SelectButtonPressed:
      if (!displayOn) {
        on();
        displayMainMenu();
      } else {
        // if page has children: show child
        // else: reset menu hierarchy
        // TODO: 
        //       - for pages, select() resets the menu hierarchy
        //       - for menus, select() calls displayChild() and also addPage() with the displayed child
        getCurrentPage()->select();
      }
      break;
    case InputEvent::TimeButtonPressed:
      displayTimePage();
      resetMenuHierarchy();
      resetActivityTimer();
      break;
    case InputEvent::JoystickDown:
      if (displayOn) {
        getCurrentPage()->joystickResponse(Direction::DOWN);
        resetActivityTimer();
      }
      break;
    case InputEvent::JoystickUp:
      if (displayOn) {
        getCurrentPage()->joystickResponse(Direction::UP);
        resetActivityTimer();
      }
      break;
    case InputEvent::JoystickLeft:
      if (displayOn) {
        getCurrentPage()->joystickResponse(Direction::LEFT);
        resetActivityTimer();
      }
      break;
    case InputEvent::JoystickRight:
      if (displayOn) {
        getCurrentPage()->joystickResponse(Direction::RIGHT);
        resetActivityTimer();
      }
      break;
    default: // None
      if (displayOn && ((millis() - startTime) > noActivityTime)) {
        off();
      }
      break;
  }
}

// MODIFIES: displayOn
// EFFECTS: Turns on the lcd backlight and display
/*Test cases - must be hardware tested
- when it is called, display and backlight both turn on
*/
void DisplayController::on() {
  lcd.display();
  setBacklight(true);
  displayOn = true;
  this->resetActivityTimer();
}

// MODIFIES: displayOn
// EFFECTS: Turns off the lcd backlight and display
/*Test cases - must be hardware tested
- when it is called, display and backlight both turn off
*/
void DisplayController::off() {
  lcd.noDisplay();
  setBacklight(false);
  displayOn = false;
}

// EFFECTS: sets the backlight on or off based on bool given (true = on, false = off)
/*Test cases - must be hardware tested
- setBacklight(true) --> backlight on
- setBacklight(false) --> backlight off
*/
void DisplayController::setBacklight(bool s) {
  digitalWrite(backlightPin, s);
}

// EFFECTS: prints an arrow on the lcd display at the current cursor location
//          if the direction given is NONE, this function does nothing
/*Test cases - must be hardware tested
- Check that each direction arrow prints out correctly
*/
void DisplayController::printArrow(Direction d) {
  switch(d) {
    case Direction::DOWN:
      lcd.write(byte(3));
      break;
    case Direction::LEFT:
      lcd.write(byte(0));
      break;
    case Direction::RIGHT:
      lcd.write(byte(1));
      break;
    case Direction::UP:
      lcd.write(byte(2));
      break;
    default: // do nothing
      break;
  }
}

// EFFECTS: Sets startTime to the current amount returned by millis()
void DisplayController::resetActivityTimer() {
  startTime = millis();
}

// TODO: delete later; only for compiling purposes
void stub() {};
// REQUIRES: history is not empty; the screen must be on and displaying when this is called
// EFFECTS: Returns the current page displayed to the user 
MenuItem* DisplayController::getCurrentPage() {
  // TODO: stub
  Page item("", "", stub);
  return &item;
}

// MODIFIES: index, history, historySize // TODO: might not even need to modify history - historySize ensures it will get rewritten over
// EFFECTS: resets index & clears history, displays first page of main menu
void DisplayController::resetMenuHierarchy() {
  // TODO: stub
}

// REQUIRES: history is not full; has room to store another page
// MODIFIES: history, historySize
// EFFECTS: Appends a page to the end of history array and updates historySize accordingly
//          Note that this function does not display the given page; it is called by the selected page
void DisplayController::addPage(MenuItem* page) {
  // TODO: stub
}

// REQUIRES: history has at least 2 pages in it; cannot go back to an empty page
// MODIFIES: history, historySize
// EFFECTS: Removes the current page from history, updates historySize accordingly, displays the previous page
//          or the first page of the previous menu
void DisplayController::back() {
  // TODO: stub
}

// MODIFIES: index, history, historySize // TODO: maybe not history if I use circular buffer-style storage
// EFFECTS: Displays the page showing current time to the user
void DisplayController::displayTimePage() {
  // TODO: stub
}

// MODIFIES: index, history, historySize
// EFFECTS: Displays first page of the main menu
void DisplayController::displayMainMenu() {
  // TODO: stub
}

// EFFECTS: calls AlarmSystem's setAlarmTime with stored period, hr, min
void DisplayController::setAlarmTime() {
  // TODO: stub
}

// EFFECTS: calls AlarmSystem's setCurrentTime with stored period, hr, min
void DisplayController::setCurrentTime() {
  // TODO: stub
}