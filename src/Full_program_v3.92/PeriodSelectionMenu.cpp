#include "PeriodSelectionMenu.h"

// EFFECTS: Initialize menu
PeriodSelectionMenu::PeriodSelectionMenu(String line1, String line2, void (*selectAction)(Period p), MenuItem** pages, uint8_t numPages) : 
  Menu(line1, line2, nullptr, pages, numPages), action(selectAction) {
    // TODO: stub
}

// EFFECTS: display appropriate period according to joystick movements
void PeriodSelectionMenu::joystickResponse(Direction d) {
  // TODO: stub
}

// EFFECTS: Send result back to DisplayController and display child
void PeriodSelectionMenu::select() {
  // TODO: stub
}