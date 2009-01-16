#include "preposition.h"
#include "text.h"
#include "unit.h"



Preposition::Preposition(Text *t): Unit(t) { myclass += ":Preposition";};
Preposition::~Preposition() {}

int Preposition::adjust_confidence(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Comma",a,b-1) == 1) {
    if (t->is_category_non_recursive("Verb",a,b) == 1) {
      if (
	t->sentence_forward_category_match("Preposition",a,b) != -1 ||
	t->sentence_forward_category_match("Verb",a,b) != -1
      ) {
       
        confidence+=2;
      }
    }
  }

  if (t->is_category_non_recursive("Punctuation",a,b-1) == 1) {
    confidence+=2;
  }
  if (t->is_category_non_recursive("Punctuation",a,b-2) == 1) {
    confidence+=2;
  }
  if (t->is_category_non_recursive("Noun",a,b+1) == 1) {
    confidence+=2;
  }

  if (t->is_category_non_recursive("Opening",a,b+1) == 1) {
    confidence+=10;
  }


  return 1;
}

