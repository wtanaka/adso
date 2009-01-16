#include "bu01.h"
#include "text.h"
#include "special.h"


Bu01::Bu01(Text *t): Special(t) { myclass += ":Bu01"; };
Bu01::~Bu01() {}

int Bu01::adjust_confidence(Text *t, int a, int b, int c) {

        if (t->is_category_non_recursive("Pronoun",a,b-1) == 1) {
        	if (t->is_category_non_recursive("Verb",a,b+1) == 1) {
                        t->make_only(a,b,"CAdverb");
                }
        }

	return 1;
}

