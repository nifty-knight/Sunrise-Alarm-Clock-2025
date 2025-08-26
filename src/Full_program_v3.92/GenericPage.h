#ifndef GENERICPAGE_H
#define GENERICPAGE_H

#include "MenuItem.h"
#include <Arduino.h>

class GenericPage : public MenuItem {
  private:
    String line1;
    String line2;

  public:
    GenericPage();
    void display() override = 0;
};

#endif