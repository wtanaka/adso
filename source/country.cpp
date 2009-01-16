#include "country.h"
#include "text.h"
#include "noun.h"
#include "encoding.h"

Country::Country(Text *t): Place(t) { 
	myclass += ":Country"; 
};
Country::~Country() {}



int Country::adjust_confidence(Text *t, int a, int b, int c) {

        if (t->is_category_non_recursive("Country",a,b-1) == 1) {
  		if (encoding->character_length(t->text(a,b-1,0)->return_chinese_input_encoding()) == 1 && encoding->character_length(return_chinese_input_encoding()) == 1) {
                        t->add_confidence("Country",2,a,b-1);
                        t->add_confidence("Country",2,a,b);
			t->make_only(a,b,this);
			t->make_only(a,b-1,"Country");
			possessive = 1;
                }
        }

        if (t->is_category("Preposition",a,b-1) == 1) {
                t->add_confidence("Country",2,a,b);
        }

	return 1;

}
int Country::advanced(Text *t, int a, int b, int c) {

  if (encoding->character_length(return_chinese_input_encoding()) > 1) {
    t->make_only(a,b,this);
  }

  if (t->is_category_non_recursive("De01",a,b+1) == 1) {
    possessive = 1;
  }
  if (t->is_category_non_recursive("City",a,b+1) == 1) {
    add_pre_english(", ");
    add_pre_english(t->text(a,b+1,"City")->return_english());
    shift_post_chinese(t,a,b+1,"City",this);
    t->make_only(a,b,this);
    myclass+=":City";
  }

  return 1;
}
