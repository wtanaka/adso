#include "date.h"
#include "text.h"
#include "unit.h"

Date::Date(Text *t): Unit(t) { myclass += ":Date"; };
Date::Date(Text *t, Text *a, Text *b): Unit(t, a, b) { myclass += ":Date"; };
Date::~Date() {}




int Date::combine2(Text *t, int a, int b, int c) {


	if (t->is_category_non_recursive("Yu01",a,b-1) == 1) {
		if (myclass.find("Day") != std::string::npos) { add_pre_english("on"); }
		else { add_pre_english("in"); }
		shift_pre_chinese(t,a,b-1,0,this); b--;
		t->make_only(a,b,this);
		if (t->is_category_non_recursive("Conjunction",a,b-1) == 1) {
			t->add_confidence("Conjunction",2,a,b-1);
		}
	}


	if (t->return_chinese(a,b+1) == "至") {
		if (t->is_category_non_recursive("Date",a,b+2) == 1) {
			add_post_english("through");
			myclass+=":Range";
			shift_post_chinese(t,a,b+1,0,this);
			add_post_english(t->text(a,b+1,"Date")->return_english());
			shift_post_chinese(t,a,b+1,"Date",this);
			t->make_only(a,b,this);
		}
		if (t->return_chinese(a,b-1,0) == "在") {
			t->make_only(a,b-1,0);
			t->text(a,b-1,0)->english = "from";
		}
	}
	if (t->return_chinese(a,b+1) == "以来") {
		add_pre_english("ever since");
		myclass+=":Range";
		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);
	}
	if (t->return_chinese(a,b-1) == "截至") {
		add_pre_english("up until");
		myclass+=":Range";
		shift_pre_chinese(t,a,b-1,0,this); b--;
		t->make_only(a,b,this);
	}

	if (t->return_chinese(a,b+1) == "夏季") {
		add_post_english("in the summer");
		myclass+=":Season";
		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);
	}
	if (t->return_chinese(a,b+1) == "秋季") {
		add_post_english("in the autumn");
		myclass+=":Season";
		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);
	}
	if (t->return_chinese(a,b+1) == "春季") {
		add_post_english("in the spring");
		myclass+=":Season";
		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);
	}
	if (t->return_chinese(a,b+1) == "冬季") {
		add_post_english("in the winter");
		myclass+=":Season";
		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);
	}

	if (t->return_chinese(a,b+1) == "起") {
	        if (myclass.find("Day") != std::string::npos) {
			if (myclass.find("Month") != std::string::npos) {
				add_pre_english("starting on");
			} else {
				add_pre_english("starting on the");
			}
		} else {
                	if (myclass.find("Month") != std::string::npos) {
				add_pre_english("starting in ");
			}
		}

		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);

		if (t->return_chinese(a,b-1) == "自") {
		  shift_pre_chinese(t,a,b-1,0,this);
		  b--;
		}
	}

	// This doesn't really belong in this function, but we should give
	// a default boost to verbs that follow dates, as in most cases
	// this will result in better default performance.
	t->add_confidence("Verb",3,a,b+1);
	t->add_confidence("Auxiliary",4,a,b+1);
	t->add_confidence("Adverb",3,a,b+1);

	return 1;
}

