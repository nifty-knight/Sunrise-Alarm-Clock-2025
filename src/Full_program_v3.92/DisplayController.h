#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include "InputEvent.h"
#include "AlarmSystem.h"
#include "Direction.h"
#include "Arrows.h"
#include "Period.h"
#include "Menu.h"
#include "Page.h"
#include <LiquidCrystal.h>

// Responsible for displaying menus and visuals to the user via the LCD
class DisplayController {
  private:
  // TODO: initialize all the variables that need initializing - note: maybe these should be passed in via constructor
    const int readTime;
    const int noActivityTime;
    const uint8_t backlightPin;
    LiquidCrystal lcd;
    unsigned long startTime;
    bool displayOn;

    uint8_t index; // for keeping track of pages with the same parent menu
    MenuItem* history[10]; // Contains page traversal history; Treat this like a stack
    // TODO: hard "magic number" limit of 10 pages in history - can I change this to be better?
    // TODO: create a stack class to use instead of array
    uint8_t historySize; // Keeps track of current number of pages in history

    Period period; // TODO: may change this to enum or a different struct to save space
    uint8_t hr;
    uint8_t min;

    void on();
    void off();
    void setBacklight(bool s);
    void printArrow(Direction d); 
    void resetActivityTimer();
    MenuItem* getCurrentPage(); 
    void displayTimePage(); 
    void displayMainMenu(); 
    void increaseIndex() { index++; };
    void decreaseIndex() { index--; };

  public:
    DisplayController(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, int readTime, int noActivityTime, uint8_t backlightPin);
    void update(InputEvent i);
    void addPage(MenuItem* page); 
    void back(); 
    uint8_t getIndex() { return index; };
    void resetIndex() { index = 0; };
    void resetMenuHierarchy();
    void setPeriod(Period p) { period = p; };
    void setHour(uint8_t h) { hr = h; };
    void setMin(uint8_t m) { min = m; };
    void setAlarmTime();
    void setCurrentTime();
};

#endif