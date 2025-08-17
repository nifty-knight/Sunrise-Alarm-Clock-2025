#include <Arduino.h>
#include <math.h>
#include <Ds1302.h>

/* MOSFET Testing
- This sketch is for figuring out how to dim/brighten the LEDs using the mosfet

TODO
- Play around with how long it takes to fade in (real life fade will probably be about 10-30 min)
  - Note: Try to customize the brightness a bit so that it initially brightens up very slowly/dimly
    - What's the brightness like at level 1/255? Still seems very bright
DONE
- Fade in the brightness of a single LED with arduino alone
- Fade in brightness of a single LED with mosfet
- Fade in at a certain time - preset on the sketch
- Turn off on the press of a button
- Test the whole thing with the LED strip lights
*/

const int PIN_CLK = 7;
const int PIN_DAT = 6;
const int PIN_ENA = 5; // RST on the module

// DS1302 RTC instance
Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);

Ds1302::DateTime fadeStartTime;
Ds1302::DateTime currentTime;

const int ledPin = 9;
const int buttonPin = 12;
int brightness = 0; // 0-255
float fadeTime = 20; // time in minutes for the light to go from 0 to full brightness
bool lightIsOn;
int delta = 1; 


void setup() {
  // put your setup code here, to run once:
  rtc.init();
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  lightIsOn = false;
  analogWrite(ledPin, 0);

  fadeStartTime = {
    .year = 24,
    .month = Ds1302::MONTH_APR,
    .day = 26,
    .hour = 17,
    .minute = 19,
    .second = 0,
    .dow = Ds1302::DOW_SAT
  };

  currentTime = {
    .year = 0,
    .month = Ds1302::MONTH_DEC,
    .day = 31,
    .hour = 17,
    .minute = 18,
    .second = 0,
    .dow = Ds1302::DOW_WED
  };

  // just so I know I set the time right
  rtc.setDateTime(&currentTime);
  printTime(currentTime);
  printTime(fadeStartTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  static uint8_t last_second = 0;
  if (last_second != now.second)
  {
      last_second = now.second;
      if (now.hour < 10) Serial.print('0');
      Serial.print(now.hour);    // 00-23
      Serial.print(':');
      if (now.minute < 10) Serial.print('0');
      Serial.print(now.minute);  // 00-59
      Serial.print(':');
      if (now.second < 10) Serial.print('0');
      Serial.print(now.second);  // 00-59
      Serial.println();
  }

  if (!lightIsOn && nowIsTime(fadeStartTime)) {
    Serial.println("ALARM ALARM ALARM");
    fadeInLight(fadeTime); // should I put fadeInLight to return true?
    lightIsOn = true;
  }

  if (lightIsOn && offButtonPressed()) {
    analogWrite(ledPin, 0);
    lightIsOn = false;
  }
  
}

// REQUIRES: fadeTime > 0
// MODIFIES: this: brightness
// EFFECTS: Calculates the speed at which the bulb should go from 0 to full brightness
//          based on the given fadeTime and changes the brightness of the bulb accordingly
//          note: fadeTime is in minutes, and brightness increase is linear (could change in the future)
void fadeInLight(float fadeTime) {

  long fadeTimeMilliSecs = abs(round(fadeTime * (60L * 1000L)));
  float test = fadeTimeMilliSecs / 255.0;
  long waitTime = round(fadeTimeMilliSecs / 255.0);
  int delta = 1;
  brightness = 0;
  // Serial.println(fadeTime);
  // Serial.println(fadeTimeMilliSecs);
  // Serial.println(test);
  // Serial.println(waitTime);

  while (brightness < 255) {
    analogWrite(ledPin, brightness);
    if ((brightness + delta) <= 255) brightness += delta;
    else brightness = 255;
    delay(waitTime);
  }

  lightIsOn = true;
  return;
}

// EFFECTS: Returns true if the off button is currently being pressed (1), false otherwise
bool offButtonPressed() {
  return digitalRead(buttonPin);
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

// EFFECTS: Prints the given time (12-hr) to the serial monitor
void printTime(Ds1302::DateTime time) {

  if (time.hour < 10) Serial.print(' ');
  if (time.hour < 12) Serial.print(time.hour + 1);
  else Serial.print(time.hour - 11);
  Serial.print(':');
  if (time.minute < 10) Serial.print('0');
  Serial.print(time.minute);  // 00-59
  Serial.print(':');
  if (time.second < 10) Serial.print('0');
  Serial.print(time.second);  // 00-59
  if (time.hour < 11) Serial.print(" AM");
  else Serial.print(" PM");
  Serial.println();
}


