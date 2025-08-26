#include "AlarmSystem.h"
#include "DisplayController.h"
#include "InputController.h"

// Pin numbers for the RTC Module - TODO: maybe I don't need these data members stored here, just add documentation for where they should go in rtc constructor
const uint8_t PIN_CLK = 7;
const uint8_t PIN_DAT = 6;
const uint8_t PIN_ENA = 5;  // RST on the module itself

// AlarmSystem alarmSystem;
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
- Add function docs for InputController update
- Create .cpp files with stub functions and fields for all classes
- Add enum class for the different possible menus
- Add necessary pin parameters for all constructors
- Create test scenarios for all functions (don't implement a full testing framework YET)
- implement some testing + test framework for more easily tested functions/classes - put it in a different folder than the this sketch
- add testing for constructors
- Add one-line class description above class declaration for all .cpp files
- Add .h files for all .cpp files
- Modify all includes to include .h, not .cpp
- Ensure there is documentation for all fields & functions

- Note: Do I want an init() function for LightController, Clock, etc? Maybe. We'll see in implementation if that makes it any easier
- It may turn out that DisplayController is the overarching controlling master class
  and may need to hold a field of AlarmSystem - in which case AlarmSystem may not need to be an observer of InputController


*/
