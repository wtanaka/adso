#include "directional.h"
#include "unit.h"
#include "text.h"


Directional::Directional(Text *t): Unit(t) { myclass += ":Directional";};
Directional::~Directional() {}

int Directional::adjust_confidence(Text *t, int a, int b, int c) {

	if (t->is_category_non_recursive("Punctuation",a,b+1) == 1) {
		confidence++;
	}
	if (t->is_category_non_recursive("Verb",a,b+1) == 1) {
		confidence+=2.2;
	}
	if (t->is_category_non_recursive("Adverb",a,b+1) == 1) {
		confidence+=2.2;
	}

	return 1;
}

