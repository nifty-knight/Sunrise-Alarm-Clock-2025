#ifndef PERIODMENU_H
#define PERIODMENU_H

#include "Menu.h"
#include "Period.h"
// #include "Direction.h"

class PeriodSelectionMenu : public Menu {
  private:
    // MenuItem* pages[5]; // note that this is a "magic number" hard limit on the max number of pages in a menu
    // TODO: how can I replace this magic number? Look up any alternative solutions

    // Accessible through superclass
    // MenuItem** pages; // pointer to an array; pages = children = subs
    // uint8_t numPages; // length of pages array; using uint8_t limits number to 255 max pages

    void (*action)(Period p);

  public:
    PeriodSelectionMenu(String line1, String line2, void (*selectAction)(Period p), MenuItem** pages, uint8_t numPages);
    void joystickResponse(Direction d) override;
    void select() override; // TODO: add function in cpp
    // Below should all be accessible from superclass
    // void display() override;
    // void displayChild(int index);
    // void addChild(MenuItem* child);
    // uint8_t getNumChildren() { return numPages; };
    // bool hasChildren() override { return numPages != 0; }; // TODO: this may just return true; a defining feature of a menu (as opposed to a page) is that it HAS children or sub-menus/pages
};

#endif