#include "Observer.cpp" // TODO: Replace with .h
#include <LiquidCrystal.h>

// Represents arrow directions; TODO: may put in separate file if multiple classes need access
enum class Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

// Responsible for displaying menus and visuals to the user via the LCD
class DisplayController : public Observer {
  private:
  // TODO: initialize all the variables that need initializing
    const int readTime;
    const int noActivityTime;
    const uint8_t backlightPin;
    LiquidCrystal lcd;
    uint8_t index;
    unsigned long startTime;
    bool displayOn;

    void on();
    void off();
    void setBacklight(bool s);
    printArrow(Direction d);

    // void select(); // Might use in implementation - don't have it all figured out yet
    // void escape();

  public:
    void update(InputEvent i) override;
};