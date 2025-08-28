#include "Clock.h"

const String AM = "AM";
const String PM = "PM";

// EFFECTS: Initializes rtc module & pins
//  TODO: add autofilled null/none parameter for time, modify constructor to sets rtc to given time if one is given
// Tested in hardware
Clock::Clock(uint8_t clk, uint8_t dat, uint8_t ena) : rtc(clk, dat, ena) {
  rtc.init();

  if (rtc.isHalted()) {
    Ds1302::DateTime currentTime = {
      .year = 2025,
      .month = Ds1302::MONTH_AUG,
      .day = 26,
      .hour = 18,
      .minute = 45,
      .second = 0,
      .dow = Ds1302::DOW_TUE
    };

    rtc.setDateTime(&currentTime);
  }
}

// EFFECTS: Returns current time on rtc
// Getter - No test cases
Ds1302::DateTime Clock::getTime() {
  Ds1302::DateTime t;
  rtc.getDateTime(&t);
  return t;
}

// REQUIRES: t is a valid DateTime
// EFFECTS: Sets rtc to given time
/* Test cases - must be tested in hardware since time is not stored in arduino
- setTime(8:32 am); getTime() should return 8:32 am
- setTime(3:00 pm); getTime() should return 3:00 pm
- setTime(1:00 am); getTime() should return 1:00 am
- setTime(12:59 pm); getTime() should return 12:59 pm
*/
void Clock::setTime(Ds1302::DateTime t) {
    rtc.setDateTime(&t);
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
  if (period == Clock::AM) {
    return hr - 1;
  } else if (period == Clock::PM) {
    return hr + 11;
  }

  // Signifies error - this line should never run
  return -1;
}


