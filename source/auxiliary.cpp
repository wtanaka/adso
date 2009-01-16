#include "auxiliary.h"
#include "text.h"

Auxiliary::Auxiliary(Text *t): Unit(t) {
	myclass += ":Auxiliary";
};
Auxiliary::~Auxiliary() {}



int Auxiliary::adjust_confidence(Text *t, int a, int b, int c) {

	if (t->is_category_non_recursive("Preposition",a,b+1) == 1) { 
		//Setting the Tense
		for (int i = 1; i < 10; i++) {
			if (t->is_category_non_recursive("Verb",a,b+1+i) == 1) {
				for (int z = 0; z < t->elements->at(a)->at(b+1+i)->size(); z++) {
					t->elements->at(a)->at(b)->at(z)->vtense = 12;
					t->elements->at(a)->at(b)->at(z)->confidence += 2;
				}
			}
		}
		confidence+=3;
	}
	if (t->is_category_non_recursive("Preposition",a,b-1) == 1) { 
		if (t->is_category_non_recursive("Conjunction",a,b-1) == 1) { 
			t->make_only(a,b-1,"Conjunction");
		}
	}
	if (t->is_category_non_recursive("Verb",a,b+1) == 1) { 
		//Setting the Tense
		if (t->text(a,b+1,"Verb")->vtense == -1) {
			t->text(a,b+1,"Verb")->vtense = 2;
		}
		t->add_confidence("Verb",1,a,b+1);
		confidence ++;
	}
	if (t->is_category_non_recursive("Adverb",a,b+1) == 1) { 
		t->add_confidence("Adverb",1,a,b+1);
		confidence++;
		if (t->is_category_non_recursive("Verb",a,b+2) == 1) { 
			t->add_confidence("Adverb",2,a,b+1);
			t->add_confidence("Verb",2,a,b+2);
			confidence+=3;
		}
	}

	return 1;
}

