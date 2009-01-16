#include "pronoun.h"
#include "noun.h"
#include "text.h"


Pronoun::Pronoun(Text *t): Noun(t) { myclass += ":Pronoun";};
Pronoun::~Pronoun() {}

int Pronoun::adjust_confidence(Text *t, int a, int b, int c) {

  confidence += 1;

  if (t->is_category_non_recursive("De01",a,b+1) == 1) {
    t->add_confidence("De01",2,a,b+1);
    confidence+=2;
  }

  return 1;
}

int Pronoun::advanced(Text *t, int a, int b, int c) {
  if (t->is_category_non_recursive("Opening",a,b+1) == 1 || t->is_category_non_recursive("De01",a,b+1) == 1) {
    set_possessive(1);
    t->make_only(a,b,this);
  }
  if (t->is_only_category_non_recursive("Noun",a,b+1) == 1) {
    set_possessive(1);
    t->make_only(a,b,this);
  }
  if (t->is_category_non_recursive("Adjective",a,b+1) == 1 && t->is_category_non_recursive("Verb",a,b+1) != 1) {
  if (t->is_category_non_recursive("Cadverb",a,b+1) != 1 && t->is_category_non_recursive("Noun",a,b+2) == 1) {
      set_possessive(1);
      t->make_only(a,b,this);
    }
  }
  return 1;
}

std::string Pronoun::make_possessive(std::string x) {

  if (x == "I") { return "my"; }
  if (x == "you") { return "your"; }
  if (x == "he") { return "his"; }
  if (x == "she") { return "her"; }
  if (x == "it") { return "its"; }
  if (x == "we") { return "our"; }
  if (x == "they") { return "their"; }

  return x;

}
