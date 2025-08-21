// #include "Observer.h" // TODO: uncomment, replace .cpp
#include "Observer.cpp"

// abstract Subject in Subject-Observer pattern
class Subject {
  public:
    virtual void addObserver(Observer o) = 0;
    // virtual void dropObserver(Observer o) = 0;
    virtual void notifyObservers(InputEvent i) = 0;
};