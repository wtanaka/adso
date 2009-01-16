#include "year.h"
#include "date.h"
#include "text.h"


Year::Year(Text *t, Text *a, Text *b): Date(t, a, b) { 
	myclass += ":Year";
	integer_representation = a->integer_representation;
	english = a->return_english();
};
Year::Year(Text *t): Date(t) { myclass += ":Year";};
Year::~Year() {}


int Year::combine(Text *x, int a, int b, int c) {

  if (x->return_chinese(a,b+1,0) == "µ½" && x->is_category_non_recursive("Year",a,b+2) == 1) {
	add_post_english("to");
	add_post_english(x->text(a,b+2,"Year")->return_english());
	shift_post_chinese(x,a,b+1,0,this);
	shift_post_chinese(x,a,b+1,"Year",this);
	myclass += ":Range";
	if (x->return_chinese(a,b-1,0) == "´Ó") {
		shift_pre_chinese(x,a,b-1,0,this);
		b--;
		add_pre_english("from");
	}
	x->make_only(a,b,this);
	add_pre_english("from");
  }

  if (x->return_chinese(a,b+1,0) == "ËêÄ©") {
    add_pre_english("at the end of");
    shift_post_chinese(x,a,b+1,0,this);
    x->make_only(a,b,this);
  }

  return 1;
}

