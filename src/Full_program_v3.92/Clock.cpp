#include "Clock.h"

// EFFECTS: Initializes rtc module & pins
//  TODO: add autofilled null/none parameter for time, modify constructor to sets rtc to given time if one is given
Clock::Clock(uint8_t clk, uint8_t dat, uint8_t ena) {
  // TODO: stub
}

// EFFECTS: Returns current time on rtc
// Getter - No test cases
Ds1302::DateTime Clock::getTime() {
  // TODO: stub
  Ds1302::DateTime t;
  return t;
}

// REQUIRES: t is a valid DateTime
// EFFECTS: Sets rtc to given time
/* Test cases
- setTime(8:32 am); getTime() should return 8:32 am
- setTime(3:00 pm); getTime() should return 3:00 pm
- setTime(1:00 am); getTime() should return 1:00 am
- setTime(12:59 pm); getTime() should return 12:59 pm
*/
void Clock::setTime(Ds1302::DateTime t) {
  // TODO: stub
}

// REQUIRES: hr is in [1, 12]
// EFFECTS: Returns an hour in 24-hr time given an hr in 12-hr time and the period (AM/PM)
//  TODO: note: since period can only be two states, could make bool if necessary to save space - if it would even save any
/* Test cases
- convertTo24HrTime(1, "AM") --> 0
- convertTo24HrTime(1, "PM") --> 12
- convertTo24HrTime(5, "AM") --> 4
- convertTo24HrTime(12, "PM") --> 23
*/
uint8_t convertTo24HrTime(uint8_t hr, String period) {
  // TODO: stub
  return 0;
}


