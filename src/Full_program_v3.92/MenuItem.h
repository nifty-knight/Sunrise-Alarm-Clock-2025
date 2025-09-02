#ifndef MENUITEM.H
#define MENUITEM.H

#include "Direction.h"
#include <Arduino.h>

class MenuItem {
  protected:
    String line1;
    String line2;
  public:
    MenuItem(String line1, String line2) {
      line1 = line1;
      line2 = line2;
    }; // use super() in subclasses
    virtual void display() = 0;
    virtual void joystickResponse(Direction d) = 0;
    virtual bool hasChildren() = 0;
    virtual void select() = 0;
};

#endif