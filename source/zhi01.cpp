#include "zhi01.h"
#include "special.h"
#include "text.h"


Zhi01::Zhi01(Text *t): Special(t) { myclass += ":Zhi01";};
Zhi01::~Zhi01() {}

int Zhi01::advanced(Text *t, int a, int b, int c) {

  if (t->return_chinese(a,b+2,0) == "ÄÚ") {
    english = "to within";
    t->make_only(a,b,this);
    t->make_only(a,b+2,t->text(a,b+2,0));
    t->text(a,b+2,0)->should_translate = 0;
  }

  return 1;
}

