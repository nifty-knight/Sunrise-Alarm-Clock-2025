#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Ds1302.h>

void off();
void displayMainMenu();
void selectPage(int index);
bool joystickLeft();
bool joystickRight();
void switchPage(int index);
String setPeriod();
int setHour();
int setMin();
int convertTo24HrTime(int hr, String s);
void printLeftArrow();
void printRightArrow();

// Test LCD with buttons & joystick control & RTC module
/*
TODO
- merge program with the mosfet and led lights one
- Fix contrast - might just buy a potentiometer/steal one from sam
- improve the program - remove unnecessary variables etc.
- Add fun little easter eggs


DONE
- Get the LCD to print some message
- Get the backlight to turn on and off
- Get the current time to display and the backlight to turn on for 5 secs at the press of a button, then automatically turn off
  - Note: ideally the person would be able to do other stuff while the backlight display is on
  - Note: In this case I want a special button which just shows time and backlight - for night stuff, so it's ok
- Get the button to work with the LCD - something happens when a button is pressed
- Get the joystick to work with the LCD - switch menus when it is turned from side to side/up and down
- Add a timer which turns off the lcd automatically if no human use after 25 secs - resets on button click/joystick movement
- Create the program for menus to set alarm time & current time
- Make custom icons for arrows, other fun things
- add another button for nighttime display time


NOTES:
Ideas for funny messages to print to lcd using displayTime
- "The time is now..." 
  - LUNCHTIME
  - Why are you awake? You have 1 hrs, 39 mins, and 56 secs of sleep time left
  - 11AM!!! YOU'RE LATE FOR SCHOOL haha just kidding it's actually ___ (real time)
  - Do you really need to pee again? I need to sleep too...
  - ...it's the witching hour <emoji> <emoji>...

*/

#include <Ds1302.h>

byte RightArrow[8] = {
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b01110,
  0b01100,
  0b01000,
  0b00000
};

byte LeftArrow[8] = {
  0b00000,
  0b00010,
  0b00110,
  0b01110,
  0b01110,
  0b00110,
  0b00010,
  0b00000
};

const int delayTime = 310;
const int readTime = 4100;
const int noActivityTime = 20000; // 25 secs

const int PIN_CLK = 7;
const int PIN_DAT = 6;
const int PIN_ENA = 5;  // RST on the module

// DS1302 RTC instance
Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);
Ds1302::DateTime alarmTime;
Ds1302::DateTime fadeStartTime;
Ds1302::DateTime currentTime;
bool alarmIsOn = false;        // initialized as off originally

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(13, 11, 10, 8, 3, 2);
int backlightPin = 19;
uint8_t backlightButtonPin = A4;  // NOTE: make sure to change this after so they don't use the same pin, I'm just too lazy to wire up another one
bool displayOn = true;

uint8_t displayButtonPin = A0;
uint8_t selectButtonPin = A4;
int index;                     // menu index (aka menu "page/tab")
const int MAX_MENU_INDEX = 2;  // represents 3 allowed pages for main menu

const uint8_t X_pin = A1;  // analog pin connected to X output of joystick
int X_pos;

long startTime; // starting time for activity timer

void setup() {
  Serial.begin(9600);
  rtc.init();
  pinMode(X_pin, INPUT);
  pinMode(selectButtonPin, INPUT);
  pinMode(displayButtonPin, INPUT);
  startTime = millis();

  currentTime = {
    .year = 0,
    .month = Ds1302::MONTH_DEC,
    .day = 31,
    .hour = 17,
    .minute = 18,
    .second = 0,
    .dow = Ds1302::DOW_WED
  };
  // This sets the current time on the clock and starts it; I shouldn't need it
  // in the final version - use a cell battery to keep it going when disconnected
  rtc.setDateTime(&currentTime);

  // pinMode(backlightButtonPin, INPUT);
  pinMode(backlightPin, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Clears the LCD screen
  lcd.clear();
  lcd.createChar(0, LeftArrow);
  lcd.createChar(1, RightArrow);
  off();
}

void loop() {

  if (pressed(displayButtonPin)) {
    on();
    printCurrentTime();
  }

  if (!displayOn && pressed(selectButtonPin)) {
    resetActivityTimer();
    displayMainMenu();
  } else if (displayOn && pressed(selectButtonPin)) {
    resetActivityTimer();
    selectPage(index);
  }

  if (displayOn) {
    if (joystickLeft()) switchPage(-1);
    else if (joystickRight()) switchPage(1);
  }

  if (displayOn && ((millis() - startTime) > noActivityTime)) {
    off();
  }
}

// EFFECTS: Returns true if the button connected to the given pin is being pressed
bool pressed(int pin) {
  if (digitalRead(pin)) {
    return true;
  } else {
    return false;
  }
}

// EFFECTS: Guides user through setting a new time and returns the time
// TODO 1: complete function
Ds1302::DateTime userSetTime() {
  String period = "";
  int hr = -1;
  int min = -1;

  // use while true loop to get input?
  // should selectPage return an int?
  period = setPeriod();                         // choose am/pm
  hr = convertTo24HrTime(setHour(), period);  // 1-12
  min = setMin(); // 0, 15, 30, or 45

  Ds1302::DateTime time = { // note that day, month, year, dow are fairly random; only time matters here
    .year = 24,
    .month = Ds1302::MONTH_APR,
    .day = 26,
    .hour = hr,
    .minute = min,
    .second = 0,
    .dow = Ds1302::DOW_SAT
  };

  return time;
}

// REQUIRES: LCD display is on
// EFFECTS: does the period selection menu, allows user to select AM or PM, returns user selection
//          note: 0 = AM, 1 = PM
String setPeriod() {

  int cursor = 0;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Select: AM");
  lcd.setCursor(6, 1);
  printLeftArrow();
  lcd.setCursor(9, 1);
  printRightArrow();

  while (true) {
    if (pressed(selectButtonPin)) {
      delay(delayTime);
      if (cursor == 0) return "AM";
      else return "PM";
    } else if (joystickLeft()) {
      cursor = 0;
      lcd.setCursor(11, 0);
      lcd.print("A");
    } else if (joystickRight()) {
      cursor = 1;
      lcd.setCursor(11, 0);
      lcd.print("P");
    }
  }

  return "ERROR";
}

// EFFECTS: does the minute selection menu, allows user to select an hour between 1-12 inclusive, returns user selection
int setHour() {
  int cursor = 6;
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Set Hour:");
  lcd.setCursor(6, 1);
  printLeftArrow();
  lcd.print("06");  // NOTE: this has to change along w/ initial cursor number if changed
  printRightArrow();

  while (true) {
    if (pressed(selectButtonPin)) {
      delay(delayTime);
      return cursor;
    } else if (joystickLeft()) {
      if (cursor <= 1) cursor = 12;
      else cursor--;
      lcd.setCursor(7, 1);
      if (cursor < 10) lcd.print("0");
      lcd.print(cursor);
      delay(delayTime);
    } else if (joystickRight()) {
      if (cursor >= 12) cursor = 1;
      else cursor++;
      lcd.setCursor(7, 1);
      if (cursor < 10) lcd.print("0");
      lcd.print(cursor);
      delay(delayTime);
    }
  }

  return -1; // this line of code should never run
}

// EFFECTS: does the minute selection menu, allows user to select a minute between 0-59, returns user selection
// for now only supports 15-min increments -> in the future may support 5-min increments
int setMin() {
  int range[] = {0,15,30,45};
  int size = 4; // size of the range[] array

  int cursor = 0;
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Set Min:");
  lcd.setCursor(6, 1);
  printLeftArrow();
  lcd.print("00");  // NOTE: this has to change along w/ initial cursor number if changed
  printRightArrow();

  while (true) {
    if (pressed(selectButtonPin)) {
      delay(delayTime);
      return range[cursor];
    } else if (joystickLeft()) {
      if (cursor <= 0) cursor = (size - 1);
      else cursor--;
      lcd.setCursor(7, 1);
      if (range[cursor] < 10) lcd.print("0");
      lcd.print(range[cursor]);
      delay(delayTime);
    } else if (joystickRight()) {
      if (cursor >= (size - 1)) cursor = 0;
      else cursor++;
      lcd.setCursor(7, 1);
      if (range[cursor] < 10) lcd.print("0");
      lcd.print(range[cursor]);
      delay(delayTime);
    }
  }
}

// EFFECTS: Takes an hour in 12-hr time and AM or PM, and determines the time in 24-hr time
int convertTo24HrTime(int hour, String period) {
  if (period == "PM") {
    return hour += 11;
  } else return hour - 1;
}

// EFFECTS: calls new routine depending on the current menu and page
void selectPage(int index) {
  switch (index) {
    case 0: {
      alarmIsOn = true;
      delay(delayTime);
      displayMainMenu();
      alarmTime = userSetTime();
      setFadeStartTime();
      printAlarmState();
      break;
    }
    case 1: {
      delay(delayTime);
      currentTime = userSetTime();
      printCurrentTime();
      break;
    }
    case 2: {
      alarmIsOn = !alarmIsOn;
      printAlarmState();
      break;
    }
  }
}

// EFFECTS: switch the index and display the next page; 1 = to the right, -1 = to the left, other displays error on LCD
void switchPage(int next) {
  resetActivityTimer();
  if (next == 1) {
    if (index >= MAX_MENU_INDEX) {
      index = 0;
    } else index++;

  } else if (next == -1) {
    if (index <= 0) {
      index = MAX_MENU_INDEX;
    } else index--;

  } else {
    lcd.clear();
    lcd.print("ERROR next,switchPage");
  }

  setPage(index);

  delay(delayTime);
}

// EFFECTS: Turns on the lcd display and backlight and shows the main menu
void displayMainMenu() {
  index = 0;
  on();
  setPage(index);
  delay(delayTime);
}

// EFFECTS: Writes into the LCD display depending on the current menu and the given index
// TODO: Should displayTime be in here? Or should this method call displayTime?
// TODO: Idea - put the arrows in the middle on the bottom row, words on top row only - can get rid of numbers to shorten message
void setPage(int index) {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (index == 0) {
    lcd.print("   Set alarm");
    lcd.setCursor(6, 1);
    printLeftArrow();
    lcd.setCursor(9, 1);
    printRightArrow();
    //
  } else if (index == 1) {
    lcd.print("Set current time");  // Set time
    // lcd.setCursor(1, 5);
    // lcd.print("time");
    lcd.setCursor(6, 1);
    printLeftArrow();
    lcd.setCursor(9, 1);
    printRightArrow();
  } else if (index == 2) {
    lcd.print("   Toggle alarm");  // Alarm toggle
    // lcd.setCursor(1, 5);
    // lcd.print("alarm");
    lcd.setCursor(6, 1);
    printLeftArrow();
    lcd.setCursor(9, 1);
    printRightArrow();
  } else {
    lcd.print("ERROR index out of bounds");
  }
}

// EFFECTS: Prints current time to the LCD, then turns off the display after readDelay sec
void printCurrentTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The time is now:");
  lcd.setCursor(5, 1);
  lcd.print(getTime(currentTime));
  delay(readTime);
  off();
}

// EFFECTS: Prints alarm state (on/off) and time to the LCD, then turns off the display after readDelay sec
void printAlarmState() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Alarm is: ");
  if (alarmIsOn) {
    lcd.print("ON");
  } else lcd.print("OFF");
  lcd.setCursor(0, 1);
  lcd.print("Set to:");
  lcd.print(getTime(alarmTime));
  delay(readTime);
  off();
}

// EFFECTS: Turns on the lcd display and backlight and shows the current time
// TODO: Timer? So that it turns off after 5 secs
void displayTime() {
  on();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("The time is now: "));  // note: could do some funny things depending on the time
  lcd.setCursor(0, 1);
  Ds1302::DateTime now;
  rtc.getDateTime(&now);
  lcd.print(getTime(now));  // TODO: actually display time here
  delay(4000);
  off();
}

// EFFECTS: Returns true if joystick has been moved to the left
bool joystickLeft() {
  if (analogRead(X_pin) <= 25) {
    return true;
  }
  return false;
}

// EFFECTS: Returns true if joystick has been moved to the right
bool joystickRight() {
  if (analogRead(X_pin) >= 1000) {
    return true;
  }
  return false;
}

// MODIFIES: this - fadeStartTime
// EFFECTS: sets fadeStartTime to be 20 minutes before the given alarmTime - depends on how long I want the fade in to be
            // note: if you want the length of the fade to be different, change all the fadeLength vars
void setFadeStartTime() {

  int fadeLength = 20; // mins

  fadeStartTime = alarmTime;

  if (alarmTime.minute >= fadeLength) {
    fadeStartTime.minute = alarmTime.minute - fadeLength;
  } else {
    int minLeft = fadeLength - alarmTime.minute;
    fadeStartTime.minute = 60 - minLeft;
    if (alarmTime.hour > 0) fadeStartTime.hour = alarmTime.hour - 1; 
    else fadeStartTime.hour = 23;
  }

  // FOR TESTING PURPOSES:
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fade start time is:");
  lcd.setCursor(0, 1);
  lcd.print(fadeStartTime.hour);
  lcd.print(":");
  lcd.print(fadeStartTime.minute);
}

// EFFECTS: Reset activity timer so that screen won't turn off for another 25 secs or so
void resetActivityTimer() {
  // TODO
  startTime = millis();
}

// EFFECTS: Turns on the lcd light and display
void on() {
  lcd.display();
  backlight();
  displayOn = true;
  resetActivityTimer();
}

// EFFECTS: Turns off the lcd light and display
void off() {
  lcd.noDisplay();
  noBacklight();
  displayOn = false;
}

// EFFECTS: Displays right arrow on the lcd display at current cursor position
void printRightArrow() {
  lcd.write(byte(1));
}

// EFFECTS: Displays left arrow on the lcd display at current cursor position
void printLeftArrow() {
  lcd.write(byte(0));
}

// EFFECTS: Turns backlight on
void backlight() {
  digitalWrite(backlightPin, 1);
}

// EFFECTS: Turns backlight off
void noBacklight() {
  digitalWrite(backlightPin, 0);
}

// EFFECTS: Returns the given time (12-hr) as a string
String getTime(Ds1302::DateTime time) {

  String message = String("");

  if (time.hour < 10) message.concat(' ');
  if (time.hour < 12) message.concat(time.hour + 1);
  else message.concat(time.hour - 11);
  message.concat(':');
  if (time.minute < 10) message.concat('0');
  message.concat(time.minute);  // 00-59
  if (time.hour < 11) message.concat(" AM");
  else message.concat(" PM");

  return message;
}
