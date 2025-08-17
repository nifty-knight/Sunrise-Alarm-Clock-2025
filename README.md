# Sunrise-Alarm-Clock-2025

Do you hate the sound of your alarm in the morning? Would you rather wake up peacefully, gently, and - most importantly - <i>quietly</i>?
If so, consider making a Sunrise Alarm Clock! This repo is part of an [instructable tutorial]() on how to do just that.

TODO: add link to instructable

## Clock User Instructions

TODO
- display and time buttons, what they do
- How to set alarm and current time
- How to turn off the alarm
- What the daylight savings menus do
- program settings on start/reset program
- What the toggle alarm does

## Notes
- The code is still being updated, check back for improved and more robust versions of the program!

## Features to add
- Add interruptibility to all reads/displays, right now only some of them are interruptible
- Include a function to prevent 
    the user from setting an alarm less than fadetime mins (currently 20 mins) from now
- Check that all functions to do with milliseconds and longs are subtraction - no addition to prevent rollover errors
- Add unit testing framework
- Add function so that looking at menus doesn't affect the light turning on or not
- Modify setHour() and setMin() functions to reduce coupling of cursor variable with magic number
- Add fun easter eggs
    - Ideas for funny messages to print to lcd using displayTime
        - "The time is now..." 
        - LUNCHTIME
        - Why are you awake? You have 1 hrs, 39 mins, and 56 secs of sleep time left
        - 11AM!!! YOU'RE LATE FOR SCHOOL haha just kidding it's actually ___ (real time)
        - Do you really need to pee again? I need to sleep too...
        - ...it's the witching hour ~ooohhhh~...

## Changelog/Completed Features

v3.5 - Added functionality to prevent the time from resetting if the Arduino loses power (requires cell battery for the RTC module)

v3 - Added interruptibility for reading current time & displaying current alarm state - pressing the Select button returns to the mains menu

v3 - Added 'back' functions and cancellation for setting alarm/current time

v3 - Added menu options for daylight savings to move the current time ahead/behind 1 hr

v2 - More custom arrow icons, changed menu switch directions (up/down instead of left/right)

v1 - Added custom icons for arrows

v1 - Added a timer to automatically switch off the LCD after 25 secs of inactivity, which resets on button click/joystick movement

v1 - Created menus for setting alarm time & current time

v1 - Added LCD menu switching with the joystick

v1 - Added functionality to display the current time for 5 seconds on Time button press