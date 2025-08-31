#include "AlarmSystem.h"
#include "DisplayController.h"
#include "InputController.h"
// #include <HardwareSerial.h>

// Pin numbers for the RTC Module - TODO: maybe I don't need these data members stored here, just add documentation for where they should go in rtc constructor
const uint8_t PIN_CLK = 7;
const uint8_t PIN_DAT = 6;
const uint8_t PIN_ENA = 5;  // RST on the module itself

DisplayController displayController(13, 11, 10, 8, 3, 2, 3500, 20000, A5);
InputController inputController(A3, A4, A1, A0);

// Main file where program is run

void setup() {
  // Serial.begin(9600); // used for troubleshooting
  AlarmSystem::getInstance(20, 7, 6, 5, 9);
}

void loop() {
  // put your main code here, to run repeatedly:
  InputEvent i = inputController.update();
  displayController.update(i);
  AlarmSystem::getInstance().update(i);
  
}

/* Current coding TODOs:
- Ok we're going to skip the unit testing for now - too much trouble for not enough value
- Uncomment headers that were commented out for testing purposes (Clock.h, )
- Add one-line class description above class declaration for all .h files
- Ensure there is documentation for all fields & functions
- Add enum class for the different possible menus?

- Note: Do I want an init() function for LightController, Clock, etc? Maybe. We'll see in implementation if that makes it any easier
- It may turn out that DisplayController is the overarching controlling master class
  and may need to hold a field of AlarmSystem - in which case AlarmSystem may not need to be an observer of InputController


DONE:
- Add function docs for InputController update
- Create .cpp files with stub functions and fields for all classes
- Add necessary pin parameters for all constructors
- Create test scenarios for all functions (don't implement a full testing framework YET)
- Add .h files for all .cpp files
- Modify all includes to include .h, not .cpp

*/
