#include "conjunction.h"
#include "text.h"


Conjunction::Conjunction(Text *t): Unit(t) { myclass += ":Conjunction";};
Conjunction::~Conjunction() {}


int Conjunction::adjust_confidence(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Punctuation",a,b-1) == 1) {
    confidence += 2;
  }
  if (t->is_category_non_recursive("Punctuation",a,b+1) == 1 && t->is_category_non_recursive("Punctuation",a,b-1) == 1) {
	t->make_only(a,b,this);
  }

  return 1;
}

