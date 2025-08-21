#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

// #include "Observer.cpp" // TODO: change these includes to be .h files
#include "Subject.cpp"

// Responsible for processing user input and informing registered clients/observers
class InputController : Subject {
  private:
    // const int delayTime; // note: should not need this line of code- use edge detection instead
    void notifyObservers(InputEvent i) override;
    void addObserver(Observer o) override;
    // virtual void dropObserver(Observer o) = 0;

  public:
    InputController();


};

#endif