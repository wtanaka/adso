#include "cadverb.h"
#include "text.h"
#include "unit.h"

Cadverb::Cadverb(Text *t): Unit(t) { 
	myclass += ":Cadverb"; 
};
Cadverb::~Cadverb() {}

int Cadverb::adjust_confidence(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Xing",a,b+1) == 1) {
    t->add_confidence("Xing",2,a,b+1);
    confidence+=2;
  }
  if (t->is_category_non_recursive("Adjective",a,b+1) == 1) {
    t->add_confidence("Adjective",2,a,b+1);
    confidence+=2;
  }
  if (t->is_category_non_recursive("Adjective",a,b+1) == 1 && t->is_category_non_recursive("De01",a,b+2) == 1) {
    t->make_only(a,b,this);
    t->add_confidence("Adjective",2,a,b+1);
  }

  return 1;
}


