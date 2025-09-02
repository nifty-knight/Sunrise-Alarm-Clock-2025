#include "Page.h"

// EFFECTS: Initializes page with given message
Page::Page(String line1, String line2, void (*selectAction)()) : GenericPage(line1, line2, *selectAction) {
  // TODO: stub
}

// EFFECTS: Displays page message on LCD
void Page::display() {
  // TODO: stub
}

// EFFECTS: Runs selectAction(), returns user display to the main menu
void Page::select() {
  // TODO: stub
}
