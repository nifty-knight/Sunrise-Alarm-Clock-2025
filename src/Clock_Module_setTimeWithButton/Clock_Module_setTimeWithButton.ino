#include <Arduino.h>
#include <Ds1302.h>

const int PIN_ENA = 5;
const int PIN_CLK = 7;
const int PIN_DAT = 6;

// DS1302 RTC instance
Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);

// Not needed - kept as reference code for arrays
// const static char* WeekDays[] =
// {
//     "Monday",
//     "Tuesday",
//     "Wednesday",
//     "Thursday",
//     "Friday",
//     "Saturday",
//     "Sunday"
// };

/* Steps:
Done
- first make something happen on button press
- Then make ability to see current time on button press

TODO
- Make a program that prints ALARM ALARM ALARM when the current time reaches the alarm time
- Then figure out a system to set time on button press using only a few buttons
  - note: when you reattach clock module, check if time has changed or needs to be set again
- 
*/ 

bool isPressed;

void setup() {
  // put your setup code here, to run once:
  isPressed = false;
  pinMode(8, INPUT);
  Serial.begin(9600);
  // initialize the RTC
  rtc.init();

  // set a date-time to start the clock

  // Ds1302::DateTime dt = {
  //     .year = 24,
  //     .month = Ds1302::MONTH_APR,
  //     .day = 26,
  //     .hour = 9,
  //     .minute = 13,
  //     .second = 0,
  //     .dow = Ds1302::DOW_SAT
  // };

  // rtc.setDateTime(&dt);
}

void loop() {
  // put your main code here, to run repeatedly:
  isPressed = digitalRead(8);
  if (isPressed) {
    printCurrentTime();
    delay(200);
  }
}

// TODO: make it so that month is printed as words not numbers
// EFFECTS: Prints the current time (12-hr) to the serial monitor
void printCurrentTime() {
  // get the current time
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  if (now.hour < 10) Serial.print(' ');
  if (now.hour < 12) Serial.print(now.hour + 1);
  else Serial.print(now.hour - 12);
  Serial.print(':');
  if (now.minute < 10) Serial.print('0');
  Serial.print(now.minute);  // 00-59
  Serial.print(':');
  if (now.second < 10) Serial.print('0');
  Serial.print(now.second);  // 00-59
  if (now.hour < 11) Serial.print(" AM");
  else Serial.print(" PM");
  Serial.println();
}
