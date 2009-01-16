#include "zhen01.h"
#include "special.h"
#include "text.h"
#include "encoding.h"
#include "memory.h"


Zhen01::Zhen01(Text *t): Special(t) { myclass += ":Zhen01";};
Zhen01::~Zhen01() {}


int Zhen01::unify(Text *t, int a, int b, int c) {

  std::string previous_word = t->text(a,b-1,0)->return_chinese();
  int length_of_previous_word = t->encoding->character_length(t->text(a,b-1,0)->return_chinese_input_encoding());
  int generate_name = 0;


  // This is probably a county name if.... the last two characters make sense contextually 
  if (length_of_previous_word == 1) {
      if (t->encoding->character_length(t->text(a,b-2,0)->return_chinese_input_encoding()) == 1) {
	english = t->text(a,b-1,0)->return_pinyin() + t->text(a,b-2,0)->return_pinyin();
	shift_pre_chinese(t,a,b-1,0,this); b--;
	shift_pre_chinese(t,a,b-1,0,this); b--;
 	t->make_only(a,b,this);
 	myclass += ":Place:Township";
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
 		myclass += ":Place:Township";
		generate_name = 1;
	}
    }
  }






  if (generate_name == 1) {
	english = generate_township_name() + " township";
  }



  return 1;

}


std::string Zhen01::generate_township_name() {

	english = stripped_of_tones(english);
	if (english.length() > 0) {
		english[0] = toupper(english[0]);
	}
	while (english.find(" ") != std::string::npos) { english = english.substr(0, english.find(" ")) + english.substr(english.find(" ")+1); }
	
	return english;
}


