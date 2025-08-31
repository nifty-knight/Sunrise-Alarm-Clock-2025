#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include "InputEvent.h"
#include "AlarmSystem.h"
#include "Direction.h"
#include <LiquidCrystal.h>

// Responsible for displaying menus and visuals to the user via the LCD
class DisplayController {
  private:
  // TODO: initialize all the variables that need initializing - note: maybe these should be passed in via constructor
    const int readTime;
    const int noActivityTime;
    const uint8_t backlightPin;
    LiquidCrystal lcd;
    uint8_t index;
    unsigned long startTime;
    bool displayOn;

    AlarmSystem alarmSystem;

    void on();
    void off();
    void setBacklight(bool s);
    void printArrow(Direction d); // TODO: note that it requires direction != NONE
    void resetActivityTimer();
    // void select(); // Might use in implementation - don't have it all figured out yet
    // void escape();

  public:
    DisplayController(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, int readTime, int noActivityTime, uint8_t backlightPin, AlarmSystem alarmSystem);
    void update(InputEvent i);
};

#endif