#include "orguess.h"
#include "organization.h"
#include "text.h"
#include "encoding.h"

Orguess::Orguess(Text *t): Organization(t) { myclass += ":Orguess";};
Orguess::~Orguess() {}

int Orguess::unify(Text *t, int a, int b, int c) {


	for (int i = 0, z = 1; i < 6; i++) {
		if (
			(t->is_category_non_recursive("Noun",a,b-1) == 1 ||
			 t->is_category_non_recursive("Phonetic",a,b-1) == 1 ||
			 t->encoding->character_length(t->text(a,b-1,0)->return_chinese_input_encoding()) == 1
			) && 
			t->is_category_non_recursive("Special",a,b-1) != 1 &&
			t->is_category_non_recursive("Punctuation",a,b-1) != 1 &&
			t->is_category_non_recursive("Preposition",a,b-1) != 1 && 
			t->is_category_non_recursive("Measure",a,b-1) != 1 &&
			(t->is_category_non_recursive("Verb",a,b-1) != 1 && t->is_category_non_recursive("Adverb",a,b-2) != 1) &&
			(t->is_category_non_recursive("Verb",a,b-1) != 1 && t->is_category_non_recursive("Auxiliary",a,b-2) != 1) &&
			t->is_category_non_recursive("Determiner",a,b-1) != 1
		) {

			int toadd = t->encoding->character_length(t->text(a,b-1,0)->return_chinese_input_encoding());

			if (toadd == 1) {

	std::string temp = t->likely(a,b-1)->return_pinyin_no_spacing();
	while (temp.find("1") != std::string::npos) { temp = temp.substr(0, temp.find("1")) + temp.substr(temp.find("1")+1); }
	while (temp.find("2") != std::string::npos) { temp = temp.substr(0, temp.find("2")) + temp.substr(temp.find("2")+1); }
	while (temp.find("3") != std::string::npos) { temp = temp.substr(0, temp.find("3")) + temp.substr(temp.find("3")+1); }
	while (temp.find("4") != std::string::npos) { temp = temp.substr(0, temp.find("4")) + temp.substr(temp.find("4")+1); }
	while (temp.find("5") != std::string::npos) { temp = temp.substr(0, temp.find("5")) + temp.substr(temp.find("5")+1); }




			if (temp.length() > 0) { temp[0] = toupper(temp[0]); }
				add_pre_english(temp);
			} else {
				
				if (t->is_category_non_recursive("Verb",a,b-1) == 1 || t->is_category_non_recursive("Adverb",a,b-1) == 1 || t->is_category_non_recursive("Auxiliary",a,b-1) == 1) { i+=10; break; }		

				add_pre_english(" ");
				std::string temp = t->likely(a,b-1)->return_english_no_spacing();
				if (temp.length() > 0) { temp[0] = toupper(temp[0]); }
				add_pre_english(temp);
			}
			shift_pre_chinese(t,a,b-1,0,this); b--;
			t->make_only(a,b,this);
		} else {i += 10; }
	}



	return 1;
}



