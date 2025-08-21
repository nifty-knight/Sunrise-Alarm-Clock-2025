#include <Arduino.h>
#include <Ds1302.h>

// Responsible for all functions dealing with the time tracked by the RTC
class Clock {
  private:
    const uint8_t PIN_CLK = 7;
    const uint8_t PIN_DAT = 6;
    const uint8_t PIN_ENA = 5;  // RST on the module itself

  public:
    Ds1302::DateTime getTime();
    void setTime(Ds1302::DateTime t);
};

uint8_t convertTo24HrTime(uint8_t hr, String s); // TODO; might make this return char + take in char hour if it would save space
