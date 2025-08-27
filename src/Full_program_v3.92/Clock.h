#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <Ds1302.h>

// TODO: might delete/replace if necessary for saving space
String AM = "AM";
String PM = "PM";

// Responsible for all functions dealing with the time tracked by the RTC
class Clock {
  private:
    // const uint8_t PIN_CLK = 7;
    // const uint8_t PIN_DAT = 6;
    // const uint8_t PIN_ENA = 5;  // RST on the module itself
    Ds1302 rtc;
  public:
    Clock(uint8_t clk, uint8_t dat, uint8_t ena);
    Ds1302::DateTime getTime();
    void setTime(Ds1302::DateTime t);
};

uint8_t convertTo24HrTime(uint8_t hr, String period); // TODO; might make it return like a 4-byte struct if it would save space - then again, that might be a large deep rabbit hole

#endif