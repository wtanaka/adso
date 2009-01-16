#include "adjective.h"
#include "text.h"


Adjective::Adjective(Text *t): Unit(t) { myclass += ":Adjective";};
Adjective::~Adjective() {}

int Adjective::adjust_confidence(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("De01",a,b+1) == 1) {
    if (t->is_category_non_recursive("Noun",a,b+2) == 1) {
      if (t->is_category_non_recursive("Adverb",a,b+3) == 1) {
        if (t->is_category_non_recursive("Verb",a,b+4) == 1) {
	  if (t->is_category_non_recursive("Noun",a,b) == 1) {
            confidence -= 6;
	  }
        }
      } 
    }
  }

  if (t->is_category_non_recursive("De01",a,b+1) == 1) {
     confidence += 2;
  }

  if (t->is_category_non_recursive("Noun",a,b+1) == 1 && t->is_category_non_recursive("Punctuation",a,b+2) == 1) {
    if (t->is_category_non_recursive("Directional",a,b) != 1 && t->is_category_non_recursive("Measure",a,b+1) != 1) {
      confidence += 2;
      t->make_only(a,b+1,"Noun");
    }
  }

  return 1;
}

