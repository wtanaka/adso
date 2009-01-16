#include "month.h"
#include "date.h"
#include "text.h"
#include "number.h"
#include "day.h"

Month::Month(Text *t): Date(t) { myclass += ":Month";};
Month::Month(Text *t, Text *a, Text *b): Date(t, a, b) { 
	myclass += ":Month";
	integer_representation = a->integer_representation;
	english = return_month(integer_representation);
};
Month::~Month() {}


std::string Month::return_month(int x) {

	std::string english2 = "";

	if (x == 1) { english2 = "January"; }
	if (x == 2) { english2 = "February"; }
	if (x == 3) { english2 = "March"; }
	if (x == 4) { english2 = "April"; }
	if (x == 5) { english2 = "May"; }
	if (x == 6) { english2 = "June"; }
	if (x == 7) { english2 = "July"; }
	if (x == 8) { english2 = "August"; }
	if (x == 9) { english2 = "September"; }
	if (x == 10) { english2 = "October"; }
	if (x == 11) { english2 = "November"; }
	if (x == 12) { english2 = "December"; }
	if (x < 1 || x > 12) {
		throw "Error initializing month";
	}
	return english2;
}


int Month::combine(Text *parent, int a, int b, int c) {


	// Eliminate Spacing if Poor
	if (parent->is_category_non_recursive("Day",a,b+2) == 1) {
		if (parent->return_chinese(a,b+1,0) == " ") {
			parent->remove_element(a,b+1);
		}
	}


	// Month, Day, (Year)
	if (parent->is_category_non_recursive("Day",a,b+1) == 1) {
		parent->text(a,b+1,"Day")->combine(parent,a,b+1,0);
		add_post_english(" " + parent->text(a,b+1,"Day")->return_english());
		shift_post_chinese(parent,a,b+1,"Day",this);
		myclass += ":Day";
		parent->make_only(a,b,this);
	}



	// Day, Month, (Year)
	if (parent->is_category_non_recursive("Day",a,b-1) == 1) {
		add_pre_english(parent->text(a,b-1,"Day")->return_english());
		shift_pre_chinese(parent,a,b-1,"Day",this); b--;
		myclass += ":Day";
		parent->make_only(a,b,this);
	}



	// Month, Year
	if (parent->is_category_non_recursive("Year",a,b+1) == 1) {
		parent->text(a,b+1,"Year")->combine(parent,a,b+1,0);
		add_post_english(parent->text(a,b+1,"Year")->return_english());
		shift_post_chinese(parent,a,b+1,"Year",this);
		parent->make_only(a,b,this);
		myclass += ":Year";
	}
	// Year, Month
	if (parent->is_category_non_recursive("Year",a,b-1) == 1) {
		add_post_english(" " + parent->text(a,b-1,"Year")->return_english());
		shift_pre_chinese(parent,a,b-1,"Year",this); b--;
		parent->make_only(a,b,this);
		myclass += ":Year";
	}











	// Common Occurrences
	if (parent->return_chinese(a,b+1) == "上旬") {
		add_post_english(" the first third of");
		shift_post_chinese(parent,a,b+1,0,this);
		if (parent->return_chinese(a,b-1) == "今年") {
			add_post_english(" this year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "去年") {
			add_post_english(" last year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "明年") {
			add_post_english(" next year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "底") {
		add_pre_english("the end of");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "初") {
		add_pre_english("the beginning of");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "中旬") {
		add_post_english(" the middle of");
		shift_post_chinese(parent,a,b+1,0,this);
		if (parent->return_chinese(a,b-1) == "今年") {
			add_post_english(" this year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "去年") {
			add_post_english(" last year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "明年") {
			add_post_english(" next year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "下旬") {
		add_post_english(" the last third of");
		shift_post_chinese(parent,a,b+1,0,this);
		if (parent->return_chinese(a,b-1) == "今年") {
			add_post_english(" this year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "去年") {
			add_post_english(" last year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "明年") {
			add_post_english(" next year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "初") {
		if (parent->is_category_non_recursive("Number",a,b+2) != 1) {
			add_post_english(" the beginning of");
			shift_post_chinese(parent,a,b+1,0,this);
			if (parent->return_chinese(a,b-1) == "今年") {
				add_post_english(" this year");
				shift_pre_chinese(parent,a,b-1,0,this); b--;
			}
			if (parent->return_chinese(a,b-1) == "去年") {
				add_post_english(" last year");
				shift_pre_chinese(parent,a,b-1,0,this); b--;
			}
			if (parent->return_chinese(a,b-1) == "明年") {
				add_post_english(" next year");
				shift_pre_chinese(parent,a,b-1,0,this); b--;
			}
			parent->make_only(a,b,this);
		}
	}
	if (parent->return_chinese(a,b+1) == "中") {
		add_post_english(" the middle of");
		shift_post_chinese(parent,a,b+1,0,this);
		if (parent->return_chinese(a,b-1) == "今年") {
			add_post_english(" this year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "去年") {
			add_post_english(" last year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "明年") {
			add_post_english(" next year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "底") {
		add_post_english(" the end of");
		shift_post_chinese(parent,a,b+1,0,this);
		if (parent->return_chinese(a,b-1) == "今年") {
			add_post_english(" this year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "去年") {
			add_post_english(" last year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		if (parent->return_chinese(a,b-1) == "明年") {
			add_post_english(" next year");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		parent->make_only(a,b,this);
	}

	if (parent->return_chinese(a,b-1) == "去年") {
		add_post_english(" last year");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		parent->make_only(a,b,this);
	}

	if (parent->return_chinese(a,b-1) == "今年") {
		add_pre_english("this ");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		parent->make_only(a,b,this);
	}

	if (parent->return_chinese(a,b-1) == "明年") {
		add_pre_english("next ");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		parent->make_only(a,b,this);
	}



	// News Bylines
	if (parent->return_chinese(a,b+1) == "电") {
		add_pre_english("filed on ");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
		myclass += ":NewsFilingDate";
	}
	if (parent->return_chinese(a,b-1) == "继") {
		add_pre_english("following ");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		parent->make_only(a,b,this);
	}







	// Phrase Functions
	if (parent->return_chinese(a,b-1) == "从" && parent->return_chinese(a,b+1) == "到") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		shift_post_chinese(parent,a,b+1,0,this);
		add_pre_english("from ");
		add_post_english(" to");
		myclass += ":Phrase";
		parent->make_only(a,b,this);
	}
	if (parent->is_category_non_recursive("Number",a,b-2) == 1 && parent->is_category_non_recursive("Dash",a,b-1) == 1 && parent->is_category_non_recursive("Day",a,b) == 1) {
		if (pre_english != NULL) {
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		} else {
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			shift_pre_chinese(parent,a,b-1,0,this); b--;
		}
		parent->make_only(a,b,this);
	}




	if (parent->return_chinese(a,b-1) == "去年") {
		add_post_english(" last year");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "上午") {
		add_post_english(" in the morning");
		shift_post_chinese(parent,a,b+1,0,this); 
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "晚上") {
		add_post_english(" in the evening");
		shift_post_chinese(parent,a,b+1,0,this); 
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "晚") {
		add_pre_english("late ");
		shift_post_chinese(parent,a,b+1,0,this); 
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "从" && parent->return_chinese(a,b+1) == "以来") {
		add_pre_english(" since");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "自" && parent->return_chinese(a,b+1) == "以来") {
		add_pre_english(" since");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "到来之际"){
		add_pre_english(" on the cusp of");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}






	if (parent->is_category_non_recursive("Time",a,b+1) == 1) {
		add_post_english(" at");
		parent->text(a,b+1,"Time")->combine(parent,a,b+1,0);
		add_post_english(parent->text(a,b+1,"Time")->return_english());
		myclass += ":"+parent->text(a,b+1,"Time")->myclass;
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}







	if (parent->return_chinese(a,b+1) == "开始" && (parent->is_category_non_recursive("Verb",a,b+1) != 1 || (parent->is_category_non_recursive("Adverb",a,b+1) != 1 && parent->is_category_non_recursive("Verb",a,b+2) != 1))) {
		if (parent->is_category_non_recursive("Auxiliary", a,b-1) != 1){
			add_pre_english("the beginning of");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			parent->make_only(a,b,this);
		}
	}


	// Start of a Month
	if (parent->return_chinese(a,b+1) == "初") {
		if (parent->is_category_non_recursive("Number",a,b+2) == 1) {
			Number *num = (Number *) parent->text(a,b+2,"Number");
			if (num->integer_representation > 0 && num->integer_representation < 10) {
				add_post_english(num->return_english());
				shift_post_chinese(parent,a,b+1,0,this);
				shift_post_chinese(parent,a,b+1,0,this);
				parent->make_only(a,b,this);
			}
		}
	}






	// Actually a time
	if (parent->return_chinese(a,b+1) == "来") {
		myclass += ":Time";
		shift_post_chinese(parent,a,b+1,0,this);
		add_pre_english("since");
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "以来") {
		myclass += ":Time";
		shift_post_chinese(parent,a,b+1,0,this);
		add_pre_english("since");
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "最快") {
		myclass += ":Time";
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_pre_english("as soon as");
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "最慢") {
		myclass += ":Time";
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_pre_english("as late as");
		parent->make_only(a,b,this);
	}

	if (parent->return_chinese(a,b-1) == "底") {
		myclass += ":Time";
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_pre_english("late");
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "初") {
		myclass += ":Time";
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_pre_english("early");
		parent->make_only(a,b,this);
	}

	return 1;
}


