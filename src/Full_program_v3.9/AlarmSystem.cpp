#include "Observer.cpp" // TODO: Replace with .h
#include <Ds1302.h>

// Controls the functionality of the clock & alarm system 
class AlarmSystem : public Observer {
  private:
    Ds1302::DateTime alarmTime;
    short fadeTime = 20;
    bool alarmIsOn = false;
    unsigned long ledStartTime;
    unsigned long waitTime;

    void updateLight();
    void daylightSavingsChange(short change); // Could make this bool since only two states- +1hr or -1hr
    void setAlarmTime(Ds1302::DateTime t);
    void setAlarmState(bool s);

  public:
    void update(InputEvent i) override;
    Ds1302::DateTime getAlarmTime();
    bool getAlarmState();

};