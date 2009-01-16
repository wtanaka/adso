#include "name.h"
#include "noun.h"
#include "text.h"
#include "encoding.h"
#include "memory.h"

Name::Name(Text *t): Noun(t) { 
	myclass += ":Name";
	length = 1;
	pinyin_generated = 0;
	name = "";
	english = "";
};
Name::~Name() {}



std::string Name::return_pinyin_no_spacing() {
  if (pinyin_generated == 1) { return pinyin; }
  return Unit::return_pinyin_no_spacing(); 
}
std::string Name::return_pinyin() { 

  if (post_pinyin_spacing == 1) { return pinyin + " "; }
  // already generated
  return pinyin;

}

void Name::set_english(std::string x) { name = x; english = x; }
void Name::set_pinyin(std::string x) { pinyin = x; }
int Name::adjust_confidence(Text *parent, int a, int b, int c) { 

  if (length == 1) {
    for (int i = 0; i < parent->memory->names->size(); i++) {
      if (parent->memory->names->at(i).find(return_chinese()) == 0) {
        parent->make_only(a,b,this);
      }
    }
  }

  return 1; 

}
int Name::combine(Text *parent, int a, int b, int c) { return 1; }
int Name::pre_unify(Text *parent, int a, int b, int c) {

	std::string last = " ";
	std::string lastpin = " ";
	std::string next_char1 = parent->return_chinese(a,b+1);
	std::string next_char2 = parent->return_chinese(a,b+2);


        // Ridiculously Long Word Follows
	if (next_char1.length() > 6) { length = 1; return 1; }

	std::string xing_pinyin = return_pinyin_no_spacing();

	// This will otherwise interfere with name generation
	if (parent->return_chinese(a,b-1) == "某") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_pre_english("a certain person named");
		parent->make_only(a,b,this);
		return 1;  // last names only
	}


	if (parent->is_category_non_recursive("Xing",a,b) == 1 && parent->is_category_non_recursive("Cadverb",a,b-1) == 1) { return 1; }
	if (parent->is_category_non_recursive("Yu01",a,b) == 1 && parent->is_category_non_recursive("Verb",a,b-1) == 1) { return 1; }

	if (parent->is_category_non_recursive("Conjunction",a,b) == 1 && parent->is_category_non_recursive("Comma",a,b-1) == 1) { return 1; }

	// Escape Conditions
	if (parent->is_category_non_recursive("Phonetic",a,b) == 1 && parent->is_category_non_recursive("Dot",a,b-1) == 1) { return 1; }
	if (parent->is_category_non_recursive("Name",a,b-1) == 1) { return 1; }
	if (parent->is_category_non_recursive("Measure") == 1 && ( parent->is_category_non_recursive("Adjective",a,b-1) == 1 || parent->is_category_non_recursive("Number",a,b-1) == 1)) { 
		if (return_chinese() == "张") {} else {
			parent->make_only(a,b,"Measure"); 
		}
	}
	if (parent->is_category_non_recursive("Measure",a,b-1) == 1) { 
		if (parent->is_category_non_recursive("Dui01",a,b-1) == 1) {} else { return 1; }
	}
	if (parent->is_category_non_recursive("Measure",a,b) == 1 && parent->is_category_non_recursive("Number",a,b-1) == 1) { return 1; }
	if (parent->elements->at(a)->size() <= b+1) { return 1; }
	if (chinese == "万" && parent->return_chinese(a,b+1) == "余") { return 1; }
	if (parent->is_category_non_recursive("Adverb",a,b+1) == 1 && parent->is_category_non_recursive("Verb",a,b+2) == 1) { return 1; }
	if (parent->is_category_non_recursive("Verb",a,b+1) == 1 && parent->is_category_non_recursive("De02",a,b+2) == 1) { return 1; }
	if (parent->is_category_non_recursive("Adjective",a,b+1) == 1 && parent->is_category_non_recursive("Bu01",a,b+2) == 1) { return 1; }
	if (parent->is_category_non_recursive("Yu01",a,b) == 1 && parent->is_category_non_recursive("Date",a,b+1) == 1) { return 1; }
	// GB2312
	if (return_chinese().length() > 4) { return 1; } 




	// Transformations
	if (parent->return_chinese(a,b-1) == "小") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_pre_english("Xiao");
		parent->make_only(a,b,this);
		return 1;
	}
	if (parent->return_chinese(a,b-1) == "老") {
		shift_pre_chinese(parent,a,b-1,0,this); b--;
		add_pre_english("Lao");
		parent->make_only(a,b,this);
		return 1;
	}
	if (parent->is_category_non_recursive("Address",a,b+1) == 1) {
		add_pre_english(parent->text(a,b+1,"Address")->return_english());
		shift_post_chinese(parent,a,b+1,0,this);
		parent->make_only(a,b,this);
		return 1;
	}





	// DOUBLENAMES
	if (flag.find("DOUBLENAME") != std::string::npos) {
		if (parent->return_chinese(a,b+1,0).length() == 2) {
			length = 2;
			if (parent->is_category_non_recursive("Punctuation",a,b+1) == 1) { length = 1; }
			if (parent->is_category_non_recursive("Verb",a,b+1) == 1) { length = 1; }
			if (parent->is_category_non_recursive("Measure",a,b+1) == 1) { length = 1; }
			parent->make_only(a,b,this);
			if (length == 2 && parent->return_chinese(b+2).length() == 2) { 
				length = 3;
				if (parent->is_category_non_recursive("Punctuation",a,b+2) == 1) { length = 2; }
				if (parent->is_category_non_recursive("Verb",a,b+2) == 1) { length = 2; }
				if (parent->is_category_non_recursive("Measure",a,b+2) == 1) { length = 2; }
			}	
		}
	}
	else { //SINGLENAME



	// Test the following Word to see if its appropriate 
	if (parent->encoding->character_length(parent->text(a,b+1,0)->return_chinese_input_encoding()) == 1 && parent->is_category_non_recursive("Phonetic",a,b+1) ==1) {
		for (int jj = 0;  jj < memory->likely->size(); jj++) {
			if (parent->return_chinese(a,b+1).find(memory->likely->at(jj)) != std::string::npos) { length = 2; }
		}
		if (length == 1) {
			if (parent->is_category_non_recursive("Number", a, b+3) == 1) { length++; }
			if (parent->is_category_non_recursive("Punctuation", a, b+2) == 1) { length++; }
			if (parent->is_category_non_recursive("Unit",a,b+2) == 1) {
				if (parent->encoding->character_length(parent->text(a,b+2,0)->return_chinese_input_encoding()) == 1) {
					length++;
				}
			}
		}

	}
	else { 

		length++; 

		// This is a bigger word, return unless we can find a likely candidate in it
		if (parent->encoding->character_length(parent->text(a,b+1,0)->return_chinese_input_encoding()) == 2) {
			std::string tempa = parent->return_chinese(a,b+1);
			for (int j = 0;  j < memory->likely->size(); j++) { 
			  if(tempa.find(memory->likely->at(j)) != std::string::npos) { length++; } 
			}
			if (length >= 2) { length = 1; return 1; }
			else { length = 2; };
		}


	} // pushes default name length to 2


	// Roll the Length back to '1' if we find any of the following conditions which suggest this is not a name
	if (parent->is_category_non_recursive("Number",a,b+1) == 1) { if (parent->return_chinese(a,b+1) != "万" && parent->return_chinese(a,b+1) != "百"){length = 1;}}
	if (parent->is_category_non_recursive("NonChinese",a,b+1) == 1) { length = 1; }
	if (parent->is_category_non_recursive("Punctuation",a,b+1) == 1) { length = 1; }
	if (parent->encoding->character_length(parent->text(a,b+1,0)->return_chinese_input_encoding()) > 2) { length = 1; }
	for (int j = 0;  j < memory->unlikely->size(); j++) { if (memory->unlikely->at(j) == parent->return_chinese(a,b+1)) { length = 1; } }


	// Now test the following Word to see if its appropriate
	if (length == 2 && parent->encoding->character_length(parent->text(a,b+1,0)->return_chinese_input_encoding()) == 1) {
		length++;
		if (parent->elements->at(a)->size() <= b+2) {}
		else {
			if (parent->return_chinese(b+2).length() > 2 || parent->return_chinese(b+1).length() == 0) {}
			else { 
				// Check Memory to see if this Name has been Added
				//if (parent->text->memory->contains_name(chinese + next_char1) == 0) { length++; }
			}
			if (parent->return_chinese(a,b+2) == "和" && (parent->is_category_non_recursive("Name",a,b+3) == 1 || parent->is_category_non_recursive("Person",a,b+3) == 1)  ) { length = 2; }
			if (parent->encoding->character_length(parent->text(a,b+2,0)->return_chinese_input_encoding()) > 1) { length = 2; }
			if (parent->is_category_non_recursive("Number",a,b+2) == 1) { length = 2; }
			if (parent->is_category_non_recursive("NonChinese",a,b+2) == 1) { length = 2; }
			if (parent->is_category_non_recursive("Punctuation",a,b+2) == 1) { length = 2; }
			if (parent->is_category_non_recursive("Jiang01",a,b+2) == 1) { 
				if (parent->is_category_non_recursive("Verb",a,b+3) == 1 && parent->is_category_non_recursive("Adverb",a,b+3) == 1) {
					length = 2; 
				}
			}

			// Unlikely
			for (int k = 0;  k < memory->unlikely->size(); k++) { if (memory->unlikely->at(k) == parent->return_chinese(a,b+2)) { length = 2; } }
		}
	}
	} // SINGLEDOUBLE


	if (parent->is_category_non_recursive("Special",a,b+1) == 1 && length == 2) { 
		// Avoid Unifying Measure Words that are Also Special
		if (parent->is_category_non_recursive("Measure",a,b+1) == 1) { length = 1; return 1; }
	}
	if (parent->is_category_non_recursive("Number",a,b-1) == 1 && length == 2) { length = 1; return 1; }
	if (parent->is_category_non_recursive("Complement",a,b+2) == 1 && length == 2) { length = 1; return 1; }
  
   
	if (length == 2) {
		if (parent->is_category_non_recursive("Jiang01",a,b+1) == 1) { return 1; }
    	}


	// Unify Word
        if (length == 1) { return 1; }
	if (length >= 2) { shift_post_chinese(parent,a,b+1,0,this); myclass+=":Person"; parent->make_only(a,b,this); }
	if (length >= 3) { shift_post_chinese(parent,a,b+1,0,this); post_chinese->post_pinyin_spacing = 0; parent->make_only(a,b,this); }
        if (length > 1) {
	  int not_present = 1;
	  std::string tempb = return_chinese();
	  for (int b = 0; b < parent->memory->names->size(); b++) {
            if (parent->memory->names->at(b) == tempb) {
              not_present = 0;
            }
          }
          if (not_present == 1) {
	    parent->memory->names->push_back(tempb);
          }
	}	

 
	std::string temppin = return_pinyin_no_spacing();
	if (xing_pinyin.length() < temppin.length()) {
		temppin = temppin.substr(xing_pinyin.length());
	}

	if (temppin.length() > 0) { temppin[0] = toupper(temppin[0]); }
	if (pinyin.length() > 0) { pinyin[0] = toupper(pinyin[0]); }
        pinyin += " " + temppin;
	pinyin_generated = 1;

	// Add this name to our collective memory
	//if (length > 1) { parent->text->memory->insert_name(return_chinese(parent));}
	return 1;

}





std::string Name::return_english() {

	std::string temp = "";
	if (name != "") {
		temp = name; 
		if (pre_english_spacing == 1) { temp = " " + temp; }
		if (post_english_spacing == 1) { temp = temp + " "; }
		return temp;
	}

  	english = return_pinyin();


	while (english.find("1") != std::string::npos) { english = english.substr(0, english.find("1")) + english.substr(english.find("1")+1); }
	while (english.find("2") != std::string::npos) { english = english.substr(0, english.find("2")) + english.substr(english.find("2")+1); }
	while (english.find("3") != std::string::npos) { english = english.substr(0, english.find("3")) + english.substr(english.find("3")+1); }
	while (english.find("4") != std::string::npos) { english = english.substr(0, english.find("4")) + english.substr(english.find("4")+1); }
	while (english.find("5") != std::string::npos) { english = english.substr(0, english.find("5")) + english.substr(english.find("5")+1); }


	if (english.length() >= 1) { english[0] = toupper(english[0]); }

	int loca = english.find(" ");
	while (loca != std::string::npos) { 
		std::string cappre = english.substr(0, english.find(" "));
		std::string cappost = english.substr(english.find(" ")+1); 
		if (cappost.length() >= 1) { 
			cappost[0] = toupper(cappost[0]);
		}
		english = cappre + " " + cappost;
		loca = english.find(" ", loca+1);
	}

	temp = english;

	if (possessive == 1) { temp += "'s"; }	
	if (pre_english_spacing == 1) { temp = " " + temp; }
	if (post_english_spacing == 1) { temp = temp + " "; }
	if (pre_english != NULL) { temp = pre_english->return_english() + temp; }
	if (post_english != NULL) { temp += post_english->return_english(); }
	if (post_english_spacing == 1) { temp = temp + " "; }
	

	return temp;

}


std::string Name::return_english_no_spacing() {

	int temp = post_english_spacing = 0;
	std::string temp2 = return_english();
	post_english_spacing = temp;
	return temp2;

}



