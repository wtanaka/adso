#include "determiner.h"
#include "text.h"
#include "unit.h"

Determiner::Determiner(Text *t): Unit(t) { myclass += ":Determiner"; };
Determiner::~Determiner() {}


int Determiner::adjust_confidence(Text *t, int a, int b, int c) {

	if (t->is_category_non_recursive("Noun", a, b+1) == 1) {
		confidence++;
		if (t->is_category_non_recursive("Punctuation", a, b-1) == 1 || b == 0) {
			t->make_only(a,b,this);
			t->make_only(a,b+1,"Noun");
		}
	}


	return 1;
}

