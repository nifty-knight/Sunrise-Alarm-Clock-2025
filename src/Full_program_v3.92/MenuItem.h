#ifndef MENUITEM.H
#define MENUITEM.H

#include "Direction.h"
#include <Arduino.h>

class MenuItem {
  protected:
    String line1;
    String line2;
    void (*action)();
  public:
    MenuItem(String line1, String line2, void (*selectAction)()) {
      line1 = line1;
      line2 = line2;
      action = selectAction;
    };
    virtual void display() = 0;
    virtual void joystickResponse(Direction d) = 0;
    virtual bool hasChildren() = 0;
    virtual void select() = 0;
};

#endif