#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h" // TODO: uncomment, replace .cpp
// #include "Observer.cpp"

// abstract Subject in Subject-Observer pattern
// TODO: I just realized, if this is an interface maybe I should just make a Subject.h file, no .cpp equivalent
class Subject {
  public:
    virtual void addObserver(Observer o) = 0;
    // virtual void dropObserver(Observer o) = 0;
    virtual void notifyObservers(InputEvent i) = 0;
};

#endif