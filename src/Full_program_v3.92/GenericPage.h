#ifndef GENERICPAGE_H
#define GENERICPAGE_H

#include "MenuItem.h"
#include <Arduino.h>

class GenericPage : public MenuItem {
  public:
    GenericPage(String line1, String line2) : MenuItem(line1, line2) {};
    void display() override = 0;
};

#endif