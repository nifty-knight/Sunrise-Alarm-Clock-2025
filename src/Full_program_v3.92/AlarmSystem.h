#ifndef ALARMSYSTEM_H
#define ALARMSYSTEM_H

#include "Observer.h"
#include "Clock.h"
#include "LightController.h"
#include <Ds1302.h>

// Controls the functionality of the clock & alarm system 
class AlarmSystem : public Observer {
  private:
    Ds1302::DateTime alarmTime;
    uint8_t fadeTime; //  = 20; // TODO: do I want to set max to be 60 minutes?
    bool alarmIsOn = false;
    unsigned long ledStartTime;
    unsigned long waitTime;
    Clock clock;
    LightController lightController;

    // void updateLight();

  public:
    AlarmSystem(uint8_t fadeTime, uint8_t clk, uint8_t dat, uint8_t ena, uint8_t ledPin);
    void update(InputEvent i) override;
    Ds1302::DateTime getAlarmTime();
    bool getAlarmState();
    void setAlarmTime(Ds1302::DateTime t);
    void setAlarmState(bool s);
    void daylightSavingsChange(bool plus); // TODO: Could make this bool since only two states- +1hr or -1hr


};

#endif