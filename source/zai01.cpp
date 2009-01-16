#include "zai01.h"
#include "special.h"
#include "text.h"


Zai01::Zai01(Text *t): Special(t) { myclass += ":Zai01";};
Zai01::~Zai01() {}


int Zai01::advanced(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Verb",a,b+1) == 1 && t->is_category_non_recursive("Punctuation",a,b+2) == 1) {
    english = "currently";
    t->make_only(a,b,this);
    t->make_only(a,b+1,"Verb");
  }

  if (t->return_chinese(a,b+2,0) == "ÆÚ¼ä") {
    english = "during the ";
    t->make_only(a,b,this);
  }

  return 1;
}

