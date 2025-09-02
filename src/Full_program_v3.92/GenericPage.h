#ifndef GENERICPAGE_H
#define GENERICPAGE_H

#include "MenuItem.h"
#include <Arduino.h>

class GenericPage : public MenuItem {
  public:
    GenericPage(String line1, String line2) : MenuItem(line1, line2) {};
    virtual void display() override = 0;
    virtual void joystickResponse(Direction d) override = 0;
    virtual void select() override = 0;
    bool hasChildren() override { return false; } ;
};

#endif