#ifndef PAGE_H
#define PAGE_H

#include "GenericPage.h"

class Page : public GenericPage {
  public:
    Page(String line1, String line2);
    void display() override;

};

#endif