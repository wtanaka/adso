#include "hour.h"
#include "adsotime.h"
#include "text.h"
#include <sstream>


std::string Hour::itoa(int x) {
        std::stringstream myStream1;
        myStream1 << x;
        return myStream1.str();
}

Hour::Hour(Text *t, Text *a, Text *b): Time(t,a,b) { 
	myclass += ":Hour";
	integer_representation = a->integer_representation;
	english = itoa(integer_representation) + " o'clock";
};
Hour::Hour(Text *t): Time(t) { myclass += ":Hour";};
Hour::~Hour() {}

int Hour::combine(Text *t, int a, int b, int c) {

  if (t->is_category_non_recursive("Number",a,b+1) == 1) {
    if (t->return_chinese(a,b+2) == "·Ö") {
      myclass += ":Minute";
      english = itoa(integer_representation) + ":" + itoa(   t->text(a,b+1,"Number")->integer_representation   );
      shift_post_chinese(t,a,b+1,0,this);
      shift_post_chinese(t,a,b+1,0,this);
      t->make_only(a,b,this);
    }
  }

  return 1;
}

