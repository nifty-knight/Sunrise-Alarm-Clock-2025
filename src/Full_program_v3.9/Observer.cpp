#include "InputEvent.h"

// abstract Observer in Subject-Observer pattern
class Observer {
  public:
    virtual void update(InputEvent i);
};