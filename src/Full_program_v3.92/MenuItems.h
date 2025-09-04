#ifndef MENUS_H
#define MENUS_H

#include "Menu.h"
#include "Page.h"
#include "RangedSelectionPage.h"

extern Page currentTimePage;
extern Page alarmStatePage;
extern Menu mainMenu; // unique in that it does not have its own display page
extern Menu setAlarmTimeMenu;
extern Menu setCurrentTimeMenu;
extern Menu toggleAlarmMenu;
extern Menu moveForwardMenu; // moves current time forward 1 hr
extern Menu moveBackwardMenu; // moves current time backward 1 hr

// note: these might change to become a different class (RangedSelectionMenu??), we'll see
extern Menu setPeriodMenu;
extern Menu setHrMenu;
extern Menu setMinMenu;

extern void doNothing();
extern void toggleAlarm();
extern void timePlusOneHr();
extern void timeMinusOneHr();

// These functions may actually need to take a parameter; need to think about how I'm going to do this
// extern void setPeriod();
// extern void setHr();
// extern void setMin();


// Menu mainMenu("", "", ); // last argument is a pointer to an array of menuitems declared in this file

#endif