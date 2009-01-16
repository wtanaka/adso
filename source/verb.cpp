#include "verb.h"
#include "text.h"
#include "memory.h"
#include "adjective.h"


Verb::Verb(Text *t): Unit(t) { myclass += ":Verb";};
Verb::~Verb() {}


int Verb::unify(Text *t, int a, int b, int c) {

	if (flag.find("SENTINTR") != std::string::npos) { myclass += ":SentIntr"; }

	// Identify Components
	std::string next = t->return_chinese(a,b+1);
	for (int i = 0; i < t->memory->complements->size(); i++) {
		if (next == t->memory->complements->at(i)) {
			t->shift_post_chinese_to_all_category(a,b,"Verb",t->elements->at(a)->at(b+1)->at(0));
			t->remove_element(a,b+1);
			t->make_only(a,b,"Verb");
			break;
		}
	}
	next = t->return_chinese(a,b+1);
	for (int i = 0; i < t->memory->tense->size(); i++) {
		if (next == t->memory->tense->at(i)) {
			t->shift_post_chinese_to_all_category(a,b,"Verb",t->elements->at(a)->at(b+1)->at(0));
			t->remove_element(a,b+1);
			t->make_only(a,b,"Verb");
			break;
		}
	}
	next = t->return_chinese(a,b-1);
	for (int i = 0; i < t->memory->predecessors->size(); i++) {
		if (next == t->memory->predecessors->at(i)) {
			if (next.find("被") != std::string::npos) {
				english = conjugate(return_english_no_spacing(),5);
				add_pre_english("to be");
			}
			t->shift_pre_chinese_to_all_category(a,b,"Verb",t->elements->at(a)->at(b-1)->at(0));
			t->remove_element(a,b-1); b--;
			t->make_only(a,b,"Verb");
			break;
		}
	}




	// Doubled Verbs
	if (t->return_chinese(a,b+1) == return_chinese() ) {
		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);
	}




	// Verbs Mascarading as Adjectives
	if (t->is_category("Noun",a,b+1) == 1 && t->is_category("Directional",a,b+2) == 1) {
		if (t->is_category("Adjective",a,b) == 1) { 
			t->make_only(a,b,"Adjective");
			return -1;
			should_translate = 0;
		}
	}





	// Differentiating Verb-Nouns
	if (b == 0) {
		if (t->is_category("Noun",a,b) == 1) {
			t->add_confidence("Noun", 1,a,b);
		}
	}




	// more / less
	if (t->return_chinese(a,b-1) == "多") {
		if (t->is_category_non_recursive("Cadverb",a,b-2) != 1) {
			shift_pre_chinese(t,a,b-1,0,this); b--;
			if (t->return_chinese(a,b+1) == "一点") {
				shift_post_chinese(t,a,b+1,0,this);
				add_post_english(" a little");
			}
			add_post_english(" more");
			t->make_only(a,b,this);
		}
	}

	if (t->return_chinese(a,b-1) == "少") {
		if (t->is_category_non_recursive("Cadverb",a,b-2) != 1) {
			shift_pre_chinese(t,a,b-1,0,this); b--;
			if (t->return_chinese(a,b+1) == "一点") {
				shift_post_chinese(t,a,b+1,0,this);
				add_post_english(" a little");
			}
			add_post_english(" less");
			t->make_only(a,b,this);
		}
	}

	if (t->return_chinese(a,b+1) == "多") {
		shift_post_chinese(t,a,b+1,0,this);
		if (t->return_chinese(a,b+1) == "一点") {
			shift_post_chinese(t,a,b+1,0,this);
			add_post_english(" a little");
		}
		add_post_english(" more");
		t->make_only(a,b,this);
	}
	if (t->return_chinese(a,b+1) == "少") {
		shift_post_chinese(t,a,b+1,0,this);
		if (t->return_chinese(a,b+1) == "一点") {
			shift_post_chinese(t,a,b+1,0,this);
			add_post_english(" a little");
		}
		add_post_english(" more");
		t->make_only(a,b,this);
	}
	if (t->return_chinese(a,b+1) == "一点") {
		shift_post_chinese(t,a,b+1,0,this);
		add_post_english(" a bit");
		t->make_only(a,b,this);
	}



	if (return_chinese().find("被") != std::string::npos) {
		if ((b == 0 && t->is_category("Noun",a,b+1) == 1) || (t->is_category("Noun",a,b+1) == 1 || (t->is_category("De01",a,b+1) == 1 && t->is_category("Noun",a,b+2) == 1))) {
			if (t->is_category("Noun",a,b-1) != 1) {
				// Change to an Adjective
				std::string temp = return_english();
				if (temp.find("to be") == 0) {
					if (temp.length() > 6) {
						Adjective *tempadj = new Adjective(this);
						this->clone_values(tempadj);
						tempadj->english = temp.substr(6);
						t->elements->at(a)->at(b)->push_back(tempadj);
						t->make_only(a,b,tempadj);
						return -1;
					}
				}
			}
		}
	}




	if (myclass.find("SentIntr") != std::string::npos && (t->is_category_non_recursive("Person",a,b-1) == 1 || t->is_category("Pronoun",a,b-1) == 1 || t->is_category("ProperNoun",a,b-1) == 1)) {
		t->make_only(a,b,"Verb");
		t->make_only(a,b-1,"Noun");
	}

	if (t->return_chinese(a,b-1) == "都")   { t->make_only(a,b-1,"Other"); }
	if (t->return_chinese(a,b-1) == "也")   { t->make_only(a,b-1,"Other"); }
	if (t->return_chinese(a,b-1) == "大都") { t->make_only(a,b-1,"Other"); }


	if (t->is_only_category_non_recursive("Adjective",a,b-1) == 1 && t->is_only_category_non_recursive("Verb",a,b) == 1) { vtense = 2; }



	// Put Verbs in the Imperative if they start a Sentence
	if (b == 0 || t->is_category_non_recursive("Terminal",a,b-1) == 1) { conj = 5; if (pinyin == "ye3 shi4") { conj = 3; } }



	// Almost Certainly A Verb
	if (t->return_chinese(a,b-1) == "乱") {
		t->shift_pre_chinese_to_all_category(a,b,"Verb",t->elements->at(a)->at(b-1)->at(0));
		t->remove_element(a,b-1); b--;
		add_pre_english("crudely");
		t->make_only(a,b,"Verb");
	}





	if (t->return_chinese(a,b-1) == "一") {
		if (t->is_category_non_recursive("Determiner",a,b-2) != 1 && t->is_category_non_recursive("Noun",a,b-2) == 1 && t->is_category_non_recursive("Measure",a,b) != 1) {
			if (t->return_chinese(b-2) == return_chinese()) {
				t->shift_pre_chinese_to_all_category(a,b,"Verb",t->elements->at(a)->at(b-1)->at(0));
				t->shift_pre_chinese_to_all_category(a,b,"Verb",t->elements->at(a)->at(b-2)->at(0));
				t->remove_element(a,b-1); b--;
				t->remove_element(a,b-1); b--;
				t->make_only(a,b,"Verb");
				for (int i = 0; i < t->elements->at(a)->at(b)->size(); i++) {
					t->elements->at(a)->at(b)->at(i)->add_post_english("a little");
				}
			} else {
				t->shift_pre_chinese_to_all_category(a,b,"Verb",t->elements->at(a)->at(b-1)->at(0));
				for (int i = 0; i < t->elements->at(a)->at(b)->size(); i++) {
					t->elements->at(a)->at(b)->at(i)->add_pre_english("immediately upon");
					t->elements->at(a)->at(b)->at(i)->vtense = 2;
				}
				vtense = 2;
				t->remove_element(a,b-1); b--;
				t->make_only(a,b,"Verb");
				t->add_confidence("Noun",2,a,b-1);
			}
		}
	}


	return 1;
}

int Verb::adjust_confidence(Text *t, int a, int b, int c) {

	if (
		t->is_category_non_recursive("Noun",a,b-1) == 1 &&
		t->is_category_non_recursive("Punctuation",a,b-2) == 1
	) {
 		confidence += 0.5;
	}

	if (
		t->is_category_non_recursive("Noun",a,b-1) == 1 &&
		t->is_category_non_recursive("Noun",a,b+1) == 1 &&
		t->is_category_non_recursive("Preposition",a,b+2) == 1
	) {
		t->make_only(a,b-1,"Noun");
		t->make_only(a,b,"Verb");
		t->make_only(a,b+1,"Noun");
		//if (t->is_category_non_recursive("Wei01",a,b+2) != 1) {
		//	t->make_only(a,b+2,"Preposition");
		//}
	}

  	if (t->is_category_non_recursive("Noun",a,b-1) == 1 && t->is_category_non_recursive("Measure",a,b-2) == 1) {
		t->add_confidence("Noun",1,a,b-1);
		t->add_confidence("Measure",1,a,b-2);
		confidence++;
	}


	if (t->is_category_non_recursive("Unit",a,b+1) != 1) {
		confidence+=1;
	}
	if (t->is_category_non_recursive("Terminal",a,b+1) == 1) {
		confidence+=1;
	}

	if (t->is_category_non_recursive("Pronoun",a,b-1) == 1) {
		confidence+=1;
		t->add_confidence("Pronoun",1,a,b-1);
	}
	if (t->is_category_non_recursive("Comma",a,b+1) == 1) {
		confidence+=1;
	}
	if (t->is_category_non_recursive("Auxiliary",a,b-1) == 1) {
		t->add_confidence("Auxiliary",5,a,b-1);
		confidence+=2;
	}
	if (t->is_category_non_recursive("Adjective",a,b+1) == 1) {
		confidence++;
	}
	if (t->is_category_non_recursive("Adverb",a,b-1) == 1) {
		t->add_confidence("Adverb",2,a,b-1);
		confidence++;
	}
	if (t->is_category_non_recursive("Comma",a,b-1) == 1 && t->is_category_non_recursive("Noun",a,b+1) == 1) {
		confidence+=2;
	}
	if (t->is_category_non_recursive("Auxiliary",a,b-1) == 1 && t->is_category_non_recursive("Adverb",a,b-2) == 1) {
		t->add_confidence("Auxiliary",5,a,b-1);
		t->add_confidence("Adverb",5,a,b-2);
		confidence+=2;
	}
	if (t->is_category_non_recursive("De02",a,b+1) == 1 && t->is_category_non_recursive("Adverb",a,b+2) == 1 && t->is_category_non_recursive("Adjective",a,b+3) == 1) {
		t->make_only(a,b+1,t->text(a,b+1,"De02"));
		t->make_only(a,b+2,t->text(a,b+2,"Adverb"));
		t->make_only(a,b+3,t->text(a,b+3,"Adjective"));
		if (t->is_category_non_recursive("Adjective",a,b+3) == 1) {
			// turn our adjective into an adverb 
			Text *temp = t->text(a,b+3,"Adjective");
			if (temp->pinyin == "hao3") {
				temp->english = "well";
			} else {
				temp->english = temp->return_english_no_spacing() + "ly";
			}
			temp->myclass += "Unit:Adverb";
			t->make_only(a,b+3,temp);
		}
		shift_post_chinese(t,a,b+1,0,this);
		shift_post_chinese(t,a,b+1,0,this);
		add_post_english(" " + t->likely(a,b+1)->return_english());
		shift_post_chinese(t,a,b+1,0,this);
		t->make_only(a,b,this);
	}
	if (t->is_category_non_recursive("De02",a,b+1) == 1 && t->is_category_non_recursive("Adverb",a,b+2) != 1 && t->is_category_non_recursive("Adjective",a,b+3) != 1) {
		t->make_only(a,b,"De02");
	}
	if (t->is_category_non_recursive("De02",a,b+1) == 1 && t->is_category_non_recursive("Adjective",a,b+2) == 1) {
		t->make_only(a,b+1,t->text(a,b+1,"De02"));
		t->make_only(a,b+2,t->text(a,b+1,"Adjective"));
		t->make_only(a,b,this);
	}


	if (	
		t->return_chinese(a,b+1,0) == "及"
	) {
		if (t->is_category_non_recursive("Verb",a,b+2) == 1) {
			t->make_only(a,b,this);
			t->make_only(a,b+1,"Conjunction");
			t->make_only(a,b+2,"Verb");
		}
	}

	if (t->return_chinese(a,b,c) == "令人") {
		if (t->is_category_non_recursive("Xing",a,b+1) == 1) {
			t->shift_post_chinese_to_all_category(a,b,"Verb",t->text(a,b+1,"Xing"));
			english = "to make people feel";
			add_post_english(" " + t->text(a,b+1,"Xing")->return_english());
			t->remove_element(a,b+1);
			return 1;
		}
		if (t->is_category_non_recursive("Adjective",a,b+1) == 1) {
			t->shift_post_chinese_to_all_category(a,b,"Verb",t->text(a,b+1,"Adjective"));
			english = "to make people feel";
			add_post_english(" " + t->text(a,b+1,"Adjective")->return_english());
			t->remove_element(a,b+1);
			return 1;
		}

		if (t->is_category_non_recursive("Verb",a,b+1) == 1) {
			t->shift_post_chinese_to_all_category(a,b,"Verb",t->text(a,b+1,"Verb"));
			english = "to cause people";
			add_post_english(" " + t->text(a,b+1,"Verb")->return_english());
			t->remove_element(a,b+1);
			return 1;
		}
	}


	if (t->return_chinese(a,b-2,0) == "进行" && t->is_category_non_recursive("Adverb",a,b-1) == 1) {
		add_pre_english(t->text(a,b-1,"Adverb")->return_english());
		add_pre_english("to start");
		t->shift_post_chinese_to_all_category(a,b,"Verb",t->text(a,b-1,"Verb"));
		t->shift_post_chinese_to_all_category(a,b,"Verb",t->text(a,b-2,"Verb"));
		t->remove_element(a,b-1); b--;
		t->remove_element(a,b-1); b--;
	}
	if (t->return_chinese(a,b-1,0) == "进行") {
		add_pre_english("to start");
		t->shift_post_chinese_to_all_category(a,b,"Verb",t->text(a,b-2,"Verb"));
		t->remove_element(a,b-1); b--;
	}






 	if (t->return_chinese(a,b+1,0) == "不") {
 		if (t->return_chinese(a,b+2,0) == "起") {
			if (t->return_chinese(a,b+4,0) == "来") {
				add_pre_english("not");
				add_post_english(" " + t->likely(a,b+3)->return_english());
				t->shift_post_chinese(t,a,b+1,0,this);	
				t->shift_post_chinese(t,a,b+1,0,this);	
				t->shift_post_chinese(t,a,b+1,0,this);	
				t->shift_post_chinese(t,a,b+1,0,this);	
			}
		}
	}
 	if (t->return_chinese(a,b+1,0) == "不") {
 		if (t->return_chinese(a,b+2,0) == "起") {
			add_pre_english("not");
			t->shift_post_chinese(t,a,b+1,0,this);	
			t->shift_post_chinese(t,a,b+1,0,this);	
			t->make_only(a,b,this);
		}
	}



/*
	// Some Cool Unifications -- "to sell best", etc.
	if (sentence->is_category(location+1, "De02") == 1 && sentence->is_category(location+2, "Cadverb") == 1 && sentence->is_category(location+3, "Bu01") == 1 && sentence->is_category(location+4, "Adjective") == 1){
		add_post_component(sentence->return_unit(location+1, "De02"));
		sentence->remove_word(location+1);
		add_post_component(sentence->return_unit(location+1, "Cadverb"));
		sentence->remove_word(location+1);
		add_post_component(sentence->return_unit(location+1, "Bu01"));
		add_post_english(sentence->return_english_output_encoding(location+1));
		add_post_english("not");
		add_post_component(sentence->return_unit(location+1, "Adjective"));
		add_post_english(sentence->return_english_output_encoding(location+1));
		sentence->remove_word(location+1);
		sentence->make_only(location, "Verb");
	}
	if (sentence->is_category(location+1, "De02") == 1 && sentence->is_category(location+2, "Cadverb") == 1 && sentence->is_category(location+3, "Adjective") == 1){
		add_post_component(sentence->return_unit(location+1, "De02"));
		sentence->remove_word(location+1);
		add_post_component(sentence->return_unit(location+1, "Cadverb"));
		sentence->remove_word(location+1);
		add_post_component(sentence->return_unit(location+1, "Adjective"));
		add_post_english(sentence->return_english_output_encoding(location+1));
		sentence->remove_word(location+1);
		sentence->make_only(location, "Verb");
	}
*/

	return 1;

}

/* alter tenses and other delightful forms of advanced analysis */
int Verb::advanced(Text *t, int a, int b, int c) {

	if (t->is_category_non_recursive("Date",a,b-1) == 1) {
		if (t->is_category_non_recursive("Person",a,b-2) == 1) {
		 	confidence += 1;
		}
	}
	if (t->is_category_non_recursive("Auxiliary",a,b-1) == 1) {
		vtense = 12;
	}
	if (t->is_category_non_recursive("Auxiliary",a,b-2) == 1) {
		if (t->is_category_non_recursive("Verb",a,b-1) != 1 && t->is_category_non_recursive("Preposition",a,b-1) != 1) {
			vtense = 12;
		}
	}

	return 1;
}








std::string Verb::return_english() {
  if (post_english_spacing == 1) {
	  return conjugate(Text::return_english_no_spacing()) + " ";
  } else {
	  return conjugate(Text::return_english_no_spacing());
  }
}




