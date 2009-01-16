#include "person.h"
#include "propernoun.h"
#include "text.h"


Person::Person(Text *t): ProperNoun(t) { myclass += ":Person";};
Person::~Person() {}


int Person::combine(Text *parent, int a, int b, int c) {

	confidence++;

	if (parent->is_category_non_recursive("Dot",a,b+1) == 1 && parent->is_category_non_recursive("Phonetic",a,b+2) == 1) {
		add_post_english(" ");
		add_post_english(parent->text(a,b+2,"Phonetic")->return_english());
		shift_post_chinese(parent,a,b+1,0,this);
		shift_post_chinese(parent,a,b+1,0,this);
		if (parent->is_category_non_recursive("ProperNoun",a,b+1) == 1) {
			shift_post_chinese(parent,a,b+1,0,this);
		}
		parent->make_only(a,b,this);
	}
	if (parent->is_category_non_recursive("Dot",a,b+1) == 1 && parent->is_category_non_recursive("Person",a,b+2) == 1) {
		add_post_english(" ");
		add_post_english(parent->text(a,b+2,"Person")->return_english());
		shift_post_chinese(parent,a,b+1,0,this);
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "-" && parent->is_category_non_recursive("Person",a,b+2) == 1) {
		add_post_english("-");
		add_post_english(parent->text(a,b+2,"Person")->return_english());
		shift_post_chinese(parent,a,b+1,0,this);
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	return 1;
}

int Person::combine2(Text *parent, int a, int b, int c) { return 1; }
int Person::advanced(Text *parent, int a, int b, int c) {

	if (parent->is_category_non_recursive("De01",a,b+1) == 1) {
		possessive = 1;
		if (parent->is_category_non_recursive("Adjective",a,b+2) == 1) {
			parent->add_confidence("Adjective",2,a,b+2);
		}
		if (parent->is_category_non_recursive("Noun",a,b+2) == 1) {
			parent->add_confidence("Noun",2,a,b+2);
		}
	}

	return 1;
}

