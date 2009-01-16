#include "noun.h"
#include "text.h"
#include "encoding.h"


Noun::Noun(Text *t): Unit(t) { myclass += ":Noun";};
Noun::~Noun() {}

int Noun::combine(Text *t, int a, int b, int c) {


  if (t->is_category_non_recursive("Noun", a, b+1) == 1) {
    if (t->elements->at(a)->at(b)->size() == 1 && t->elements->at(a)->at(b+1)->size() == 1
      && t->is_category_non_recursive("Person",a,b+1) != 1 && t->is_category_non_recursive("Person",a,b) != 1
      && encoding->character_length(return_chinese_input_encoding()) > 1)
    {

      // Two Nouns with a single definition. Unify for Analytic convenience.
      add_post_english(" " + t->elements->at(a)->at(b+1)->at(0)->return_english());
      shift_post_chinese(t,a,b+1,0,this);
      t->make_only(a,b,this);
      
    }
  }


  if (t->is_category_non_recursive("Preposition",a,b+1) == 1 && t->is_category_non_recursive("Punctuation",a,b-1) == 1) {
    confidence+=3;
  }


  if (t->is_category_non_recursive("Adjective", a, b-1) == 1) {
    if (t->is_category_non_recursive("Noun", a, b-1) == 1) {
      if (
t->is_category_non_recursive("Directional", a, b-1) != 1 && 
t->is_category_non_recursive("Special", a, b-1) != 1 && 
t->is_category_non_recursive("Temporal", a, b-1) != 1 && 
t->is_category_non_recursive("Country", a, b-1) != 1
) {	
        t->text(a,b-1,"Adjective")->confidence+=3;
        confidence++;
      }
    }
  }

  if (t->is_category_non_recursive("De01", a, b-1) == 1) {
    confidence += 1;
    if (t->is_category_non_recursive("Adjective",a,b-2) == 1) {
      t->add_confidence("Adjective",2,a,b-2);
    }
  }

  if (t->is_category_non_recursive("Zhi02", a, b+1) == 1) {
    confidence += 1;
    if (t->is_category_non_recursive("Noun",a,b+2) == 1) {
      t->make_only(a,b,this);
      t->make_only(a,b+1,"Zhi02");
      t->make_only(a,b+2,"Noun");
    }
  }

  if (t->is_category_non_recursive("Number", a, b-3) == 1 &&
      t->is_category_non_recursive("Organization", a, b-2) == 1 &&
      t->is_category_non_recursive("PreNoun", a, b-1) == 1) {
 
       // Two Nouns with a single definition. Unify for Analytic convenience.
        add_pre_english(t->text(a,b-1,"PreNoun")->return_english());
        add_post_english("of the");
        add_post_english(t->text(a,b-3,"Number")->return_english());
        add_post_english(t->text(a,b-2,"Noun")->return_english());
        shift_pre_chinese(t,a,b-1,0,this);
	b--;
        shift_pre_chinese(t,a,b-1,0,this);
	b--;
        shift_pre_chinese(t,a,b-1,0,this);
	b--;
        t->make_only(a,b,this);
	myclass += ":Meeting";
  }

  if (t->return_chinese(a,b+1,0) == "好坏") {
    add_pre_english("the strengths and weaknesses of");
    shift_post_chinese(t,a,b+1,0,this);
    t->make_only(a,b,this);
  }


  if (t->is_category_non_recursive("De01",a,b-1) == 1 && t->return_chinese(a,b-2) == "所有") {
    shift_pre_chinese(t,a,b-1,0,this); b--;
    shift_pre_chinese(t,a,b-1,0,this); b--;
    add_pre_english("all");
    plural = 1;
    t->make_only(a,b,this);
    if (t->return_chinese(a,b+1) == "都") {
      for (int i = 0; i < t->elements->at(a)->at(b+1)->size(); i++) {
        t->elements->at(a)->at(b+1)->at(i)->should_translate = 0;
      }
    }
  }


  if (t->is_category_non_recursive("De01",a,b-1) == 1 && t->is_category_non_recursive("Adjective",a,b-2) == 1 && t->return_chinese(a,b-3) == "所有") {
    add_pre_english("all");
    add_pre_english(t->text(a,b-2,"Adjective")->return_english());
    shift_pre_chinese(t,a,b-1,0,this); b--;
    shift_pre_chinese(t,a,b-1,0,this); b--;
    shift_pre_chinese(t,a,b-1,0,this); b--;
    plural = 1;
    t->make_only(a,b,this);
    if (t->return_chinese(a,b+1) == "都") {
      for (int i = 0; i < t->elements->at(a)->at(b+1)->size(); i++) {
        t->elements->at(a)->at(b+1)->at(i)->should_translate = 0;
      }
    }
  }


  // Evaluation of Possessive Compounds
  if (t->encoding->character_length(return_chinese_input_encoding()) >= 3) {
    if (t->is_category_non_recursive("De01",a,b+1) == 1) {
      possessive = 1;
    }
  }


  if (t->is_category_non_recursive("De01",a,b-1) == 1 && t->is_category_non_recursive("Noun",a,b-2) == 1 && t->return_chinese(a,b-3) == "所有") {
    t->text(a,b-2,"Noun")->possessive = 1;
    t->text(a,b-2,"Noun")->plural = 0;
    add_pre_english(t->text(a,b-2,"Noun")->return_english());
    add_pre_english("all");
    shift_pre_chinese(t,a,b-1,0,this); b--;
    shift_pre_chinese(t,a,b-1,0,this); b--;
    shift_pre_chinese(t,a,b-1,0,this); b--;
    t->make_only(a,b,this);
    if (t->return_chinese(a,b+1) == "都") {
      for (int i = 0; i < t->elements->at(a)->at(b+1)->size(); i++) {
        t->elements->at(a)->at(b+1)->at(i)->should_translate = 0;
      }
    }
  }


  return 1;
}
