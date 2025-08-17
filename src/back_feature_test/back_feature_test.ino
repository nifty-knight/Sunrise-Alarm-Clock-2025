#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Ds1302.h>

void off();
void displayMainMenu();
void selectPage(int index);
bool joystickUp();
bool joystickDown();
bool joystickLeft();
bool joystickRight();
void switchPage(int index);
String setPeriod();
int setHour();
int setMin();
int convertTo24HrTime(int hr, String s);
void printUpArrow();
void printDownArrow();
// void printLeftArrow();
// void printRightArrow();

// Test LCD with buttons & joystick control & RTC module
/*
TODO
- Add 'back' functions for setting alarm time
  - Add a cancel menu if joystickLeft() while on setPeriod
  - Move back to the previous menu/Set previous menu again if joystickLeft() on any other set menu
- Do the same for setting current time/user time

TESTING:

TODO
- 

DONE


*/

#include <Ds1302.h>

byte UpArrow[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b00000
};

byte DownArrow[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};

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

const int delayTime = 280;
const int readTime = 3500;
const int noActivityTime = 20000; // 25 secs

const int PIN_CLK = 7;
const int PIN_DAT = 6;
const int PIN_ENA = 5;  // RST on the module

const String PERIOD_ERROR = "ERROR";
const int HOUR_ERROR = -1;
const int MIN_ERROR = -1;
const int YEAR_ERROR = 0;

// DS1302 RTC instance
Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);
Ds1302::DateTime alarmTime;
Ds1302::DateTime fadeStartTime;
// Ds1302::DateTime currentTime;
bool alarmIsOn = false;        // initialized as off originally

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(13, 11, 10, 8, 3, 2);
const int backlightPin = 19;
const uint8_t backlightButtonPin = A4;  // NOTE: make sure to change this after so they don't use the same pin, I'm just too lazy to wire up another one
bool displayOn = true;

const uint8_t displayButtonPin = A0; // displays current time when pressed
const uint8_t selectButtonPin = A4; // used to select options for menu and turn the light off
int index;                     // menu index (aka menu "page/tab")
const int MAX_MENU_INDEX = 2;  // represents 3 allowed pages for main menu

const uint8_t X_pin = A1;  // analog pin connected to X output of joystick
const uint8_t Y_pin = A2; // analog pin connected to Y output of joystick
int X_pos;
int Y_pos;

long startTime; // starting time for activity timer

const int ledPin = 9;
bool lightIsOn = false; // keeps track of the state of the LED light; off initially
float fadeTime = 20; // time in minutes for the light to go from 0 to full brightness
int brightness = 0; // 0-255
int brightnessMultiplier = 2; // Range from 1..*, the smaller the number the brighter it gets
long ledStartTime; // used for controlling light brightness
long waitTime; // the amount of delay before increasing the brightness of the light

void setup() {
  // TODO: Serial is not needed for the final sketch
  Serial.begin(9600);
  rtc.init();
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
  pinMode(selectButtonPin, INPUT);
  pinMode(displayButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  turnLightOff();
  startTime = millis();
  ledStartTime = millis();

  Ds1302::DateTime currentTime = {
    .year = 2025,
    .month = Ds1302::MONTH_MAY,
    .day = 30,
    .hour = 19,
    .minute = 51,
    .second = 0,
    .dow = Ds1302::DOW_FRI
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
  // lcd.createChar(0, LeftArrow);
  // lcd.createChar(1, RightArrow);
  lcd.createChar(2, UpArrow);
  lcd.createChar(3, DownArrow);
  off();
}

void loop() {

  if (pressed(displayButtonPin)) {
    on();
    printCurrentTime();
  }

  if (pressed(selectButtonPin)) {

    if (displayOn) {
      resetActivityTimer();
      selectPage(index);
    } else {
      resetActivityTimer();
      displayMainMenu();
    }
  }

  if (displayOn) {
    if (joystickUp()) switchPage(-1);
    else if (joystickDown()) switchPage(1);
  }

  if (displayOn && ((millis() - startTime) > noActivityTime)) {
    off();
  }

  if (alarmIsOn && !lightIsOn && nowIsTime(fadeStartTime)) {
    setupFade();
  } else if (alarmIsOn && lightIsOn && (brightness < 255)) { // light is on, not at full brightness
    // side note: I can NOT tell if the light is on using analogREad without lightIsOn var - it's in output mode
    if ((millis() - ledStartTime) >= waitTime) {
      analogWrite(ledPin, brightness);
      brightness++;
      ledStartTime = millis();
    }

  }
}

// note that fading is kinda paused while user is busy on screen, but it shouldn't matter all that much
// note that fading will not work if user is in a menu screen when the alarm passes
    // I could add the if to check in the function while loops

// EFFECTS: Sets up the variable needed to start fading in the light in the while loop
void setupFade() {
  ledStartTime = millis();
  lightIsOn = true;
  waitTime = abs(round(fadeTime * (60L * 1000L) / 255.0)) * brightnessMultiplier; // * multiplier because I find full brightness too much
  brightness = 1;
  analogWrite(ledPin, brightness);
}

// REQUIRES: time is not null
// EFFECTS: Returns true if the current time matches the given time (up to the second)
//          note: returns true if the hour and minute and second all match (when setting alarm time, give user option only for hour and minute, set time to zero)
//               - matches second +- 4 secs
bool nowIsTime(Ds1302::DateTime time) {
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  if ((now.hour == time.hour) && (now.minute == time.minute) 
      && ((now.second <= time.second + 4) || (now.second >= time.second - 4))) return true;
  else {
    return false;
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
  int hr = 1;
  int min = 0;
  int year = 25;

  String period = setPeriod();
  if (period.equals(PERIOD_ERROR)) {
    year = YEAR_ERROR;
  } else {
    hr = convertTo24HrTime(hr, period);
  }

  while (true) {
    hr = setHour();
    if (hr == HOUR_ERROR) {
      period = setPeriod();
      if (period.equals(PERIOD_ERROR)) {
        year = YEAR_ERROR;
        break;
      }
    } else {
      min = setMin();
      if (min == MIN_ERROR) {
        continue;
      } else {
        hr = convertTo24HrTime(hr, period);
        break;
      }
    }
  }

  Ds1302::DateTime time = { // note that day, month, year, dow are fairly random; only time matters here
    .year = year,
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
  lcd.setCursor(14, 0);
  printUpArrow();
  lcd.setCursor(14, 1);
  printDownArrow();
  delay(delayTime);

  while (true) {
    if (pressed(selectButtonPin) || joystickRight()) {
      delay(delayTime);
      if (cursor == 0) return "AM";
      else return "PM";
    } else if (joystickUp()) {
      cursor = 0;
      lcd.setCursor(11, 0);
      lcd.print("A");
    } else if (joystickDown()) {
      cursor = 1;
      lcd.setCursor(11, 0);
      lcd.print("P");
    } else if (joystickLeft()) {
      delay(delayTime);
      // Serial.print("To the left\n");
      return PERIOD_ERROR;
    }
  }
}

// EFFECTS: does the minute selection menu, allows user to select an hour between 1-12 inclusive, returns user selection
int setHour() {
  int cursor = 7;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Set Hour: 07 "); // NOTE: this has to change along w/ initial cursor number if changed
  printUpArrow();
  lcd.setCursor(14, 1);
  printDownArrow();
  delay(delayTime);

  while (true) {
    if (pressed(selectButtonPin) || joystickRight()) {
      delay(delayTime);
      return cursor;
    } else if (joystickUp()) {
      if (cursor <= 1) cursor = 12;
      else cursor--;
      lcd.setCursor(11, 0);
      if (cursor < 10) lcd.print("0");
      lcd.print(cursor);
      delay(delayTime);
    } else if (joystickDown()) {
      if (cursor >= 12) cursor = 1;
      else cursor++;
      lcd.setCursor(11, 0);
      if (cursor < 10) lcd.print("0");
      lcd.print(cursor);
      delay(delayTime);
    } else if (joystickLeft()) {
      delay(delayTime);
      return HOUR_ERROR;
    }
  }
}

// EFFECTS: does the minute selection menu, allows user to select a minute between 0-59, returns user selection
// for now only supports 15-min increments -> in the future may support 5-min increments
int setMin() {
  int range[] = {0,15,30,45};
  int size = 4; // size of the range[] array

  int cursor = 0;
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Set Min: 00 "); // NOTE: this has to change along w/ initial cursor number if changed
  lcd.setCursor(14, 0);
  printUpArrow();
  lcd.setCursor(14, 1);
  printDownArrow();
  delay(delayTime);

  while (true) {
    if (pressed(selectButtonPin) || joystickRight()) {
      delay(delayTime);
      return range[cursor];
    } else if (joystickUp()) {
      if (cursor <= 0) cursor = (size - 1);
      else cursor--;
      lcd.setCursor(11, 0);
      if (range[cursor] < 10) lcd.print("0");
      lcd.print(range[cursor]);
      delay(delayTime);
    } else if (joystickDown()) {
      if (cursor >= (size - 1)) cursor = 0;
      else cursor++;
      lcd.setCursor(11, 0);
      if (range[cursor] < 10) lcd.print("0");
      lcd.print(range[cursor]);
      delay(delayTime);
    } else if (joystickLeft()) {
      return MIN_ERROR;
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
  Ds1302::DateTime temp = userSetTime();
  if (temp.year != YEAR_ERROR) { // If year == 0, that means user cancelled
    alarmTime = temp;
    setFadeStartTime();
    printAlarmState(); 
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cancelled");
    delay(readTime);
    displayMainMenu();
  }
  // alarmTime = userSetTime();
  // setFadeStartTime();
  // printAlarmState();
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
  lcd.print("   Set alarm");
  lcd.setCursor(14, 0);
  printUpArrow();
  lcd.setCursor(14, 1);
  printDownArrow();
}

// EFFECTS: Prints current time to the LCD, then turns off the display after readDelay sec
void printCurrentTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The time is now:");
  lcd.setCursor(5, 1);
  Ds1302::DateTime now;
  rtc.getDateTime(&now);
  lcd.print(getTime(now));
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
  lcd.print("Set to: ");
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

// EFFECTS: Returns true if joystick has been moved upwards
bool joystickUp() {
  if (analogRead(Y_pin) <= 25) {
    return true;
  }
  return false;
}

// EFFECTS: Returns true if joystick has been moved downwards
bool joystickDown() {
  if (analogRead(Y_pin) >= 1000) {
      return true;
    }
    return false;
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
}

// EFFECTS: Turns of the LED light
void turnLightOff() {
  lightIsOn = false;
  analogWrite(ledPin, 0);
}

// EFFECTS: Reset activity timer so that screen won't turn off for another 25 secs or so
void resetActivityTimer() {
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

// EFFECTS: Displays up arrow on the lcd display at current cursor position
void printUpArrow() {
  lcd.write(byte(2));
}

// EFFECTS: Displays down arrow on the lcd display at current cursor position
void printDownArrow() {
  lcd.write(byte(3));
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
