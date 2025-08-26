#ifndef MENUITEM.H
#define MENUITEM.H

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
};

#endif