#include "place.h"
#include "text.h"


Place::Place(Text *t): ProperNoun(t) { myclass += ":Place"; };
Place::~Place() {}


int Place::combine(Text *t, int a, int b, int c) {

  int place_found = 0;
  if (t->return_chinese(a,b+1,0) == "南部") {
    shift_post_chinese(t,a,b+1,0,this);
    add_pre_english("the southern part of");
    t->make_only(a,b,this);
    place_found = 1;
  }
  if (t->return_chinese(a,b+1,0) == "西部") {
    shift_post_chinese(t,a,b+1,0,this);
    add_pre_english("the western part of");
    t->make_only(a,b,this);
    place_found = 1;
  }
  if (t->return_chinese(a,b+1,0) == "东部") {
    shift_post_chinese(t,a,b+1,0,this);
    add_pre_english("the eastern part of");
    t->make_only(a,b,this);
    place_found = 1;
  }
  if (t->return_chinese(a,b+1,0) == "北部") {
    shift_post_chinese(t,a,b+1,0,this);
    add_pre_english("the northern part of");
    t->make_only(a,b,this);
    place_found = 1;
  }
  if (place_found == 1) {
    if (t->is_category_non_recursive("Place",a,b+1) == 1) {
    } else {
      if (t->is_category_non_recursive("Punctuation",a,b+2) == 1 && t->is_category_non_recursive("Noun",a,b+1) == 1) {
        add_pre_english("in");
        add_pre_english(t->text(a,b+1,"Noun")->return_english());
        shift_post_chinese(t,a,b+1,0,this);
        t->make_only(a,b,this);
      }
    }
  }

  return 1;
}


