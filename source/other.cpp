#include "other.h"
#include "unit.h"
#include "text.h"


Other::Other(Text *t): Unit(t) { myclass += ":Other";};
Other::~Other() {}

int Other::adjust_confidence(Text *t, int a, int b, int c) {
	if (t->is_category_non_recursive("Punctuation",a,b-1) == 1) { confidence += 2; }
	return 1;
}
