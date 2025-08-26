#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"

byte UpArrow[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b00000
};

byte DownArrow[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};

byte RightArrow[8] = {
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b01110,
  0b01100,
  0b01000,
  0b00000
};

byte LeftArrow[8] = {
  0b00000,
  0b00010,
  0b00110,
  0b01110,
  0b01110,
  0b00110,
  0b00010,
  0b00000
};

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