#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Ds1302.h>

void on();
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
void daylightSavingChange(int change);
void printUpArrow();
void printDownArrow();
// void printLeftArrow();
// void printRightArrow();
void turnLightOff();
void printCurrentTime();
void printAlarmState();
void resetActivityTimer();

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

const int delayTime = 525;
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
bool alarmIsOn = false;        // initialized as off originally

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(13, 11, 10, 8, 3, 2);
const uint8_t backlightPin = A5; // A on LCD

bool displayOn = true;

const uint8_t displayButtonPin = A3; // displays current time when pressed - previously A0
const uint8_t selectButtonPin = A4; // used to select options for menu and turn the light off
int index;                     // menu index (aka menu "page/tab")
const int MAX_MENU_INDEX = 4;  // represents 5 allowed pages for main menu - set alarm, set current time, current time +1hr, current time -1hr, toggle alarm

const uint8_t X_pin = A1;  // analog pin connected to X output of joystick
const uint8_t Y_pin = A0; // analog pin connected to Y output of joystick
int X_pos;
int Y_pos;

unsigned long startTime; // starting time for activity timer

const int ledPin = 9; // MOSFET control pin (SIG)
bool lightIsOn = false; // keeps track of the state of the LED light; off initially
float fadeLength = 20; // time in minutes for the light to go from 0 to full brightness
int brightness = 0; // 0-255
int brightnessMultiplier = 1; // Range from 1..*, the smaller the number the brighter it gets
unsigned long long ledStartTime; // used for controlling light brightness
unsigned long long waitTime; // the amount of delay before increasing the brightness of the light

void setup() {
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
  pinMode(selectButtonPin, INPUT);
  pinMode(displayButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  turnLightOff();
  startTime = millis();
  ledStartTime = millis();

  rtc.init();

  if (rtc.isHalted()) {
    Ds1302::DateTime currentTime = {
      .year = 2025,
      .month = Ds1302::MONTH_AUG,
      .day = 9,
      .hour = 16,
      .minute = 32,
      .second = 0,
      .dow = Ds1302::DOW_SAT
    };

    rtc.setDateTime(&currentTime);
  }

  pinMode(backlightPin, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Clears the LCD screen
  lcd.clear();
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

    if (lightIsOn) {
      turnLightOff();
      delay(delayTime);
    } else if (displayOn) {
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
    if ((millis() - ledStartTime) >= waitTime) {
      brightness++;
      analogWrite(ledPin, brightness);
      ledStartTime = millis();
    }

  }
}

// EFFECTS: Sets up the variable needed to start fading in the light in the while loop
void setupFade() {
  lightIsOn = true;
  waitTime = abs(round(fadeLength * (60L * 1000L) / 255.0)) * brightnessMultiplier; // * multiplier if full brightness too much
  brightness = 1;
  analogWrite(ledPin, brightness);
  ledStartTime = millis();
}

// REQUIRES: time is not null
// EFFECTS: Returns true if the current time matches the given time (up to the second)
//          note: returns true if the hour and minute and second all match (when setting alarm time, give user option only for hour and minute, set time to zero)
//               - matches second +- 8 secs
bool nowIsTime(Ds1302::DateTime time) {
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  if ((now.hour == time.hour) && (now.minute == time.minute) 
      && ((now.second <= time.second + 8) || (now.second >= time.second - 8))) return true;
  else {
    return false;
  }
}

// EFFECTS: Returns true if the button connected to the given pin is being pressed
//          - note that the buttons I am using are backwards - let current flow when not pressed, block current when they are pressed - eg. 0 = pressed, 1 = not pressed
// FOR INVERTED BUTTONS
bool pressed(int pin) {
  if (digitalRead(pin)) {
    return false;
  } else {
    return true;
  }
}

// EFFECTS: Returns true if the button connected to the given pin is being pressed
//          - note that the buttons I am using are backwards - let current flow when not pressed, block current when they are pressed - eg. 0 = pressed, 1 = not pressed
// FOR NON-INVERTED BUTTONS - uncomment the below pressed() function and comment out the above pressed() function
// bool pressed(int pin) {
//   if (digitalRead(pin)) {
//     return true;
//   } else {
//     return false;
//   }
// }

// EFFECTS: Guides user through setting a new time and returns the time
Ds1302::DateTime userSetTime() {
  int hr = 1;
  int min = 0;
  int year = 25;

  String period = setPeriod();
  if (period.equals(PERIOD_ERROR)) {
    year = YEAR_ERROR;
  } else {
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
  }

  Ds1302::DateTime time = { // note that day, month, year, dow are fairly random; only time really matters here
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
  lcd.print("Set Hour: 07 "); // NOTE: this has to change along w/ initial cursor number if changed - coupling :(
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
  delay(delayTime);
  switch (index) {
    case 0: {
      alarmIsOn = true;
      displayMainMenu();
      Ds1302::DateTime temp = userSetTime();
      if (temp.year != YEAR_ERROR) { // If year==YEAR_ERROR, that means user cancelled
        alarmTime = temp;
        setFadeStartTime();
        printAlarmState(); 
      } else {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Set alarm");
        lcd.setCursor(3, 1);
        lcd.print("cancelled");
        delay(readTime);
        displayMainMenu();
      }
      break;
    }
    case 1: {
      Ds1302::DateTime temp = userSetTime();
      if (temp.year != YEAR_ERROR) { // If year==YEAR_ERROR, that means user cancelled
        rtc.setDateTime(&temp);
        printCurrentTime();
      } else {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Set time");
        lcd.setCursor(3, 1);
        lcd.print("cancelled");
        delay(readTime);
        displayMainMenu();
      }
      break;
    }
    case 2: { // Change time for daylight savings forward 1hr
      daylightSavingChange(1);
      printCurrentTime();
      break;
    }
    case 3: {
      daylightSavingChange(-1);
      printCurrentTime();
      break;
    }
    case 4: {
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
void setPage(int index) {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (index == 0) {
    lcd.print("   Set alarm");
    lcd.setCursor(14, 0);
    printUpArrow();
    lcd.setCursor(14, 1);
    printDownArrow();
    //
  } else if (index == 1) {
    lcd.print("    Set time");  // Set time
    lcd.setCursor(14, 0);
    printUpArrow();
    lcd.setCursor(14, 1);
    printDownArrow();
  } else if (index == 2) {
    lcd.print("   Move time");
    lcd.setCursor(14, 0);
    printUpArrow();
    lcd.setCursor(0, 1);
    lcd.print(" forward 1hr");
    lcd.setCursor(14, 1);
    printDownArrow();
  } else if (index == 3) {
    lcd.print("   Move time");
    lcd.setCursor(14, 0);
    printUpArrow();
    lcd.setCursor(0, 1);
    lcd.print(" backward 1hr");
    lcd.setCursor(14, 1);
    printDownArrow();
  } else if (index == 4) {
    lcd.print(" Toggle alarm ");  // Alarm toggle
    printUpArrow();
    lcd.setCursor(14, 1);
    printDownArrow();
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
  Ds1302::DateTime currentTime;
  rtc.getDateTime(&currentTime);
  lcd.print(getTime(currentTime));

  long now = millis();
  long end = millis() + long(readTime);

  while (now < end) {
    if (pressed(selectButtonPin)) {
      displayMainMenu();
      return;
    }

    now = millis();
  }

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
  
  long now = millis();
  long end = millis() + long(readTime);

  while (now < end) {
    if (pressed(selectButtonPin)) {
      displayMainMenu();
      return;
    }

    now = millis();
  }

  off();
}

// EFFECTS: Turns on the lcd display and backlight and shows the current time
void displayTime() {
  on();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("The time is now: "));  // note: could do some fun things depending on the time
  lcd.setCursor(0, 1);
  Ds1302::DateTime now;
  rtc.getDateTime(&now);
  lcd.print(getTime(now));
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
  if (analogRead(X_pin) <= 15) {
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
void setFadeStartTime() {

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

void daylightSavingChange(int change) {
  Ds1302::DateTime old;
  rtc.getDateTime(&old);
  int newHour = old.hour + change;

  if (newHour < 0) newHour = 23;
  else if (newHour > 23) newHour = 0;

  Ds1302::DateTime newTime = { // note that day, month, year, dow are fairly random; only time matters here
    .year = old.year,
    .month = old.month,
    .day = old.day,
    .hour = newHour,
    .minute = old.minute,
    .second = old.second,
    .dow = old.dow
  };

  rtc.setDateTime(&newTime);
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
