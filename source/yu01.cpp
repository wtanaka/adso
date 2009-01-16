#include "yu01.h"
#include "special.h"
#include "text.h"


Yu01::Yu01(Text *t): Special(t) { myclass += ":Yu01";};
Yu01::~Yu01() {}

int Yu01::advanced(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Range", a, b+1) == 1) {
    english = "from";
    t->make_only(a,b,this);
  }

  if (t->is_category_non_recursive("Xing", a, b-1) == 1) {
    english = "than";
    t->text(a,b-1,"Text")->add_pre_english("more");
    t->make_only(a,b,this);
    t->make_only(a,b-1,"Xing");
  }

  return 1;
}

