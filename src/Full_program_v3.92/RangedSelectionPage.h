#ifndef RANGED_H
#define RANGED_H

#include "GenericPage.h"

class RangedSelectionPage : public GenericPage {
  private:
    // TODO: change from ints to uint8_t if trying to save space
    const int minn;
    const int maxn;
    const int step;
    int current;

  public:
    // TODO: change from ints to uint8_t if trying to save space
    RangedSelectionPage(String line1, String line2, void (*selectAction)(), int minn, int maxn, int step);
    void display() override;
    void joystickResponse(Direction d) override;
    void select() override; // TODO: add function in cpp
    void increase();
    void decrease();

};

#endif