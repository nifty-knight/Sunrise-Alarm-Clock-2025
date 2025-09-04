#include "Menu.h"
// #include "Direction.h"

// REQUIRES: pages contains equal to or less than the max number of pages allowed in Menu.h
// EFFECTS: Initializes menu, adds pages to menu
Menu::Menu(String line1, String line2, void (*selectAction)(), MenuItem** pages, uint8_t numPages) : MenuItem(line1, line2, *selectAction), pages(pages), numPages(numPages) {
  
  // TODO: stub
}

// EFFECTS: shows message for this menu on the LCD
// Tested in hardware
void Menu::display() {
  // TODO: stub
}

void Menu::joystickResponse(Direction d) {

}

// EFFECTS: runs selectAction(), displays first child, resets index
void Menu::select() {
  // TODO: stub
}

// REQUIRES: index is valid and within range of pages
// EFFECTS: Shows message for child menuItem at given index
// Tested in hardware - ensure that the page at the correct index is being displayed
void Menu::displayChild(int index) {
  // TODO: stub
}

// REQUIRES: There is room in pages to add another one
// EFFECTS: Adds the given child to pages
/*Test cases - low priority
- Check that the child is being added - would need a getter for this
- define behaviour for if pages is full
*/
void Menu::addChild(MenuItem* child) {
  // TODO: stub
}