#include "MenuItems.h"

Page currentTimePage("The time is now:", "", doNothing);
Page alarmStatePage("", "", doNothing);

MenuItem* timePage[] = {&currentTimePage};
MenuItem* alarmPage[] = {&alarmStatePage};

Menu moveForwardMenu("", "", timePlusOneHr, timePage, (uint8_t)(sizeof(timePage) / sizeof(timePage[0])));
Menu moveBackwardMenu("", "", timeMinusOneHr, alarmPage, (uint8_t)(sizeof(alarmPage) / sizeof(alarmPage[0])));
// Menu mainMenu()
// RangedSelectionPage minSelect("", "", 0, 45, 15);

// EFFECTS: literally does nothing
void doNothing() { return; };

// EFFECTS: toggles alarm on/off - flips it to the reverse of what it was before
void toggleAlarm() {
  // TODO: stub
}

// EFFECTS: Changes current time by moving it forward 1 hr
// TODO: this could be combined with minusOneHr? Reduce repetition?
void timePlusOneHr() {
  // TODO: stub
}

// EFFECTS: Changes current time by moving it backward 1 hr
// TODO: this could be combined with minusOneHr? Reduce repetition?
void timeMinusOneHr() {
  // TODO: stub
}


