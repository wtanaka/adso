#include "phonetic.h"
#include "unit.h"
#include "text.h"


Phonetic::Phonetic(Text *t): Unit(t) { myclass += ":Phonetic";};
Phonetic::~Phonetic() {}


std::string Phonetic::return_english() {

  if (english != "") { return english; }

  english = return_pinyin();

  while (english.find("1") != std::string::npos) { english = english.substr(0, english.find("1")) + english.substr(english.find("1")+1); }
  while (english.find("2") != std::string::npos) { english = english.substr(0, english.find("2")) + english.substr(english.find("2")+1); }
  while (english.find("3") != std::string::npos) { english = english.substr(0, english.find("3")) + english.substr(english.find("3")+1); }
  while (english.find("4") != std::string::npos) { english = english.substr(0, english.find("4")) + english.substr(english.find("4")+1); }
  while (english.find("5") != std::string::npos) { english = english.substr(0, english.find("5")) + english.substr(english.find("5")+1); }
  while (english.find(" ") != std::string::npos) { english = english.substr(0, english.find(" ")) + english.substr(english.find(" ")+1); }

  if (english.length() > 0) {
    english[0] = toupper(english[0]);
  }

  return english;

}

int Phonetic::unify(Text *parent, int a, int b, int c) {


	english = "";

	if (parent->is_category_non_recursive("Country",a,b+1) == 1 && parent->is_category_non_recursive("Country",a,b) == 1) { return 1; }
	if (parent->is_category_non_recursive("Xing",a,b) == 1 && parent->is_category_non_recursive("Cadverb",a,b-1) == 1) { return 1; }

	if (parent->is_category_non_recursive("Person",a,b-1) == 1) {
		if (parent->is_category_non_recursive("Directional",a,b) != 1) {
			shift_pre_chinese(parent,a,b-1,0,this);
			b--;
			parent->make_only(a,b,this);
		} else {
			if (parent->is_category_non_recursive("Phonetic",a,b+1) == 1) {
				shift_post_chinese(parent,a,b+1,"Phonetic",this);
				parent->make_only(a,b,this);
			}
		}
	}
	while (parent->is_category_non_recursive("Phonetic",a,b+1) == 1 || parent->is_category_non_recursive("Person",a,b+1) == 1) {
		// Ignore Countries
		if (parent->is_category_non_recursive("Country",a,b) == 1 && parent->is_category_non_recursive("Country",a,b+1) == 1) { return 1; }
		if (parent->is_category_non_recursive("He01",a,b+1) == 1) { return 1; }
		if ( (parent->is_category_non_recursive("Directional",1,b+1) == 1 || parent->is_category_non_recursive("Temporal",a,b+1) == 1) && parent->is_category_non_recursive("Phonetic",a,b+2) != 1) { return 1; }
		shift_post_chinese(parent,a,b+1,0,this);
		myclass += ":Place:ProperNoun";
		parent->make_only(a,b,this);
	}

	return 1;
}


int Phonetic::combine(Text *parent, int a, int b, int c) {

	if ((parent->is_category_non_recursive("Dot",a,b-1) == 1 || parent->return_chinese(a,b-1) == "-")&& (parent->is_category_non_recursive("Person",a,b-2) == 1 || parent->is_category_non_recursive("Phonetic",a,b-2) == 1 || parent->is_category_non_recursive("Place",a,b-2) == 1) ) {
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			shift_pre_chinese(parent,a,b-1,0,this); b--;
			parent->make_only(a,b,this);
	}

	return 1;
}



