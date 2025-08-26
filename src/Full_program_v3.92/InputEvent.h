#ifndef INPUTEVENT_H
#define INPUTEVENT_H

// Enumerator for different possible user input types
enum class InputEvent {
  None,
  TimeButtonPressed,
  SelectButtonPressed,
  JoystickUp,
  JoystickDown,
  JoystickLeft,
  JoystickRight
};

#endif