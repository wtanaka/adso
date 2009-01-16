#include "jiang01.h"
#include "special.h"
#include "text.h"


Jiang01::Jiang01(Text *t): Special(t) { myclass += ":Jiang01";};
Jiang01::~Jiang01() {}

int Jiang01::adjust_confidence(Text *t, int a, int b, int c) {

	if (t->is_category_non_recursive("Verb",a,b-1) == 1) {
	  t->add_confidence("Auxiliary",2,a,b);
	}
	if (t->is_category_non_recursive("Verb",a,b+1) != 1) {
	  t->add_confidence("Auxiliary",2,a,b);
	}
	if (t->is_category_non_recursive("Noun",a,b+1) == 1) {
	  t->add_confidence("Verb",2,a,b);
	}

	return 1;
}


