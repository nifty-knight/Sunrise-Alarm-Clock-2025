#ifndef PAGE_H
#define PAGE_H

#include "GenericPage.h"

class Page : public GenericPage {
  public:
    Page(String line1, String line2, void (*selectAction)());
    void display() override;
    void joystickResponse(Direction d) override {}; // Regular pages do nothing on joystick response
    void select() override;
};

#endif