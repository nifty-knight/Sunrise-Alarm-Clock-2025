#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include "Observer.h" // TODO: Replace with .h
#include <LiquidCrystal.h>

// Represents arrow directions; TODO: may put in separate file if multiple classes need access
// TODO: accessed by DisplayController.h
// #include "Direction.h" // TODO: uncomment if you end up putting Direction in separate file
enum class Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  NONE
};

// Responsible for displaying menus and visuals to the user via the LCD
class DisplayController : public Observer {
  private:
  // TODO: initialize all the variables that need initializing - note: maybe these should be passed in via constructor
    const int readTime;
    const int noActivityTime;
    const uint8_t backlightPin;
    // int readTime;
    // int noActivityTime;
    // uint8_t backlightPin;
    // LiquidCrystal lcd(13, 11, 10, 8, 3, 2); // TODO: You cannot instantiate an object in a class definition; if you really need this var, use a member initialization list
    uint8_t index;
    unsigned long startTime;
    bool displayOn;

    void on();
    void off();
    void setBacklight(bool s);
    void printArrow(Direction d); // TODO: note that it requires direction != NONE

    // void select(); // Might use in implementation - don't have it all figured out yet
    // void escape();

  public:
    DisplayController(int readTime, int noActivityTime, uint8_t backlightPin);
    void update(InputEvent i) override;
};

#endif