#include "AlarmSystem.cpp" // TODO: replace all with .h
#include "DisplayController.h"
#include "InputController.cpp"

// Pin numbers for the RTC Module - TODO: maybe I don't need these data members stored here, just add documentation for where they should go in rtc constructor
const uint8_t PIN_CLK = 7;
const uint8_t PIN_DAT = 6;
const uint8_t PIN_ENA = 5;  // RST on the module itself

AlarmSystem alarmSystem;
// DisplayController displayController;
// InputController inputController;

// Main file where program is run

void setup() {
  // put your setup code here, to run once:
  // alarmSystem = AlarmSystem();
  // displayController = DisplayController();
  // inputController = InputController();
}

void loop() {
  // put your main code here, to run repeatedly:

  // inputController.update();
  // displayController.update(InputEvent::None); // note: don't know if this will mess with the program's operations; might not need this function, and only updates on inputController call
  // alarmSystem.update(InputEvent::None);
  
}

/* Current coding TODOs:
- Create .cpp files with stub functions and fields for all classes
- Create test scenarios for all functions (don't implement a full testing framework YET)
- implement some testing + test framework for more easily tested functions/classes - put it in a different folder than the this sketch
- Add one-line class description above class declaration for all .cpp files
- Add .h files for all .cpp files
- Modify all includes to include .h, not .cpp
- Ensure there is documentation for all fields & functions




*/