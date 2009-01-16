#include "number.h"
#include "text.h"
#include <sstream>
#include <stdio.h>
#include "month.h"
#include "day.h"
#include "year.h"
#include "hour.h"
#include "minute.h"
#include "second.h"
#include "adverb.h"

Number::Number(Text *text) : Unit(text) {
	myclass += ":Number";
	whole_number = 0;
	decimal_number = 0;
	full_number = 0;
	starts_with_zero = 0;
	plural_next = 0;
	following_pinyin = "";
}
Number::~Number() {}

std::string Number::return_pinyin() {

  std::string temp_pinyin = pinyin;
  if (pre_chinese != NULL) { temp_pinyin  = pre_chinese->return_pinyin() + pinyin; }
  if (post_chinese != NULL) { temp_pinyin = pinyin + post_chinese->return_pinyin(); }

  if (post_pinyin_spacing == 1) { return temp_pinyin + " "; }
  return temp_pinyin;

}
std::string Number::return_pinyin_no_spacing() {

  std::string temp_pinyin = pinyin;
  if (pre_chinese != NULL) { temp_pinyin  = pre_chinese->return_pinyin() + pinyin; }
  if (post_chinese != NULL) { temp_pinyin = pinyin + post_chinese->return_pinyin(); }

  return pinyin;

}
int Number::adjust_confidence(Text *parent, int a, int b, int c) {

  if (parent->is_category_non_recursive("Verb",a,b-1) == 1) { 
    parent->add_confidence("Verb",1,a,b-1);
  }

  return 1;

}
int Number::pre_unify(Text *parent, int a, int b, int c) {

  if (parent->return_chinese(b+1) == "多" || parent->return_chinese(b+1) == "余" || parent->return_chinese(b+1) == "逾") {
    add_pre_english("more than");
    shift_post_chinese(parent, a, b+1, 0, this);
    parent->make_only(a, b, this);
  }

  if (convert2number(chinese) == 0) { starts_with_zero = 1; }

  while (parent->is_category_non_recursive("Number", a, b+1) == 1) {
    /* We automatically generate the pinyin below, so we set the pinyin of 
     * any but the first number to "" when we add it to post_character. This 
     * ensures that when we automatically generate the pinyin (return_pinyin) 
     * we end up with something usable, and can iterate past these numbers 
     * and still get the pinyin of characters added at the end. See return_pinyin()
     * if there is any confusion.
     */
    parent->text(a, b+1, 0)->pinyin = "";
    shift_post_chinese(parent, a, b+1, "Number", this);
  }

  return 1;

}

int Number::unify(Text *parent, int a, int b, int c) {


     // Decimal Unification with NonChinese Punctuation
     if (parent->is_category_non_recursive("Number",a,b+1) == 1 &&
         parent->is_category_non_recursive("Period",a,b+1) == 1
     ) {
	shift_post_chinese(parent, a, b+1, 0, this);
	parent->make_only(a,b,this);
     }





    // Avoid Problems which Interfere with Unification
    if (parent->return_chinese(b+1) == " ") { 
      parent->make_only(a, b, this);
      parent->remove_element(a,b+1);
    }

        // Avoid Problems which Interfere with Unification
        if (parent->return_chinese(b+1) == "多" || parent->return_chinese(b+1) == "余" || parent->return_chinese(b+1) == "逾") {
          add_pre_english("more than");
          shift_post_chinese(parent, a, b+1, 0, this);
	  while (parent->is_category_non_recursive("Number",a,b+1) == 1){
    	    shift_post_chinese(parent, a, b+1, "Number", this);
	  }
          parent->make_only(a, b, this);

        }




	// Decimal Number
	if ((parent->return_chinese(b+1) == "点") && parent->is_category_non_recursive("Number", a, b+2) == 1) {
		parent->text(a, b+1, 0)->pinyin = "dian3";
		shift_post_chinese(parent, a, b+1, 0, this);
		while (parent->is_category_non_recursive("Number", a, b+1) == 1) {
			shift_post_chinese(parent, a, b+1, 0, this);
		}
		parent->make_only(a, b, this);
	}
	else {
	if ((parent->return_chinese(b+1) == "．" || parent->return_chinese(b+1) == ".") && parent->is_category_non_recursive("Number", a, b+2) == 1) {
		parent->text(a, b+1, 0)->pinyin = "dian3";
		shift_post_chinese(parent, a, b+1, 0, this);
		while (parent->is_category_non_recursive("Number", a, b+1) == 1) {
			shift_post_chinese(parent, a, b+1, 0, this);
		}
		parent->make_only(a, b, this);
	}
	}



	generate_numbers();
	if (decimal_number != 0) { plural_next = 1; };
	if (whole_number > 1) { plural_next = 1; };



	// Now Generate the Pinyin
	pinyin = generate_complex_pinyin(whole_number);

	if (following_pinyin == "shi2 yi4") { whole_number *= 10; following_pinyin = "yi4"; }
	if (decimal_number != 0) {
		std::string decimal_as_string = return_english();
		if (decimal_as_string.find(".") != std::string::npos) {
			decimal_as_string = decimal_as_string.substr(decimal_as_string.find(".")+1);
			pinyin += " dian3 ";
			pinyin += generate_complex_pinyin(atoi(decimal_as_string.c_str()));
		}
	}
	if (following_pinyin != "") { pinyin += following_pinyin; }



	return 1;

}

int Number::post_unify(Text *parent, int a, int b, int c) {



	//... measurements
	if (parent->is_category_non_recursive("Mment", a, b+1) == 1) {
    		add_post_english(" " + parent->text(a,b+1,"Mment")->return_english_no_spacing());
    		shift_post_chinese(parent, a, b+1, "Mment", this);   
 		parent->make_only(a, b, this);
		myclass += "Mment";
	}
	//... and a half
	if (parent->is_category_non_recursive("Measure", a, b+1) == 1) {
		if (parent->return_chinese(b+2) == "半"){
    			add_post_english("and a half");
    			shift_post_chinese(parent, a, b+1, "Measure", this);
    			shift_post_chinese(parent, a, b+2, 0, this);
    			parent->make_only(a, b, this);
			decimal_representation += 0.5;
		}
	}

	// Shorthand for Age
	if (parent->return_chinese(b+1) == "的") {
		if (parent->return_chinese(b+2) == "人") {
			add_post_english(" years old");
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			if (parent->return_chinese(b-1) == "都") {
				if (shift_pre_chinese(parent, a, b-1, 0, this) == 1) { b--; }
				add_pre_english("is");
			}
			parent->make_only(a, b, this);
		}
	}



	// Floor
	if (parent->return_chinese(a,b+1) == "楼") {
		english = suffix(english);
		shift_post_chinese(parent, a, b+1, 0, this);
		add_post_english(" floor");
	}
	if (parent->return_chinese(a,b+1) == "倍") {
		plural_next = 0;
		add_post_english(" times");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "倍多") {
		plural_next = 0;
		add_pre_english("more than");
		add_post_english(" times");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "层") {
		english = suffix(english);
		add_post_english(" floor");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "多") {
		shift_post_chinese(parent, a,b+1,0,this);
		add_pre_english("more than ");
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(b+1) == "多年") {
		shift_post_chinese(parent, a,b+1,0,this);
		add_pre_english("more than ");
		add_post_english( "years");
		parent->make_only(a,b,this);
	}

	// Weeks
	if (parent->return_chinese(a, b+1, 0) == "周") {
		if (whole_number > 0 && whole_number < 20) {
			shift_post_chinese(parent, a, b+1, "Noun", this);
			add_post_english("weeks");

			if (parent->return_chinese(a, b+1, 0) == "来") {
				shift_post_chinese(parent, a, b+1, 0, this);
				add_pre_english("over the last");
				if (parent->return_chinese(a, b+1, 0) == "首次") {
					shift_post_chinese(parent, a, b+1, 0, this);
					add_pre_english("for the first time");
				}
			}
		}
	}



	// Months
	if (parent->return_chinese(b+1) == "月" || parent->return_chinese(b+1) == "月份") {
		if (parent->return_chinese(a, b+2) == "内") {
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			if (whole_number == 1) { add_post_english(" month"); }
			else { add_post_english(" months"); }
			add_pre_english("within ");
			parent->make_only(a, b, this);
			return 1;
		}
		if (parent->return_chinese(a, b+2) == "之内") {
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			if (whole_number == 1) { add_post_english(" month"); }
			else { add_post_english(" months"); }
			add_pre_english("within ");
			parent->make_only(a, b, this);
			return 1;
		}
		if (whole_number < 13) { 
			Month *temp = new Month(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			return 1;
		}
	}	
	if (parent->return_chinese(a, b+1) == "月份会议") {
		if (whole_number < 13) { 
			Month *temp = new Month(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			temp->add_post_english("meeting");
			return 1;
		}
	}


	// Days
	if (parent->return_chinese(a,b+1) == "日夜") {
		if (whole_number < 32) { 
			Day *temp = new Day(this, this, parent->elements->at(0)->at(b+1)->at(0));
			temp->add_pre_english("the evening of the");
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			if (parent->return_chinese(a,b+1) == "间") {
				shift_post_chinese(parent,a,b+1,0,temp);
			}
			return 1;
		}
	}
	if (parent->return_chinese(a, b+1) == "日") {
		if (whole_number < 32) { 
			Day *temp = new Day(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->remove_element(a, b+1);
			if (parent->is_category_non_recursive("Number",a,b-2) == 1 && parent->return_chinese(b-1) == "-") {
				Day *temp2 = new Day(parent);
				parent->text(a,b-2,"Number")->clone_values(temp2);
				parent->elements->at(a)->at(b-2)->push_back(temp2);
				parent->make_only(a, b-2, temp2);
				temp2->post_english_spacing = 0;
				temp2->post_pinyin_spacing = 0;
			}
			parent->make_only(a, b, temp);
			return 1;
		}
	}
	if (parent->return_chinese(a, b-1) == "初") {
		add_pre_english("the ");
		english = suffix(english);
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a, b+1) == "号") {
		if (whole_number < 32 && parent->is_category_non_recursive("Number", a, b-2) == 1) { 
			Day *temp = new Day(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			return 1;
		}
	}
	if (parent->return_chinese(a, b+1) == "日前") {
		if (whole_number < 32) { 
			Day *temp = new Day(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			add_pre_english("before the ");
			return 1;
		}
	}	
	// Avoid common confusion with "Daily Newspaper"
	if (parent->return_chinese(a, b+1) == "日报" || parent->return_chinese(a, b+1) == "日报道") {
		if (whole_number < 32) {
			parent->resegment(a, b+1, 1);
			Day *temp = new Day(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			return 1;
		}
	}	




	// Years
	// Obscure pairings sought first
	if (parent->return_chinese(a, b-1) == "民国" && parent->return_chinese(a, b+1) == "年") {
		if (whole_number < 300) {
			Year *temp = new Year(this, this, parent->elements->at(0)->at(b+1)->at(0));
			clone_values(temp);
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			return 1;
		}
	}
	// Shorthand References for 2001-2009
	if (starts_with_zero == 1 && whole_number < 9 && whole_number > 0) {
		if (parent->return_chinese(b+1) == "年") {
			whole_number += 2000;
			english = "200" + english;
			Year *temp = new Year(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			parent->remove_element(a, b+1);
			return 1;
		} else {
			Year *temp = new Year(this);
			clone_values(temp);
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->make_only(a, b, temp);
			temp->integer_representation = whole_number+2000;
			if (whole_number == 0) { temp->english = "2000"; }
			if (whole_number == 1) { temp->english = "2001"; }
			if (whole_number == 2) { temp->english = "2002"; }
			if (whole_number == 3) { temp->english = "2003"; }
			if (whole_number == 4) { temp->english = "2004"; }
			if (whole_number == 5) { temp->english = "2005"; }
			if (whole_number == 6) { temp->english = "2006"; }
			if (whole_number == 7) { temp->english = "2007"; }
			if (whole_number == 8) { temp->english = "2008"; }
			if (whole_number == 9) { temp->english = "2009"; }
			return 1;
		}
	}


	// Reference to Proximate Years
	if (parent->return_chinese(a, b+1) == "年" || parent->return_chinese(a, b+1) == "年度") {
		if (parent->return_chinese(a,b+3) == "来" && parent->return_chinese(a,b+2) == "多") {
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			add_pre_english("over more than the last ");
			if (whole_number == 1) { add_post_english(" year"); } 
			else { add_post_english(" years"); }
			parent->make_only(a,b, this);
			confidence += 10;
			plural_next = 0;
			parent->make_only(a,b,this);
			return 1;
		}
		if (parent->return_chinese(a,b+2) == "来"){
			if (parent->return_chinese(a, b+3) == "首次") {
				shift_post_chinese(parent, a, b+1, 0, this);
				shift_post_chinese(parent, a, b+1, 0, this);
				shift_post_chinese(parent, a, b+1, 0, this);
				add_pre_english("for the first time in ");
				if (whole_number == 1) { add_post_english(" year"); }
				else { add_post_english(" years"); }
				myclass += ":Time";
				parent->make_only(a,b, this);
				plural_next = 0;
				return 1;
			}
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			add_pre_english("in the last ");
			if (whole_number == 1) { add_post_english(" year"); }
			else { add_post_english(" years"); }
			confidence += 10;
			plural_next = 0;
			parent->make_only(a,b,this);
			return 1;
		}
		if (parent->return_chinese(a,b+2) == "之内") {
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			add_pre_english("within ");
			if (whole_number == 1) { add_post_english(" year"); }
			else { add_post_english(" years"); }
			plural_next = 0;
			myclass += ":Time";
			parent->make_only(a,b, this);
			return 1;
		}
		if (parent->return_chinese(a, b+2) == "内") {
			shift_post_chinese(parent, a, b+1, 0, this);
			shift_post_chinese(parent, a, b+1, 0, this);
			add_pre_english("within ");
			if (whole_number == 1) { add_post_english(" year"); }
			else { add_post_english(" years"); }
			plural_next = 0;
			myclass += ":Time";
			parent->make_only(a,b, this);
			plural_next = 0;
			return 1;
		}
		if (whole_number > 1800 && whole_number < 2200) {
			Year *temp = new Year(this, this, parent->elements->at(0)->at(b+1)->at(0));
			parent->elements->at(a)->at(b)->push_back(temp);
			parent->remove_element(a, b+1);
			temp->confidence+=10;
			parent->make_only(a,b,temp);
			return 1;
		}
		if (parent->return_chinese(a,b-1) == "在过去") {
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			shift_post_chinese(parent,a,b+1,0,this);
			add_pre_english("in the past ");
			if (whole_number == 1) { add_post_english(" year"); }
			else { add_post_english(" years"); }
			parent->make_only(a,b,this);
			myclass += ":Time:Range";
			return 1;
		}
		if (parent->return_chinese(a,b-1) == "在未来") {
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			shift_post_chinese(parent,a,b+1,0,this);
			add_pre_english("in the future ");
			if (whole_number == 1) { add_post_english(" year"); }
			else { add_post_english(" years"); }
			parent->make_only(a,b,this);
			myclass += ":Time:Range";
			return 1;
		}
	}
	if (whole_number > 1900 && whole_number < 2080) {
		Year *temp = new Year(this);
		clone_values(temp);
		parent->elements->at(a)->at(b)->push_back(temp);
		temp->confidence+=5;
		if (parent->return_chinese(a,b+1) == "年前") {
			shift_post_chinese(parent,a,b+1,0,temp);
			temp->add_pre_english("before the start of ");
			parent->make_only(a,b,temp);
			return 1;
		}
	}



	if (parent->return_chinese(b-1) == "为期" && parent->is_category("Noun",a,b+1) == 1) {
		plural_next = 0;
		add_post_english(parent->text(a,b+1,"Noun")->return_english_no_spacing() + "-long");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		shift_post_chinese(parent,a,b+1,0,this);
		myclass += ":Adjective";
		parent->make_only(a,b,this);
	}


	// Time with No Reference to Hours
	if (parent->is_category_non_recursive("Colon",a,b+1) == 1) {
		if (parent->is_category_non_recursive("Number",a,b+2) == 1) {
			if (whole_number < 25) {
				shift_post_chinese(parent, a, b+1, 0, this);
				add_post_english(":");
				add_post_english(parent->text(a,b+1,"Number")->return_english());
				shift_post_chinese(parent, a, b+1, 0, this);

				if (parent->is_category_non_recursive("Colon",a,b+1) == 1) {
					if (parent->is_category_non_recursive("Colon",a,b+1) == 1) {
						shift_post_chinese(parent, a, b+1, 0, this);
						add_post_english(":");
						add_post_english(parent->text(a,b+1,"Number")->return_english());
						shift_post_chinese(parent, a, b+1, 0, this);
					}
				}

				if (parent->return_chinese(a,b-1,0) == "下午") {
					shift_pre_chinese(parent, a, b-1, 0, this); b--;
					add_post_english(" in the afternoon");
				}
				if (parent->return_chinese(a,b-1,0) == "早上") {
					shift_pre_chinese(parent, a, b-1, 0, this); b--;
					add_post_english(" in the afternoon");
				}
				if (parent->return_chinese(a,b-1,0) == "晚上") {
					shift_pre_chinese(parent, a, b-1, 0, this); b--;
					add_post_english(" in the afternoon");
				} 
				if (parent->return_chinese(a,b-1,0) == "夜里") {
					shift_pre_chinese(parent, a, b-1, 0, this); b--;
					add_post_english(" in the afternoon");
				}

				parent->make_only(a,b,this);
				myclass += ":Time";

			}
		}
	}



	// Hours
	if (parent->return_chinese(a,b+1) == "时许") {
		Hour *temp = new Hour(this, this, parent->elements->at(0)->at(b+1)->at(0));
		parent->elements->at(a)->at(b)->push_back(temp);
		parent->make_only(a, b, temp);
		parent->remove_element(a, b+1);
		parent->add_post_english("or so");
		return 1;
	}
	if (whole_number > 0 && whole_number < 24 && (parent->return_chinese(a,b+1) == "时" || parent->return_chinese(a,b+1) == "点" || parent->return_chinese(a,b+1) == "点钟")) {
		Hour *temp = new Hour(this, this, parent->elements->at(0)->at(b+1)->at(0));
		parent->elements->at(a)->at(b)->push_back(temp);
		parent->make_only(a, b, temp);
		parent->remove_element(a, b+1);
		return 1;
	}
	if (whole_number < 0 && whole_number > 24 && (parent->return_chinese(a,b+1) == "点整")) {
		Hour *temp = new Hour(this, this, parent->elements->at(0)->at(b+1)->at(0));
		parent->elements->at(a)->at(b)->push_back(temp);
		parent->make_only(a, b, temp);
		parent->remove_element(a, b+1);
		temp->add_post_english("on the dot");
		return 1;
	}
	if (parent->return_chinese(a,b+1) == "小时") {
		if (whole_number > 1) {	add_post_english(" hours"); }
		if (whole_number == 1){	add_post_english(" hour");  }
		parent->make_only(a, b, this);
		shift_post_chinese(parent, a, b+1, 0, this);
		if (parent->return_chinese(a,b+1) == "后") {
			shift_post_chinese(parent,a,b+1,0,this);
			parent->make_only(a,b,this);
			add_pre_english("after");
		}
	}





	// Minutes
	if (parent->return_chinese(a,b+1) == "分") {
		if (parent->return_chinese(a,b+2) != "之") {
			Text *temp1 = new Text(this, parent->elements->at(0)->at(b+1)->at(0), parent->elements->at(0)->at(b+2)->at(0));
			Text *temp2 = new Minute(this, this, temp1);
			delete temp1;
			parent->elements->at(a)->at(b)->push_back(temp2);
			parent->make_only(a, b, temp2);
			parent->remove_element(a, b+1);
			parent->remove_element(a, b+1);
			return 1;
		}	
	}
	// Seconds, Minutes and Hours
	if (parent->return_chinese(a,b+1) == "分钟") {
		shift_post_chinese(parent,a,b+1,0,this);
		if (whole_number == 1) { add_post_english(" minute"); }
		if (whole_number > 1) { add_post_english(" minutes"); }
		myclass += ":Minutes";
		parent->make_only(a,b,this);
	}









	// Decades
	if (whole_number == 10 ||
	    whole_number == 20 ||
	    whole_number == 30 ||
	    whole_number == 40 ||
	    whole_number == 50 ||
	    whole_number == 60 ||
	    whole_number == 70 ||
	    whole_number == 80 ||
	    whole_number == 90) {
		if (parent->return_chinese(a,b+1) == "年代") {
			plural_next = 0;
			english += "s";
			shift_post_chinese(parent, a, b+1, 0, this);
			if (parent->return_chinese(a,b+1) == "中期") {
				add_pre_english("the middle of the");
				shift_post_chinese(parent, a, b+1, 0, this);
			}
			if (parent->return_chinese(a,b+1) == "初期") {
				add_pre_english("the beginning of the");
				shift_post_chinese(parent, a, b+1, 0, this);
			}
			if (parent->return_chinese(a,b+1) == "末") {
				add_pre_english("the end of the");
				shift_post_chinese(parent, a, b+1, 0, this);
			}
			if (parent->return_chinese(a,b-1) == "世纪") {
				add_post_english("of this century");
				shift_pre_chinese(parent, a, b-1, 0, this);
				b--;
				if (parent->return_chinese(a,b-1) == "本") {
					add_post_english("of this century");
					shift_pre_chinese(parent, a, b-1, 0, this);
					b--;
				}
			}
			if (parent->return_chinese(a,b-1) == "上世纪") {
				add_post_english("of the last century");
				shift_pre_chinese(parent, a, b-1, 0, this);
				b--;
			}
			if (parent->return_chinese(a,b-1) == "进入") {
				add_pre_english("entering");
				shift_pre_chinese(parent, a, b-1, 0, this);
				b--;
			}
			if (pre_english == NULL) {
				add_pre_english("in the ");
				if (
					parent->is_category_non_recursive("Comma",a,b-1) == 1 &&
					parent->is_category_non_recursive("Number",a,b-2) == 1
				) {
					int tempx = parent->text(a,b-2,"Number")->integer_representation;
					if (tempx < 10) {
						add_post_english(" and the decade before that");
						shift_pre_chinese(parent,a,b-1,0,this); b--;
						shift_pre_chinese(parent,a,b-1,0,this); b--;
						parent->make_only(a,b,this);
					}
				}
			}
			parent->make_only(a,b,this);
		}
	}











	// Number of Months
	if (whole_number < 13 && parent->is_category_non_recursive("Measure", a, b+1) == 1 && parent->return_chinese(a,b+2) == "月") {
		shift_post_chinese(parent, a, b+1, 0, this);
		shift_post_chinese(parent, a, b+1, 0, this);
		if (whole_number == 1) { add_post_english("month"); }
		else { add_post_english("months"); }

		if (parent->return_chinese(a,b+1) == "里") {
			shift_post_chinese(parent, a, b+1, 0, this);
			add_pre_english("within");
		}
			
		if (parent->return_chinese(a,b-1) == "前") { 
			shift_pre_chinese(parent, a, b-1, 0, this);
			b--;
			add_pre_english("the previous");
			if (parent->return_chinese(a, b-1) == "今年") {
				shift_pre_chinese(parent, a, b-1, 0, this);
				b--;
				add_post_english("of this year");
			}
		}
		if (parent->return_chinese(a,b+1) == "以前") { 
			shift_post_chinese(parent, a, b+1, 0, this);
			add_post_english("before");
		}
		if (parent->return_chinese(a,b+1) == "以后") {
			shift_post_chinese(parent, a, b+1, 0, this);
			add_post_english("after");
		}
		if (parent->return_chinese(a,b+1) == "之前") {
			shift_post_chinese(parent, a, b+1, 0, this);
			add_post_english("before");
		}
		if (parent->return_chinese(a,b+1) == "以后") {
			shift_post_chinese(parent, a, b+1, 0, this);
			add_post_english("after");
		}
		if (parent->return_chinese(a,b-1) == "头") {
			shift_pre_chinese(parent, a, b-1, 0, this);
			b--;
			add_pre_english("first");
		}
		parent->make_only(a,b,this);
	}










	if (parent->return_chinese(a,b-1) == "等") {
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		add_pre_english("and");
		add_post_english("other");
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "过去") {
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		add_pre_english("the past");
		parent->make_only(a,b,this);
	}




	// Repeated Numbers
	if (decimal_number == 0) {
		int rem = 0;
		int suspect = 0; 
		rem = (whole_number-89)%100; if (rem == 0) {  suspect = 1;  }
		rem = (whole_number-78)%100; if (rem == 0) {  suspect = 1;  }
		rem = (whole_number-67)%100; if (rem == 0) {  suspect = 1;  }
		rem = (whole_number-56)%100; if (rem == 0) {  suspect = 1;  }
		rem = (whole_number-45)%100; if (rem == 0) {  suspect = 1;  }
		rem = (whole_number-34)%100; if (rem == 0) {  suspect = 1;  }
		rem = (whole_number-23)%100; if (rem == 0) {  suspect = 1;  }
		rem = (whole_number-12)%100; if (rem == 0) {  suspect = 1;  }

		if (suspect == 1) {
			// Opens Can of Worms, But We Have Found Our Doubles
			// One and Two, Two or Three, Three or Four, etc.
		}
	}










	// Days and Months by reference to Numbers
	// GB2312 is used as return_chinese(), so a length of four implies a character value of 2 chars
	if ((whole_number < 100 && whole_number > 10) && return_chinese().length() == 4) {

		// GB2312 Specific
		std::string nword = return_chinese().substr(0, 2);
		std::string oword = return_chinese().substr(2);
		std::string possiblem = "";
		std::string possibled = "";

		if (parent->return_chinese(a,b+1) == "周年" || (parent->is_category_non_recursive("Punctuation",a,b-1) == 1 && parent->is_category_non_recursive("Punctuation",a,b+1) == 1)) {
			if (parent->return_chinese(a,b-1) == "月") {

				if (nword == "一") { possiblem = "January"; }
				if (nword == "二") { possiblem = "Februrary"; }
				if (nword == "三") { possiblem = "March"; }
				if (nword == "四") { possiblem = "April"; }
				if (nword == "五") { possiblem = "May"; }
				if (nword == "六") { possiblem = "June"; }
				if (nword == "七") { possiblem = "July"; }
				if (nword == "八") { possiblem = "August"; }
				if (nword == "九") { possiblem = "September"; }
				if (nword == "十") { possiblem = "October"; }

				if (oword == "一") { possibled = "1st"; }
				if (oword == "二") { possibled = "2nd"; }
				if (oword == "三") { possibled = "3rd"; }
				if (oword == "四") { possibled = "4th"; }
				if (oword == "五") { possibled = "5th"; }
				if (oword == "六") { possibled = "6th"; }
				if (oword == "七") { possibled = "7th"; }
				if (oword == "八") { possibled = "8th"; }
				if (oword == "九") { possibled = "9th"; }
				if (oword == "十") { possibled = "10th"; }
		
				if (possibled != "" && possiblem != "" && parent->is_category_non_recursive("Measure",a,b+1) != 1) {
					Date *temp = new Date(this);
					clone_values(temp);
					temp->english = possiblem + " " + possibled;
					temp->myclass += ":Month:Day";
					parent->elements->at(a)->at(b)->push_back(temp);
					parent->make_only(a,b,temp);
					return 1;
				}
			}
		}
	}
	if (parent->is_category_non_recursive("Dot",a,b+1) == 1 && parent->is_category_non_recursive("Number",a,b+2) == 1) {
		english = return_english_no_spacing() + "-" + parent->text(a,b+2,"Number")->return_english_no_spacing();
		shift_post_chinese(parent,a,b+1,0,this);
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
		plural_next = 0;
	}




	if (parent->return_chinese(a,b+1) == "届") {
		plural_next = 0;
		english = suffix(english);
		shift_post_chinese(parent,a,b+1,0,this);
	}
	if (parent->return_chinese(a,b+1) == "论") {
		plural_next = 0;
		english = suffix(english);
		add_post_english("round");
		shift_post_chinese(parent,a,b+1,0,this);
	}
	if (parent->return_chinese(a,b+1) == "左右") {
		add_pre_english("more or less");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b, this);
	}
	if (parent->return_chinese(a,b+1) == "型") {
		add_post_english("class");
		shift_post_chinese(parent, a, b+1, 0, this);
		parent->make_only(a,b, this);
		plural_next = 0;
	}

	
	if (parent->return_chinese(a,b+1) == "周年") {
		english = suffix(english);
		add_post_english("anniversary");
		shift_post_chinese(parent,a,b+1,0,this);
		if (parent->return_chinese(a,b-1) == "成立") {
			parent->make_only(a,b-1,"Noun");
			parent->text(a,b-1,0)->english = "establishment";
			parent->make_only(a,b-1,0);
		}
		parent->make_only(a,b,this);
		plural_next = 0;
	}





	// Percentages
	if (parent->return_chinese(a,b+1) == "％" || parent->return_chinese(a,b+1) == "%") { 
		add_post_english(" percent");
		shift_post_chinese(parent, a, b+1, 0, this);
		plural_next = 0;
		if (parent->return_chinese(a,b+1) == "左右") {
			parent->make_only(a,b,this);
			shift_post_chinese(parent,a,b+1,0,this);
			add_pre_english("around ");
		}
		if (parent->is_category_non_recursive("Noun", a, b+1) == 1) {
			add_post_english(" of");
		}
		parent->make_only(a,b,this);
		myclass += ":Percent";



	}
	if (parent->return_chinese(a,b-1) == "之" && parent->return_chinese(a,b-2) == "分" && parent->is_category_non_recursive("Number", a, b-3) == 1) {
		plural_next = 0;
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		add_post_english("/");
		add_post_english(parent->text(a,b-1,"Number")->return_english());
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		parent->make_only(a,b,this);
		post_english_spacing = 0;
		myclass += ":Percent";
		if (parent->return_chinese(a,b+1) == "左右") {
			parent->make_only(a,b,this);
			shift_post_chinese(parent,a,b+1,0,this);
			add_pre_english("around ");
		}
	}






	if (parent->return_chinese(a,b-1) == "之" && parent->return_chinese(a,b-2) == "百分") {
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		add_post_english(" percent");
		parent->make_only(a,b,this);
		myclass += ":Percent";
	}



	// Do Not Plural in Some Cases
	if (parent->return_chinese(a,b+1,0) == "版") { plural_next = 0; }



	// Measurement Words Following
	if (parent->is_category_non_recursive("Measurement",a,b+1) == 1) {
		plural_next = 0;
		parent->make_only(a,b+1,"Measurement");
	}


	// Centuries and Anniversaries
	if (parent->return_chinese(a,b+1) == "世纪" || 
	    parent->return_chinese(a,b+1) == "周年" ||
	    parent->return_chinese(a,b+1) == "周年纪念日" || 
	    parent->return_chinese(a,b+1) == "季度") {
		plural_next = 0;
		english = suffix(english);
		confidence += 10;
	}











	// 第/其 Precedes 
	if (parent->return_chinese(a,b-1) == "第" || parent->return_chinese(a,b-1) == "其") {

		shift_pre_chinese(parent, a, b-1, 0, this); b--;
		parent->make_only(a,b,this);		
		english = suffix(return_english_no_spacing());
		plural_next = 0;

		// 次/届
		if (parent->return_chinese(a,b+1) == "次") {

			shift_post_chinese(parent, a, b+1, 0, this);
			if (parent->is_category_non_recursive("Verb",a,b+1) == 1) {
				Adverb *temp = new Adverb(this);
				clone_values(temp);
				temp->english = "for the " + return_english() + " time";
				temp->myclass += ":PreD";
				parent->elements->at(a)->at(b)->push_back(temp);
				parent->make_only(a,b,temp);
				return 1;
			} 
			else {
				Text *temp = new Text(this);
				clone_values(temp);
				temp->english = return_english();
				temp->myclass += "Unit:PreNoun";
				parent->elements->at(a)->at(b)->push_back(temp);
				parent->make_only(a,b,temp);
				return 1;
			}
		}
		if (parent->return_chinese(a,b+1) == "届") {
			shift_post_chinese(parent,a,b+1,0,this);
		}
		if (parent->return_chinese(a,b+1) == "号") {
			english = suffix(english);
		}
		if (parent->return_chinese(a,b+1) == "代") {
			add_post_english("generation");
			shift_post_chinese(parent,a,b+1,0,this);
		}
		if (parent->is_category_non_recursive("Measure",a,b+1) == 1) {
			shift_post_chinese(parent,a,b+1,0,this);
			myclass += ":Measure:PreNoun";
			parent->make_only(a,b,this);
		}
	}






	// Currencies
	if (parent->return_chinese(a,b-1) == "人民币") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_post_english(" RMB");
		parent->make_only(a,b,this);
		if (parent->return_chinese(a,b+1) == "元") {
			shift_post_chinese(parent, a, b+1, 0, this);
		}
		plural_next = 0;
	}
	if (parent->return_chinese(a,b-1) == "美元") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_post_english(" USD");
		parent->make_only(a,b,this);
		plural_next = 0;
	}
	if (parent->return_chinese(a,b-1) == "加元") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_post_english(" CND");
		parent->make_only(a,b,this);
		plural_next = 0;
	}
	if (parent->return_chinese(a,b-1) == "日元") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_post_english(" YEN");
		parent->make_only(a,b,this);
		plural_next = 0;
	}
	if (parent->return_chinese(a,b-1) == "欧元") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_post_english(" EURO");
		parent->make_only(a,b,this);
		plural_next = 0;
	}



	// Measure Words & Misc
	if (parent->return_chinese(a,b+1) == "元") {
		plural_next = 0;
		add_post_english(" yuan");
		shift_post_chinese(parent, a, b+1, 0, this);
		if (parent->return_chinese(a, b+1) == "人民币") { shift_post_chinese(parent, a, b+1, 0, this); }
		if (parent->return_chinese(a,b+1) == "钱") { shift_post_chinese(parent, a, b+1, 0, this); }
	}
	if (parent->return_chinese(a,b+1) == "多元") {
		plural_next = 0;
		add_post_english(" dollars");
		add_pre_english("more than");
		shift_post_chinese(parent, a, b+1, 0, this);
	}
	if (parent->return_chinese(a,b+1) == "块") {
		plural_next = 0;
		add_post_english(" kuai");
		shift_post_chinese(parent, a, b+1, 0, this);
		if (parent->return_chinese(a, b+1) == "人民币") { shift_post_chinese(parent, a, b+1, 0, this); }
		if (parent->return_chinese(a,b+1) == "钱") { shift_post_chinese(parent, a, b+1, 0, this); }
	}
	if (parent->return_chinese(a,b+1) == "毛") {
		plural_next = 0;
		add_post_english(" mao");
		shift_post_chinese(parent, a, b+1, 0, this);
		if (parent->return_chinese(a, b+1) == "人民币") { shift_post_chinese(parent, a, b+1, 0, this); }
		if (parent->return_chinese(a,b+1) == "钱") { shift_post_chinese(parent, a, b+1, 0, this); }
	}
	if (parent->return_chinese(a,b+1) == "分" && parent->return_chinese(a,b+2) == "之") {
		plural_next = 0;
		add_post_english(" fen");
		shift_post_chinese(parent, a, b+1, 0, this);
		if (parent->return_chinese(a, b+1) == "人民币") { shift_post_chinese(parent, a, b+1, 0, this); }
		if (parent->return_chinese(a,b+1) == "钱") { shift_post_chinese(parent, a, b+1, 0, this); }
	}
	if (parent->return_chinese(a,b+1) == "余款") {
		plural_next = 0;
		add_post_english(" dollars");
		shift_post_chinese(parent, a, b+1, 0, this);
		add_pre_english(" ");
		add_pre_english("more than");
		if (parent->return_chinese(a,b+1) == "钱") { shift_post_chinese(parent, a, b+1, 0, this); }
	}
	if (parent->return_chinese(a,b+1) == "层楼房") {
		plural_next = 0;
		add_post_english(" story building");
		shift_post_chinese(parent, a, b+1, 0, this);
	}
	if (parent->return_chinese(a,b+1) == "层楼") {
		plural_next = 0;
		add_post_english(" story building");
		shift_post_chinese(parent, a, b+1, 0, this);
	}








	if (parent->return_chinese(a,b+1) == "成") {
		if (parent->is_category_non_recursive("Number",a,b+2) != 1) {
			if (whole_number == 1) { english = "ten percent"; }
			if (whole_number == 2) { english = "twenty percent"; }
			if (whole_number == 3) { english = "thirty percent"; }
			if (whole_number == 4) { english = "forty percent"; }
			if (whole_number == 5) { english = "fifty percent"; }
			if (whole_number == 6) { english = "sixty percent"; }
			if (whole_number == 7) { english = "seventy percent"; }
			if (whole_number == 8) { english = "eighty percent"; }
			if (whole_number == 9) { english = "ninety percent"; }
			shift_post_chinese(parent,a,b+1,0,this);
			parent->make_only(a,b,this);
		}
	}
	if (parent->return_chinese(a,b+1) == "及以上") {
		add_post_english(" or more");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "以上") {
		add_pre_english("upwards of ");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "以下") {
		add_pre_english("downwards of ");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "到" && parent->is_category_non_recursive("Number",a,b+2) == 1) {
		add_post_english(" to");
		shift_post_chinese(parent,a,b+1,0,this);
		add_post_english(" ");
		add_post_english(parent->text(a,b+2,"Number")->return_english());
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
		myclass += ":Range";
	}
	if (parent->return_chinese(a,b+1) == "到" && parent->is_category_non_recursive("Date",a,b) != 1) {
		if (parent->is_category_non_recursive("NonChinese",a,b-1) != 1) {
			add_post_english("downwards of");
			shift_post_chinese(parent,a,b+1,0,this);
			parent->make_only(a,b,this);
			return 1;
		}
	}
	if (parent->return_chinese(a,b+1) == "上") {
		add_post_english(" over");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "多") {
		add_pre_english("more than ");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "逾") {
		add_post_english(" more than");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "余") {
		add_post_english(" more than");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "少") {
		add_post_english(" less than");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "历时") {
		add_pre_english("over the last ");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "号") {
		add_pre_english("number ");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
		plural_next = 0;
	}
	if (parent->return_chinese(a,b+1) == "室") {
		add_post_english(" room");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
		plural_next = 0;
	}
	if (parent->return_chinese(a,b-1) == "连续") {
		add_pre_english("over the last ");
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "多年来") {
		add_pre_english("over the past ");
		if (whole_number == 1) { add_post_english(" year"); } else { add_post_english(" years"); }
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "岁" || parent->return_chinese(a,b+1) == "大寿" || parent->return_chinese(a,b+1) == "高龄") {
		add_post_english(" years old");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
		myclass += ":Age";
		if (parent->return_chinese(a,b+1) == "以上") {
			add_pre_english("upwards of ");
			shift_post_chinese(parent,a,b+1,0,this);
			parent->make_only(a,b,this);
		}
		if (parent->return_chinese(a,b+1) == "以下") {
			add_pre_english("less than ");
			shift_post_chinese(parent,a,b+1,0,this);
			parent->make_only(a,b,this);
		}
		if (parent->return_chinese(a,b-1) == "现年") {
			add_post_english("this year ");
			shift_post_chinese(parent,a,b+1,0,this);
			parent->make_only(a,b,this);
		}
	}





	// Measure Words & Misc
	if (parent->return_chinese(a,b+1) == "元") {
		plural_next = 0;
		add_post_english(" yuan");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "摄氏度") {
		plural_next = 0;
		if (whole_number != 1) { add_post_english(" degrees Celcius"); }
		else { add_post_english(" degree Celcius"); }
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "块") {
		plural_next = 0;
		add_post_english(" kuai");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "毛") {
		plural_next = 0;
		add_post_english(" mao");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "分" == 1 && parent->return_chinese(a,b+2) != "之") {
		plural_next = 0;
		add_post_english(" fen");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b+1) == "折") {
		plural_next = 0;

		if (whole_number == 1 || whole_number == 2 || whole_number == 3 || whole_number == 4 || whole_number == 5 || whole_number == 6 || whole_number == 7 || whole_number == 8 || whole_number == 9) {
			add_post_english(" percent");
			add_pre_english("discounted to ");
			shift_post_chinese(parent,a,b+1,0,this);
			parent->make_only(a,b,this);
			english += return_english() + "0";
		}
	}
	if (parent->return_chinese(a,b-1) == "至" && parent->is_category_non_recursive("Number",a,b-2) == 1) {
		if (parent->is_category_non_recursive("Time",a,b) == -1 && parent->is_category_non_recursive("Month",a,b) == -1) {
			add_pre_english("to ");
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			parent->make_only(a,b,this);
		}
	}

	if (parent->return_chinese(a,b+1) == "左右") {
		add_pre_english("around ");
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
	}











	if (parent->return_chinese(a,b+1) == "级") {
		plural_next = 0;
		add_pre_english("level ");
		shift_post_chinese(parent,a,b+1,0,this);
		if  (parent->return_chinese(a,b-1) == "里氏") {
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			add_post_english(" on the Richter scale");
			if (parent->return_chinese(a,b+1) == "强烈余震") {
				add_pre_english("an intense earthquake measuring ");
				shift_post_chinese(parent,a,b+1,0,this);
			}
			if (parent->return_chinese(a,b+1) == "地震") {
				add_pre_english("an earthquake measuring ");
				shift_post_chinese(parent,a,b+1,0,this);
			}
		}
		if (parent->return_chinese(a,b+1) == "以上") {
			add_pre_english("more than ");
			shift_post_chinese(parent,a,b+1,0,this);
		}
		if (parent->return_chinese(a,b+1) == "以下") {
			add_pre_english("less than ");
			shift_post_chinese(parent,a,b+1,0,this);
		}
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "刑" && parent->return_chinese(a,b+1) == "年") {
		shift_post_chinese(parent,a,b+1,0,this);
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		if (whole_number > 1) { add_post_english(" years"); }
		else { add_post_english(" year"); }
		add_post_english(" punishment");
		parent->make_only(a,b,this);
	}
	if (parent->return_chinese(a,b-1) == "有期徒刑" && parent->return_chinese(a,b+1) == "年") {
		shift_post_chinese(parent,a,b+1,0,this);
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		if (whole_number > 1) { add_post_english(" years"); }
		else { add_post_english(" year"); }
		add_post_english(" limited imprisonment");
		parent->make_only(a,b,this);
	}
	if (parent->is_category_non_recursive("Measure",a,b+1) == 1 && parent->return_chinese(a,b+2) == "多") {
		shift_post_chinese(parent,a,b+1,0,this);
		shift_post_chinese(parent,a,b+1,0,this);
		add_pre_english("more than ");
		if (parent->return_chinese(a,b+1) == "来") {
			shift_post_chinese(parent,a,b+1,0,this);
			add_pre_english("in the last ");
		}
		parent->make_only(a,b,this);
	}


	// Measure versus Time
	if (parent->return_chinese(a,b+1) == "次" && parent->is_category_non_recursive("Verb",a,b+2) == 1) {
		shift_post_chinese(parent,a,b+1,0,this);
		if (whole_number > 1) { add_post_english(" times"); }
		else { add_post_english(" time"); }
		parent->make_only(a,b,this);
		parent->make_only(a,b+1,"Verb");
	}
	if (parent->return_chinese(a,b-1) == "过" && parent->is_category_non_recursive("Measure", a, b+1) == 1 && parent->is_category_non_recursive("Noun",a,b+2) == 1){
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_post_english(" in excess of");
		parent->make_only(a,b,this);
	}







	// Miscellaneous
	if (parent->return_chinese(a,b+1) == "强") {
		shift_post_chinese(parent,a,b+1,0,this);
		add_post_english(" strongest");
		if (parent->return_chinese(a,b-1) == "前") {
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			add_pre_english("top");
		}
		add_pre_english("the");
		parent->make_only(a,b,this);
		plural_next = 0;
	}










	if (parent->return_chinese(a,b+1) == "大") {
		if (parent->return_chinese(a,b-1).find("中") != std::string::npos) {
			shift_post_chinese(parent,a,b+1,0,this);
			english = suffix(english);
			english += " Congress";	
			parent->make_only(a,b,this);
			plural_next = 0;
			myclass = "Unit:ProperNoun";
		}
	}
	if (parent->return_chinese(a,b+1) == "点") {
		shift_post_chinese(parent,a,b+1,0,this);
		english += " points";	
		parent->make_only(a,b,this);
		plural_next = 0;
		myclass += ":Stock";
	}




	if (parent->return_chinese(a,b-2) == "距离") {
		if (parent->is_category_non_recursive("Noun",a,b-1) == 1) {
			add_post_english(" from");
			add_post_english(parent->likely(a,b-1)->return_english());
			add_pre_english("a distance of");
			shift_pre_chinese(parent,a,b-1,0,this);b--;
			shift_pre_chinese(parent,a,b-1,0,this);b--;
			parent->make_only(a,b,this);
		}
	}



	// Pluralize Following Nouns which do not require measure words
	std::string next = parent->return_chinese(a,b+1,0);
        if (
		next == "年" ||
		next == "周" ||
		next == "月" ||
		next == "日" ||
		next == "星期" ||
		next == "礼拜" ||
		next == "小时" ||
		next == "分钟" ||
		next == "秒"
	) {
		for (int i = 0; i < parent->elements->at(a)->at(b+1)->size(); i++) {
			parent->elements->at(a)->at(b+1)->at(i)->plural = 1;
		}
	}




	return 1;
}

int Number::advanced(Text *t, int a, int b, int c) {

  if (plural_next == 1) {
    myclass += ":Plural";
  }

  return 1;
}

void Number::generate_numbers() {

	int y = 0;
	int mm = 1;
	int max_loop = 0;
	int decimal_found  = 0;
	int decimal_start  = 0;
	int post_number = 0;

	double dmm = 0.1; 

	// Are We Consecutive?
	int starts_with_zero = 0;
	int previous_number = 0;
	int current_number = 0;
	int place_signifier_used = 0;	

	int temp;	

	long unsigned int whole_num = 0;
	double decimal_num = 0;
	long unsigned int multiplier = 0;
	long unsigned int decimal_multiplier = 0;
	float complete = 0;

	std::string fullchinese = return_numeric_chinese();
	following_pinyin = "";

	Number *post = this;


	// Generate Chinese for the Whole Number
	for (int i = 0, j = 1; j == 1 && post->post_chinese != NULL; i++) {
		if (post->post_chinese->chinese == "." || post->post_chinese->chinese_utf8s == "." || post->post_chinese->chinese == "．" || post->post_chinese->chinese == "点") {
			j = 0;
			max_loop--;
			decimal_found = 1;
			decimal_start = i+1;
			if (post->post_chinese->chinese == "点") {
				post->post_chinese->english = ".";
			}
		} else {
			if (post->post_chinese->is_category_non_recursive("Number") != 1) {
//				max_loop--;
			}
		}
		max_loop++;
		post = (Number *) post->post_chinese;
	}


	// What is the first number?
	previous_number = convert2number(chinese);


	// Check to see if this starts with a ZERO
	if (previous_number == 0) { starts_with_zero = 1; }


	int prev_place_signifier = 0;
	int last_place_signifier = 0; 
	int first_number = 1;
	int ignore_first_zero = 0;

	// Now Generate Whole Number
	for (int i = 0; i <= max_loop; i++) { 

		post = this;
		for (int h = i; h < max_loop; h++) { post = (Number *) post->post_chinese; }

		if ( post->myclass.find("Number") == std::string::npos) {
		} else {


		temp = convert2number(post->chinese);


		// Check to see if this is a consecutive number
		current_number = temp;
		if (current_number == previous_number+1 && previous_number != 0) { 
			if (is_complex_number(fullchinese) != 1) {
			}
		}
		previous_number = current_number;




		// Check to See if the Number Has Grown Too Big -- Adjust
		if (mm == 1000000000 && whole_num == 0) {
		  mm = 1000;
		  add_post_english(" million");
  		}




	        if (temp == 0 && last_place_signifier == 1) { mm /= 10; }
		if (temp == 0) { 
                  mm *= 10; 
                  last_place_signifier = 0;
                }
		else {

			if (temp < 10) {
				if (last_place_signifier == 1) {

					mm/=10;
					whole_num = (int) whole_num + (int) (mm * temp);
					y = 0;
					last_place_signifier = 0;

				} else {

					// Only Add if Last is NOT a Place Signifier
  					if (last_place_signifier != 1 && first_number != 1) { mm *= 10; }
					whole_num = (int) whole_num + (int) (mm * temp);
					y = 0;
					last_place_signifier = 0;
				}
				first_number = 0;
			}
			else {
				if (mm < temp) { 
					if (prev_place_signifier == 0) {
						int temp2 = temp/10;
						int temp3 = whole_num/10;
						while (temp3 > 0) { temp2=temp2/10; temp3=temp3/10; }
						post_number = (whole_num * temp2) + post_number;
					}
					else {
						if (whole_num == 0) { whole_num = 1 * prev_place_signifier; }
						post_number = whole_num + post_number;
					}
					prev_place_signifier = temp;
					whole_num = 0;

					mm = temp *10; 
					multiplier = temp;
				}
				else { 

					if (mm == temp) {}
					else { mm *= temp; };

				}
				y = 1;
				place_signifier_used = 1;
				last_place_signifier = 1;

			}

		}
		}

	}



	if (y == 1) { whole_num = (int) (mm + whole_num) / 10; }
	if (post_number > 0 ) { whole_num += post_number; }




	int yi_in_decimal = 0;


	// Generate Chinese for Decimal
	mm = 1;
	if (decimal_found == 1) {

		post = this;
		// Generate Chinese for the Whole Number
		for (int i = 0; i < decimal_start; i++) { post = (Number *) post->post_chinese; }

		if (post->post_chinese == NULL) { return; }
		while (post->post_chinese != NULL) {
			post = (Number *) post->post_chinese;
			temp = convert2number(post->chinese);			
			if (temp > 9)  { 
				if (temp == 100000000) {
					// YI in DECIMAL NUMBER
					yi_in_decimal = 1;
				} else {
					if (mm == 1) { mm = temp; }
					else { mm *= temp; } 
				}
			}
			if (temp < 9) { decimal_num += (dmm * temp); dmm *= 0.1; }
		}
	}

	if (mm > 1) { decimal_multiplier = mm; }




	// Now Generate the English
	if (decimal_num == 0) {
		std::stringstream myStream1;
		myStream1 << whole_num;
		english = myStream1.str(); 

	} else {

		// Adjust Whole Number with Decimal Multiplier
		if (decimal_multiplier == 0) { decimal_multiplier = 1; }
			whole_num *= decimal_multiplier;
			int bigger_than_dec = (int) (decimal_num * (decimal_multiplier));
			if (bigger_than_dec <= 0) {}
			else {
				decimal_num = bigger_than_dec - (decimal_num * (decimal_multiplier));
                                decimal_num *= -1;
				if (decimal_num < 0.0001 && decimal_multiplier > 1) { decimal_num = 0; }
				whole_num += bigger_than_dec;
			}
		}


		// Handle Really Large Decimal Numbers with Yi
		if (yi_in_decimal == 1) {
			following_pinyin = "yi4";
			int testred = whole_num / 10;
			int testrem = whole_num - ((whole_num/10)*10);
			if (testrem != 0) {
				add_post_english(" hundred million");
			} else {

				testred = whole_num / 10000;
				testrem = whole_num - ((whole_num/10000)*10000);
				if (testrem != 0) {
					whole_num = (whole_num/10);
					decimal_num = (decimal_num/10);
					add_post_english(" billion");
				} else {
					whole_num = (whole_num/10000);
					add_post_english(" trillion");
				}
			}
		}



	std::stringstream myStream;
	if (decimal_num > 0) {
		myStream << whole_num; 
		myStream << decimal_num;
		english = myStream.str();
		english = english.substr(0, english.find("0.")) + "." + english.substr(english.find("0.")+2); 
		complete = (float) decimal_num + whole_num;
	} 
	else { 
		myStream << whole_num; 
		english = myStream.str(); 
	}


	whole_number = whole_num;
	decimal_number = decimal_num;
	full_number = complete;
	integer_representation = whole_number;
	decimal_representation = decimal_number;

	return;
}

int Number::convert2number(std::string word) {

	if (word == "Ｏ") { return 0; }
	if (word == "０") { return 0; }		
	if (word == "１") { return 1; }
	if (word == "２") { return 2; }
	if (word == "３") { return 3; }
	if (word == "４") { return 4; }
	if (word == "５") { return 5; }
	if (word == "６") { return 6; }
	if (word == "７") { return 7; }
	if (word == "８") { return 8; }
	if (word == "９") { return 9; }
	if (word == "零") { return 0; }
	if (word == "十") { return 10; }
	if (word == "百") { return 100; }
	if (word == "千") { return 1000; }
	if (word == "万")   { return 10000; }
	if (word == "十万") { return 100000; }
	if (word == "百万") { return 1000000; }
	if (word == "千万") { return 10000000; }
	if (word == "万万") { return 100000000; }
	if (word == "亿")   { return 100000000; }
	if (word == "一") { return 1; }
	if (word == "二") { return 2; }
	if (word == "两") { return 2; }
	if (word == "三") { return 3; }
	if (word == "四") { return 4; }
	if (word == "五") { return 5; }
	if (word == "六") { return 6; }
	if (word == "七") { return 7; }
	if (word == "八") { return 8; }
	if (word == "九") { return 9; }
	if (word == "1") { return 1; }
	if (word == "2") { return 2; }
	if (word == "3") { return 3; }
	if (word == "4") { return 4; }
	if (word == "5") { return 5; }
	if (word == "6") { return 6; }
	if (word == "7") { return 7; }
	if (word == "8") { return 8; }
	if (word == "9") { return 9; }
	if (word == "0") { return 0; }
	if (word == "壹") { return 1; }
	if (word == "贰") { return 2; }
	if (word == "叄") { return 3; }
	if (word == "肆") { return 4; }
	if (word == "伍") { return 5; }
	if (word == "陆") { return 6; }
	if (word == "柒") { return 7; }
	if (word == "捌") { return 8; }
	if (word == "玖") { return 9; }
	if (word == "拾") { return 10; }
	if (word == "佰") { return 100; }
	if (word == "仟") { return 1000; }


	return -1;	
};

int Number::is_complex_number(std::string word) {

	if (word == "十") { return 1; }
	if (word == "百") { return 1; }
	if (word == "千") { return 1; }
	if (word == "万")   { return 1; }
	if (word == "亿")   { return 1; }

	return 0;	
};


/* Returns only the Numbers */
std::string Number::return_numeric_chinese() {
  std::string my_number = chinese;
  if (post_chinese != NULL) {
    if (post_chinese->is_category_non_recursive("Number") == 1) {
      Number *temp = (Number *) post_chinese;
      my_number += temp->return_numeric_chinese();
      return my_number;
    }
  }
  return my_number;
}





std::string Number::suffix(std::string x) {

	if (x.length() == 0) { return x; }
	if (x.substr(x.length()-1) == "1") { 
		if (x.length() >= 2) { if (x.substr(x.length()-2) == "11") { return x+"th"; } } return x+"st"; 
	}
	if (x.substr(x.length()-1) == "2") { 
		if (x.length() >= 2) { if (x.substr(x.length()-2) == "12") { return x+"th"; } } return x+"nd"; 
	}		
	if (x.substr(x.length()-1) == "3") { 
		if (x.length() >= 2) { if (x.substr(x.length()-2) == "13") { return x+"th"; } } return x+"rd"; 
	}		
	if (x.substr(x.length()-1) == "4") { return x+"th"; }		
	if (x.substr(x.length()-1) == "5") { return x+"th"; }		
	if (x.substr(x.length()-1) == "6") { return x+"th"; }		
	if (x.substr(x.length()-1) == "7") { return x+"th"; }		
	if (x.substr(x.length()-1) == "8") { return x+"th"; }		
	if (x.substr(x.length()-1) == "9") { return x+"th"; }		
	if (x.substr(x.length()-1) == "0") { return x+"th"; }		

	return x;	

};

std::string Number::add_commas_to_number(std::string numin) {

	std::string numout = numin;

	if (numin == "") { return ""; }
        if (numin.find("a") != std::string::npos) { return numin; }
        if (numin.find("e") != std::string::npos) { return numin; }
        if (numin.find("i") != std::string::npos) { return numin; }
        if (numin.find("o") != std::string::npos) { return numin; }
        if (numin.find("u") != std::string::npos) { return numin; }
        if (numin.find("st") != std::string::npos) { return numin; }
        if (numin.find("th") != std::string::npos) { return numin; }
        if (numin.find("nd") != std::string::npos) { return numin; }
        if (numin.find("rd") != std::string::npos) { return numin; }

	int decimal_location = numin.length()-1;
	if (numin.find(".") != std::string::npos) {
		decimal_location = numin.find(".")-1;
	}

	for (int i = decimal_location-3; i >= 0; i-=3) {
	numout = numout.substr(0, i+1) + "," + numout.substr(i+1);
	}

	return numout;
}
std::string Number::generate_complex_pinyin(int nu) {


	if (nu < 0) { return ""; }
	if (nu == 0) { return "ling2"; }

	std::string pp = "";
	std::string tt = "";
	std::string post_num = "";
	int i = 1;
	int last_num = 0;

	if (nu%100000000  == 0) { post_num += "yi4"; nu = nu/100000000; }
	if (nu%10000000 == 0) { post_num += "qian1wan4"; nu = nu / 10000000; }
	if (nu%1000000 == 0) { post_num += "bai3wan4"; nu = nu / 1000000; }
	if (nu%10000  == 0) { post_num += "wan4"; nu = nu / 10000; }

	while (nu > 0) {

		if (i == 100000) {

 			if (nu < 10000) {
				int nu2 = nu%10000;
				nu2 *= 10;
				nu = nu - nu%10000;
				pp = generate_complex_pinyin(nu2);
				if (pp.length() > 5) {
					if (
						 pp.substr(pp.length()-5) == "ling2"
					) {
						pp = pp.substr(0, pp.length()-5);
					}
				}
				if (pp == "ling2") { pp = ""; }
				i*= 10000;
			} else {
				int nu2 = (nu - nu%10000) / 10000;
				nu2 *= 10;
				pp = generate_complex_pinyin(nu2);
				if (pp == "ling2") { pp = ""; 
				} 
				else { pp += "yi4"; }
				i*= 10000;
				if (generate_complex_pinyin(nu%10000) != "ling2") {
					pp += generate_complex_pinyin(nu%10000);
				};
			}


		} else {

			pp = what_is_my_pinyin(nu%10);
			last_num = nu%10;
			nu -= nu%10;
			nu /= 10;

			if (pp == "yi1" && (i == 10000 || i == 100000000)) { pp = "yi2"; }

			if (pp == "ling2") { pp = ""; 

			}
			else {
				if (i == 10) { pp += "shi2 "; }
				if (i == 100) { pp += "bai3 "; }
				if (i == 1000) { pp += "qian1 "; }
				if (i == 10000) { pp += "wan4 "; }
			}
				if (i == 100000000) { pp += "yi4 "; }

			i*=10;
		}
		tt = pp + tt;
	}

	if (post_num != "") { tt += post_num; }
	if (tt.find("yi1shi2") != std::string::npos) {	
		if (tt.length() > tt.find("yi1shi2"+6)) {
			tt = tt.substr(0, tt.find("yi1shi2")) + "shi2" + tt.substr(tt.find("yi1shi2")+7);
		}
		else { 
			tt = tt.substr(0, tt.find("yi1shi2")) + "shi2";
		}
	}


	return tt;


}
std::string Number::what_is_my_pinyin(int x) {
	if (x == 1) { return "yi1"; }
	if (x == 2) { if (chinese == "两") {return "liang3";} return "er4"; }
	if (x == 3) { return "san1"; }
	if (x == 4) { return "si4"; }
	if (x == 5) { return "wu3"; }
	if (x == 6) { return "liu4"; }
	if (x == 7) { return "qi1"; }
	if (x == 8) { return "ba1"; }
	if (x == 9) { return "jiu3"; }
	if (x == 0) { return "ling2"; }
	return "";
}





