#include "DisplayController.h"
#include "Arrows.h"

// EFFECTS: initializes needed variables + output pin for LED
DisplayController::DisplayController(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, int readTime, int noActivityTime, uint8_t backlightPin, AlarmSystem alarmSystem) : 
        lcd(rs, enable, d4, d5, d6, d7), readTime(readTime), noActivityTime(noActivityTime), backlightPin(backlightPin), alarmSystem(alarmSystem) {
  // TODO: stub    
  index = 0;
  pinMode(backlightPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
  this->off();
  lcd.createChar(0, LeftArrow);
  lcd.createChar(1, RightArrow);
  lcd.createChar(2, UpArrow);
  lcd.createChar(3, DownArrow);
}

// MODIFIES: index, startTime, displayOn
// EFFECTS: Updates LCD display depending on user event
/*Test cases - NOTE: may not fully use unit tests for this function
- None: checks if noActivityTime amount of time has passed since startTime - if so, turn off LCD; else, do nothing
- TimeButtonPressed: display current time, which should turn off automatically after 5 secs
- SelectButtonPressed: 
- 
*/
void DisplayController::update(InputEvent i) {
  // TODO: stub
  alarmSystem.update(i);
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

//
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
