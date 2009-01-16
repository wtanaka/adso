#include "roman.h"
#include "unit.h"
#include "text.h"


Roman::Roman(Text *t): Unit(t) { myclass += ":Roman";};
Roman::~Roman() {}

int Roman::pre_unify(Text *parent, int a, int b, int c) {

  while (parent->is_category_non_recursive("Roman", a, b+1) == 1) {
    add_post_english(parent->text(a,b+1,"Roman")->return_english_no_spacing());
    shift_post_chinese(parent, a, b+1, "Roman", this);
  }

}

