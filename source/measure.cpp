#include "measure.h"
#include "unit.h"
#include "text.h"


Measure::Measure(Text *t): Unit(t) { myclass += ":Measure";};
Measure::~Measure() {}

int Measure::adjust_confidence(Text *t, int a, int b, int c) {

	if (t->is_category_non_recursive("Preposition",a,b+1) == 1) {
		confidence += 2;
		t->add_confidence("Preposition",2,a,b+1);
	}
	if (t->is_category_non_recursive("Noun",a,b+1) == 1) {
		confidence += 2;
		t->add_confidence("Noun",2,a,b+1);
	}
	if (t->is_category_non_recursive("Number",a,b-1) == 1) {
		confidence += 2;
		t->add_confidence("Number",3,a,b-1);
		t->add_confidence("Noun",3,a,b+1);
	}
	

	return 1;
}
int Measure::advanced(Text *t, int a, int b, int c) {

	if (t->is_category_non_recursive("Noun",a,b+1) == 1) {
		should_translate = 0;
	}
	if (t->is_category_non_recursive("Adjective",a,b+1) == 1) {
		should_translate = 0;
	}
	if (t->is_category_non_recursive("Xing",a,b+1) == 1) {
		should_translate = 0;
	}
	if (t->is_category_non_recursive("Opening",a,b+1) == 1) {
		should_translate = 0;
	}
	if (t->is_category_non_recursive("NonChinese",a,b+1) == 1) {
		should_translate = 0;
	}

	return 1;
}


