#include "lu01.h"
#include "special.h"
#include "text.h"
#include "encoding.h"
#include "memory.h"




Lu01::Lu01(Text *t): Special(t) { myclass += ":Lu01";};
Lu01::~Lu01() {}

int Lu01::unify(Text *t, int a, int b, int c) {


  std::string previous_word = t->text(a,b-1,0)->return_chinese();
  int length_of_previous_word = t->encoding->character_length(t->text(a,b-1,0)->return_chinese_input_encoding());
  int generate_name = 0;

  if (t->return_chinese(a,b-1) == "北") { 
	shift_pre_chinese(t,a,b-1,0,this); b--;
	add_pre_english(" North");
	t->make_only(a,b,this);
  }
  if (t->return_chinese(a,b-1) == "南") { 
	shift_pre_chinese(t,a,b-1,0,this); b--;
	add_pre_english(" South");
	t->make_only(a,b,this);
  }
  if (t->return_chinese(a,b-1) == "西") { 
	shift_pre_chinese(t,a,b-1,0,this); b--;
	add_pre_english(" West");
	t->make_only(a,b,this);
  }
  if (t->return_chinese(a,b-1) == "东") { 
	shift_pre_chinese(t,a,b-1,0,this); b--;
	add_pre_english(" East");
	t->make_only(a,b,this);
  }
  if (t->return_chinese(a,b-1) == "中") { 
	shift_pre_chinese(t,a,b-1,0,this); b--;
	add_pre_english(" Central");
	t->make_only(a,b,this);
  }




  // This is probably a road name if.... the last two characters make sense contextually 
  if (length_of_previous_word == 1) {
      if (t->encoding->character_length(t->text(a,b-2,0)->return_chinese_input_encoding()) == 1) {
	english = t->text(a,b-1,0)->return_pinyin() + t->text(a,b-2,0)->return_pinyin();
	shift_pre_chinese(t,a,b-1,0,this); b--;
	shift_pre_chinese(t,a,b-1,0,this); b--;
 	t->make_only(a,b,this);
 	myclass += ":Road:Place";
	generate_name = 1;
      }
  } else {
    if (length_of_previous_word == 2) {
	// see if the previous word is in our likely list in memory
	int treat_as_place_name = 0;
	for (int i = 0; i < t->memory->likely->size(); i++) {
		if (
			previous_word.find(t->memory->likely->at(i)) != std::string::npos
		) {
 			treat_as_place_name = 1;
			i = t->memory->likely->size()+1;
		} 
	}
	if (treat_as_place_name == 1) {
		english = t->text(a,b-1,0)->return_pinyin();
		shift_post_chinese(t,a,b-1,0,this); b--;
 		t->make_only(a,b,this);
 		myclass += ":Road:Place";
		generate_name = 1;
	}
    }
  }




  if (generate_name == 1) {

	english = generate_road_name() + " road";
  

	// Check to See if this is a Number
	if (t->is_category_non_recursive("Number",a,b-1) == 1) {
		add_pre_english(t->text(a,b-1,"Number")->return_english_no_spacing());
		shift_pre_chinese(t,a,b-1,0,this); b--;	
	} else {
		if (t->is_category_non_recursive("Number",a,b-2) == 1 && t->return_chinese(a,b-1,0) == "号") {
			add_pre_english(t->text(a,b-2,"Number")->return_english_no_spacing());
			shift_pre_chinese(t,a,b-1,0,this); b--;	
			shift_pre_chinese(t,a,b-1,0,this); b--;	
		}
	}

  }


  if (t->is_category_non_recursive("Place",a,b+1) == 1) {
    add_post_english(t->text(a,b+1,"Place")->return_english_no_spacing());
    shift_post_chinese(t,a,b+1,0,this);
    t->make_only(a,b,this);
    if (myclass.find("Place") != std::string::npos) {
      myclass += ":Address";
    }
  }


  return 1;

}


std::string Lu01::generate_road_name() {

	english = stripped_of_tones(english);
	if (english.length() > 0) {
		english[0] = toupper(english[0]);
	}
	while (english.find(" ") != std::string::npos) { english = english.substr(0, english.find(" ")) + english.substr(english.find(" ")+1); }
	
	return english;
}




