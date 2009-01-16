#include "mment.h"
#include "unit.h"
#include "text.h"


Mment::Mment(Text *t): Unit(t) { myclass += ":Mment";};
Mment::~Mment() {}


int Mment::adjust_confidence(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Number",a,b-1) == 1) {
     t->make_only(a,b,this);
     confidence++;
  }
  return 1;

}

