#include "he01.h"
#include "special.h"
#include "text.h"


He01::He01(Text *t): Special(t) { myclass += ":He01";};
He01::~He01() {}

int He01::advanced(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Adjective",a,b+1) == 1) {
    t->make_only(a,b,this);
  }

  if (t->is_only_category_non_recursive("Noun",a,b-1) == 1 && t->is_category_non_recursive("Noun",a,b+1) == 1) {
    t->make_only(a,b-1,"Noun");
    t->make_only(a,b+1,"Noun");
    t->make_only(a,b,this);
  }
  if (t->is_category_non_recursive("Noun",a,b-1) == 1 && t->is_only_category_non_recursive("Noun",a,b+1) == 1) {
    t->make_only(a,b-1,"Noun");
    t->make_only(a,b+1,"Noun");
    t->make_only(a,b,this);
  }
  if (t->is_category_non_recursive("Number",a,b+1) == 1) {
    t->make_only(a,b,this);
  }

  if (t->is_category_non_recursive("Noun",a,b+2) == 1) {
    if (t->is_category_non_recursive("Verb",a,b+1) == 1 && t->is_category_non_recursive("Verb",a,b-1) == 1) {
      t->make_only(a,b-1,"Verb");
      t->make_only(a,b+1,"Verb");
      t->make_only(a,b+2,"Noun");
      t->make_only(a,b,this);
    }
  }
  return 1;
}

