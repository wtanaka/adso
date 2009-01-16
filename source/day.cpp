#include "day.h"
#include "text.h"
#include "date.h"

Day::Day(Text *t, Text *a, Text *b): Date(t, a, b) { 
	myclass += ":Day";
	integer_representation = a->integer_representation;
	english = return_day(integer_representation);
};
Day::Day(Text *t): Date(t) { myclass += ":Day";};
Day::~Day() {}

int Day::combine(Text *parent, int a, int b, int c) {


	if (parent->return_chinese(a,b+1) == "晚") {
		add_pre_english("the evening of the");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "晨") {
		add_post_english(" in the morning");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}	
	if (parent->return_chinese(a,b+1) == "一早") {
		add_post_english(" early in the morning");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}	
	if (parent->return_chinese(a,b+1) == "早上") {
		add_post_english(" in the morning");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}	

	if (parent->return_chinese(a,b+1) == "下午") {
		add_post_english(" in the afternoon");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}	

	if (parent->return_chinese(a,b+1) == "上午") {
		add_post_english(" in the morning");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}	

	if (parent->return_chinese(a,b+1) == "晚") {
		add_post_english(" in the evening");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}	
	if (parent->return_chinese(a,b+1) == "晚间") {
		add_pre_english("in the evening of the");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "晚上") {
		add_post_english(" in the evening");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}	

	if (parent->return_chinese(a,b+1) == "晨") {
		add_post_english(" in the morning");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "凌晨") {
		add_post_english(" early in the morning");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "凌晨") {
		add_post_english(" early in the morning");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "中午") {
		add_post_english(" around midday");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "本月") {
		add_post_english(" this month");
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "当月") {
		add_pre_english("the ");
		add_post_english(" of that month");
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "当地时间") {
		add_post_english(" at localtime");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}

	if (parent->is_category_non_recursive("Day",a,b+2) == 1 && parent->is_category_non_recursive("He01",a,b+1) == 1) {
		parent->text(a,b+2,"Day")->combine(parent,a,b+2,0);
		add_post_english(" and ");
		add_post_english(parent->text(a,b+2,"Day")->return_english_no_spacing());
		shift_post_chinese(parent,a,b+1,0,this);
		shift_post_chinese(parent,a,b+1,0,this);
		myclass += ":Range";
		parent->make_only(a,b,this);
	}

	Date::combine(parent,a,b,c);
	return 1;
}



std::string Day::return_day(int x) {

	if (x == 1)  { return "1st"; }
	if (x == 2)  { return "2nd"; }
	if (x == 3)  { return "3rd"; }
	if (x == 4)  { return "4th"; }
	if (x == 5)  { return "5th"; }
	if (x == 6)  { return "6th"; }
	if (x == 7)  { return "7th"; }
	if (x == 8)  { return "8th"; }
	if (x == 9)  { return "9th"; }
	if (x == 10) { return "10th"; }
	if (x == 11) { return "11th"; }
	if (x == 12) { return "12th"; }
	if (x == 13) { return "13th"; }
	if (x == 14) { return "14th"; }
	if (x == 15) { return "15th"; }
	if (x == 16) { return "16th"; }
	if (x == 17) { return "17th"; }
	if (x == 18) { return "18th"; }
	if (x == 19) { return "19th"; }
	if (x == 20) { return "20th"; }
	if (x == 21) { return "21st"; }
	if (x == 22) { return "22nd"; }
	if (x == 23) { return "23rd"; }
	if (x == 24) { return "24th"; }
	if (x == 25) { return "25th"; }
	if (x == 26) { return "26th"; }
	if (x == 27) { return "27th"; }
	if (x == 28) { return "28th"; }
	if (x == 29) { return "29th"; }
	if (x == 30) { return "30th"; }
	if (x == 31) { return "31st"; }

	return "";
}


