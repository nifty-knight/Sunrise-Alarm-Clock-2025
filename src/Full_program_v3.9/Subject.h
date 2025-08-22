#ifndef SUBJECT_H
#define SUBJECT_H

#include <Arduino.h>
#include "Observer.h" // TODO: uncomment, replace .cpp
// #include "Observer.cpp"

// abstract Subject in Subject-Observer pattern
// TODO: I just realized, if this is an interface maybe I should just make a Subject.h file, no .cpp equivalent
class Subject {
  public:
    // TODO: See if there's a better way to create the observer array than making it fixed-length
    static const uint8_t numObservers = 2; // TODO: This limits the max number of observers, must change if need more observers 
    virtual void addObserver(Observer &o) = 0;
    // virtual void dropObserver(Observer o) = 0;
    virtual void notifyObservers(InputEvent i) = 0;

  protected:
      Observer* observers[numObservers];
};

#endif