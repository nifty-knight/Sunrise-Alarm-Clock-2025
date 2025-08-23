// #ifndef ALARMSYSTEM_H
// #define ALARMSYSTEM_H

// #include "Observer.h"
// #include <Ds1302.h>

// // Controls the functionality of the clock & alarm system 
// class AlarmSystem : public Observer {
//   private:
//     Ds1302::DateTime alarmTime;
//     short fadeTime = 20;
//     bool alarmIsOn = false;
//     unsigned long ledStartTime;
//     unsigned long waitTime;

//     void updateLight();
//     void daylightSavingsChange(short change); // Could make this bool since only two states- +1hr or -1hr
//     void setAlarmTime(Ds1302::DateTime t);
//     void setAlarmState(bool s);

//   public:
//     void update(InputEvent i) override;
//     Ds1302::DateTime getAlarmTime();
//     bool getAlarmState();

// };

// #endif

#include "AlarmSystem.h"

// EFFECTS: initializes necessary fields & subclass objects & set initial alarmTime to 1:00am
// TODO: maybe include alarmTime as an optional parameter?
AlarmSystem::AlarmSystem(uint8_t fadeTime, uint8_t clk, uint8_t dat, uint8_t ena, uint8_t ledPin) : clock(clk, dat, ena), lightController(ledPin) {
  clock = Clock(clk, dat, ena);
  // TODO: stub
}

// EFFECTS: Updates the state of the light and clock as necessary
/*Test cases
- update(SelectButtonPressed) --> turn light off if it is on, nothing otherwise
- Ignore all other events - do the same thing in any case
- Check that light turns on at the correct time
- Check that light does not turn on if alarmIsOn is off
- Check that light gets brighter at the correct times - as time progresses
*/
void AlarmSystem::update(InputEvent i) {
  // TODO: stub
}

// // EFFECTS: updates the light according to the correct variables
// // TODO: do I even need this function? Don't think so honestly
// void AlarmSystem::updateLight() {
//   // TODO: stub
// }

// MODIFIES: 
// EFFECTS: 
void AlarmSystem::daylightSavingsChange(bool plus) {

}

// MODIFIES: alarmTime, alarmIsOn
// EFFECTS: Sets alarmTime to t and sets alarmIsOn to true
/*Test cases
- test setting it multiple times 
- check that alarmIsOn ends up true regardless of whether it started as false or true
*/
void AlarmSystem::setAlarmTime(Ds1302::DateTime t) {
  // TODO: stub
}

// MODIFIES: alarmIsOn
// EFFECTS: sets alarmIsOn to s
/*Test cases
- alarmIsOn = false, setAlarmState(true) --> alarmIsOn = true
- alarmIsOn = false, setAlarmState(false) --> alarmIsOn = false
- alarmIsOn = true, setAlarmState(true) --> alarmIsOn = true
- alarmIsOn = true, setAlarmState(false) --> alarmIsOn = false
*/
void AlarmSystem::setAlarmState(bool s) {
  // TODO: stub
}

// EFFECTS: Returns alarmTime
// Getter - no test cases
Ds1302::DateTime AlarmSystem::getAlarmTime() {
  // TODO: stub
  Ds1302::DateTime t;
  return t;
}

// EFFECTS: Returns alarmIsOn
// Getter - no test cases
bool AlarmSystem::getAlarmState() {
  // TODO: stub
  return false;
}