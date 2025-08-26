#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"

class Menu : public MenuItem {
  private:
    MenuItem* pages[5]; // note that this is a "magic number" hard limit on the max number of pages in a menu
    // TODO: how can I replace this magic number? Look up any alternative solutions

  public:
    Menu(String line1, String line2, MenuItem* pages);
    void display() override;
    void displayChild(int index);
    void addChild(MenuItem* child);

};

#endif