#include "AlarmSystem.h"

// EFFECTS: initializes necessary fields & subclass objects & set initial alarmTime to 1:00am
// TODO: maybe include alarmTime as an optional parameter?
AlarmSystem::AlarmSystem(uint8_t fadeTime, uint8_t clk, uint8_t dat, uint8_t ena, uint8_t ledPin) : clock(clk, dat, ena), lightController(ledPin) {
  fadeTime = fadeTime;
  alarmIsOn = false;
  // alarmTime = // TODO: Do I actually need to initially set this? If not, remove initial set time from EFFECTS
}

// EFFECTS: Updates the state of the light and clock as necessary
/*Test cases - tested in hardware
- update(SelectButtonPressed) --> turn light off if it is on, nothing otherwise
- Ignore all other events - do the same thing in any case
- Check that light turns on at the correct time
- Check that light does not turn on if alarmIsOn is off
- Check that light gets brighter at the correct times - as time progresses
*/
void AlarmSystem::update(InputEvent i) {
  if ((i == InputEvent::SelectButtonPressed) && (lightController.lightIsOn())) {
    lightController.setBrightness(0); // Turn light off if on on selectButtonPressed
  }
  if (nowIsTime(this->getFadeTime(alarmTime)) && alarmIsOn && !lightController.lightIsOn()) {
    // Turn light on:
    lightController.increaseBrightness();
    // setup wait time
    waitTime = abs(round(fadeTime * (60UL * 1000UL) / 255.0));
  } else if (alarmIsOn && lightController.lightIsOn() && (lightController.getBrightness() < 255)) {
    if ((millis() - ledStartTime) >= waitTime) {
      lightController.increaseBrightness();
      ledStartTime = millis();
    }
  }
}

// EFFECTS: Return the fadetime for the given alarm time, using fadetime minutes
// TODO: Will the program get mad if I don't initialize fadeStartTime's year, month, day, DOW?
// TODO: test cases?
Ds1302::DateTime AlarmSystem::getFadeTime(Ds1302::DateTime alarmTime) {
  Ds1302::DateTime fadeStartTime;

  if (alarmTime.minute >= this->fadeTime) {
    fadeStartTime.minute = alarmTime.minute - this->fadeTime;
  } else {
    int minLeft = this->fadeTime - alarmTime.minute;
    fadeStartTime.minute = 60 - minLeft;
    if (alarmTime.hour > 0) fadeStartTime.hour = alarmTime.hour - 1; 
    else fadeStartTime.hour = 23;
  }
  return fadeStartTime;
}

// EFFECTS: Returns true if the current time matches the given time to the hour and minute
/* Test cases
- t = 8:00pm, current = 8:00pm, nowIsTime(t) --> true
- t = 8:01pm, current = 8:00pm, nowIsTime(t) --> false
- t = 8:00pm, current = 8:00am, nowIsTime(t) --> false
- t = 7:55am, current = 8:55am, nowIsTime(t) --> false
*/
bool AlarmSystem::nowIsTime(Ds1302::DateTime t) {
  Ds1302::DateTime current = clock.getTime();
  if ((current.hour == t.hour) && (current.minute == t.minute)) return true;
  else return false;
}

// MODIFIES: 
// EFFECTS: 
void AlarmSystem::daylightSavingsChange(bool plus) {
  Ds1302::DateTime current = clock.getTime();
  if (plus) current.hour = current.hour + 1;
  else current.hour = current.hour - 1;
  clock.setTime(current);
}

// MODIFIES: alarmTime, alarmIsOn
// EFFECTS: Sets alarmTime to t and sets alarmIsOn to true
/*Test cases
- test setting it multiple times 
- check that alarmIsOn ends up true regardless of whether it started as false or true
*/
void AlarmSystem::setAlarmTime(Ds1302::DateTime t) {
  alarmTime = t;
  alarmIsOn = true;
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
  alarmIsOn = s;
}

// EFFECTS: Returns alarmTime
// Getter - no test cases
Ds1302::DateTime AlarmSystem::getAlarmTime() {
  return alarmTime;
}

// EFFECTS: Returns alarmIsOn
// Getter - no test cases
bool AlarmSystem::getAlarmState() {
  return alarmIsOn;
}
