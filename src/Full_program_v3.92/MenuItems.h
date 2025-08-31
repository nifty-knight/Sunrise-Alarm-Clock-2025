#ifndef MENUS_H
#define MENUS_H

#include "Menu.h"
#include "Page.h"
#include "RangedSelectionPage.h"

Page timeDisplayMenu("The time is now:", "");


Page alarmStatePage("", "");
RangedSelectionPage minSelect("", "", 0, 45, 15);

// Menu mainMenu("", "", ); // last argument is a pointer to an array of menuitems declared in this file

#endif