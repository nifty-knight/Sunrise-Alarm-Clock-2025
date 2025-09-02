#include "RangedSelectionPage.h"

// REQUIRES: minn and maxn are 1-2 digit numbers
// EFFECTS: Initializes page variables (minn, maxn inclusive); sets current to minimum
RangedSelectionPage::RangedSelectionPage(String line1, String line2, void (*selectAction)(), int minn, int maxn, int step) : GenericPage(line1, line2, *selectAction), minn(minn), maxn(maxn), step(step) {
  // TODO: stub
}

// EFFECTS: displays page with minimum number
void RangedSelectionPage::display() {
  // TODO: stub
}

// EFFECTS: updates the number on lcd display based on joystick direction,
//          ignores directions other than up/down
// TODO: make increase() and decrease() private
void RangedSelectionPage::joystickResponse(Direction d) {
  // TODO: stub
}

// EFFECTS: runs selectAction(), returns to main menu
void RangedSelectionPage::select() {
  // TODO: stub
}

// REQUIRES: last page displayed was this RangedSelectionPage (since it only changes the number)
// EFFECTS: displays page with number decreased by one step unless already displaying minimum number
/*Test cases - test in hardware
- test that it decreases number
- check that it doesn't display a number below the minimum */
void RangedSelectionPage::decrease() {
  // TODO: stub
}

// REQUIRES: last page displayed was this RangedSelectionPage (since it only changes the number)
// EFFECTS: displays page with number decreased by one step unless already displaying maximum number
/*Test cases - test in hardware
- test that it increases number
- check that it doesn't display a number above the maximum */
void RangedSelectionPage::increase() {
  // TODO: stub
}