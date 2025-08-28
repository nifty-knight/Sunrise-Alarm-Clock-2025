#ifndef ALARMSYSTEM_H
#define ALARMSYSTEM_H

#include "InputEvent.h"
#include "Clock.h"
#include "LightController.h"
#include <Ds1302.h>

// Controls the functionality of the clock & alarm system 
class AlarmSystem {
  private:
    Ds1302::DateTime alarmTime;
    uint8_t fadeTime; //  = 20; // TODO: do I want to set max to be 60 minutes?
    bool alarmIsOn;
    unsigned long ledStartTime;
    unsigned long waitTime;
    Clock clock;
    LightController lightController;
    bool nowIsTime(Ds1302::DateTime t);
    Ds1302::DateTime getFadeTime(Ds1302::DateTime alarmTime);

  public:
    AlarmSystem(uint8_t fadeTime, uint8_t clk, uint8_t dat, uint8_t ena, uint8_t ledPin);
    void update(InputEvent i);
    Ds1302::DateTime getAlarmTime();
    bool getAlarmState();
    void setAlarmTime(Ds1302::DateTime t);
    void setAlarmState(bool s);
    void daylightSavingsChange(bool plus); // TODO: Could make this bool since only two states- +1hr or -1hr


};

#endif