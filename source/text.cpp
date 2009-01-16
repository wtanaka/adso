#include "text.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>


#include "unit.h"
#include "adso.h"
#include "code.h"
#include "encoding.h"
#include "feedback.h"
#include "memory.h"
#include "ontology.h"
#include "parser.h"
#include "polisher.h"

using namespace std;







// Constructor and Destructor
Text::Text(Text *t) {
  init(t->adso, t->code, t->encoding, t->feedback, t->memory, t->ontology, t->parser, t->polisher);
  asciify_punctuation = t->asciify_punctuation;
  split_nonchinese_on_punctuation = t->split_nonchinese_on_punctuation;
};
Text::Text(Text *t, Text *a, Text *b) {
  init(t->adso, t->code, t->encoding, t->feedback, t->memory, t->ontology, t->parser, t->polisher);

  chinese = a->return_chinese() + b->return_chinese();
  chinese_utf8s = a->return_chinese_utf8s() + b->return_chinese_utf8s();
  chinese_utf8c = a->return_chinese_utf8c() + b->return_chinese_utf8c();
  pinyin = a->return_pinyin() + b->return_pinyin();
  jyutpin = a->return_jyutpin() + b->return_jyutpin();
  asciify_punctuation = a->asciify_punctuation;
  split_nonchinese_on_punctuation = a->split_nonchinese_on_punctuation;

  capitalize = a->capitalize;

  if (a->pre_english != NULL) { add_pre_english(a->pre_english->return_english()); }
  if (b->pre_english != NULL) { add_pre_english(b->pre_english->return_english()); }
  if (a->post_english != NULL) { add_post_english(a->post_english->return_english()); }
  if (b->post_english != NULL) { add_post_english(b->post_english->return_english()); }

};
void Text::clone_values(Text *x) {
  x->english = return_english_no_spacing();
  x->chinese = return_chinese();
  x->chinese_utf8s = return_chinese_utf8s();
  x->chinese_utf8c = return_chinese_utf8c();
  x->pinyin = return_pinyin_no_spacing();
  x->jyutpin = return_jyutpin_no_spacing();
  x->asciify_punctuation = asciify_punctuation;
  x->split_nonchinese_on_punctuation = split_nonchinese_on_punctuation;
  return;
}
void Text::append_clone_values(Text *x) {
  x->english += return_english();
  x->chinese += return_chinese();
  x->chinese_utf8s += return_chinese_utf8s();
  x->chinese_utf8c += return_chinese_utf8c();
  x->pinyin += return_pinyin();
  x->jyutpin += return_jyutpin();
  x->asciify_punctuation = asciify_punctuation;
  x->split_nonchinese_on_punctuation = split_nonchinese_on_punctuation;
  return;
}



Text::Text(Adso *a, Code *c, Encoding *e, Feedback *f, Memory *m, Ontology *o, Parser *pa, Polisher *po) {
  init(a,c,e,f,m,o,pa,po);
};
Text::~Text() {

	// Clear and Delete Elements
	for (unsigned int i = 0; i < elements->size(); i++) {
	  for (unsigned int ii = 0; ii < elements->at(i)->size(); ii++) {
	    for (unsigned int iii = 0; iii < elements->at(i)->at(ii)->size(); iii++) {
              delete elements->at(i)->at(ii)->at(iii);
            }
	    elements->at(i)->at(ii)->clear();
            delete elements->at(i)->at(ii);
          }
	  elements->at(i)->clear();
	  delete elements->at(i);
        } 
	elements->clear();
	delete elements;

	delete field_english;
	delete field_pinyin;
	delete field_pkey;
	delete field_newstrack;
	delete field_code;
	delete field_rank;

	// Clear and delete pre and post elements/components
	delete pre_english;
	delete post_english;
	delete pre_chinese;
	delete post_chinese;

};
int Text::init(Text *t) {
  init(t->adso, t->code, t->encoding, t->feedback, t->memory, t->ontology, t->parser, t->polisher);
  asciify_punctuation = t->asciify_punctuation;
  split_nonchinese_on_punctuation = t->split_nonchinese_on_punctuation;
  return 1;
}
int Text::init(Adso *a, Code *c, Encoding *e, Feedback *f, Memory *m, Ontology *o, Parser *pa, Polisher *po) {

	// Variables for End-Unit Elements
	myclass = "";
	flag = "";

	frequency_int = 0;
	frequency_float = 0;

	integer_representation = 0;
	decimal_representation = 0;

	full_definitions = 0;

	split_nonchinese_on_punctuation = 0;
	asciify_punctuation = 0;

	table = "";

	code_analysed = 0;	

	should_translate = 1;

	pre_english_spacing = 0;
	post_english_spacing = 0;
	pre_pinyin_spacing = 0;
	post_pinyin_spacing = 0;

	generate_spacing = "";

	chinese = "";
	chinese_utf8s = "";
	chinese_utf8c = "";
	chinese_big5 = "";
	pinyin = "";
	jyutpin = "";

	english = "";
	spanish = "";
	french = "";
	german = "";
	italian = "";
	japanese = "";
	arabic = "";
	russian = "";
	portuguese = "";
	korean = "";
	hebrew = "";
	farsi = "";

	location = -1;
	beginning = 0;
	ending = 0;
	capitalize = 0;

	html_class = "";
	html_id = "";
	html_href = "";
	html_src = "";

	confidence = 0;
	probability = 0;

	plural = 0;
	negative = 0;
	possessive = 0;
	vtense = -1;  // not set yet. list of values in verb.cpp conjugate function
	conj = 0;

	field_english = new std::vector<std::string>;
	field_pinyin = new std::vector<std::string>;
	field_code = new std::vector<std::string>;
	field_pkey = new std::vector<std::string>;
	field_newstrack = new std::vector<std::string>;
	field_rank = new std::vector<double>;


	// Initialize Variables
	adso = a;
	code = c;
	encoding = e;
	feedback = f;
	memory = m;
	ontology = o;
	parser = pa;
	polisher = po;

	pre_chinese = NULL;
	post_chinese = NULL;
	pre_english = NULL;
	post_english = NULL;

	elements = new std::vector<std::vector<std::vector<Text *> *> *>;

	return 1;
}

int Text::init_markup(std::string t) {

	fulltext = t;
	fulltext_gb2312 = "";

	/* Unless we know the encoding of this chunk of text
	 * we ask the encoding class to analyse it for us. And
      	 * set the variables in the encoding class appropriately.
	 * We should only need to do this once for any text we 
	 * analyse.
	 */
	parser->parse_textbook_markup(this);

	return 1;
}
int Text::init_text(std::string t) {

	fulltext = t;
	fulltext_gb2312 = "";

	/* Unless we know the encoding of this chunk of text
	 * we ask the encoding class to analyse it for us. And
      	 * set the variables in the encoding class appropriately.
	 * We should only need to do this once for any text we 
	 * analyse.
	 */
        if (encoding->input_encoding == 0 || encoding->input_script == 0) {
                int existing_output_encoding = encoding->output_encoding;
                int existing_output_script = encoding->output_script;

                encoding->analyse_encoding(this);

                if (existing_output_encoding != 0) { encoding->output_encoding = existing_output_encoding; }
                if (existing_output_script != 0) { encoding->output_script = existing_output_script; }
        }

	parser->parse(this);

	return 1;
}




int Text::sentence_forward_word_match(std::string word, int a, int b) {
  for (int i = 0; i < elements->size(); i++) {
    for (int ii = b+1; ii < b+20 && ii < elements->at(i)->size(); ii++) {
      if (return_chinese(i, ii, 0).find(word) != std::string::npos) { 
	return ii;
}
      if (is_category_non_recursive("Terminal", a, ii) == 1) { return -1; }
    }
  } 
  return -1;
}
int Text::sentence_backward_word_match(std::string word, int a, int b) {
  for (int i = 0; i < elements->size(); i++) {
    for (int ii = b-1; ii >= 0 && ii > b-20; ii--) {
      if (return_chinese(i, ii, 0).find(word) != std::string::npos) { return ii; }
      if (is_category_non_recursive("Terminal", i, ii) == 1) { return -1; }
    }
  } 
  return -1;
}
int Text::sentence_forward_category_match(std::string category, int a, int b) {
  for (int i = 0; i < elements->size(); i++) {
    for (int ii = b+1; ii < b+20 && ii < elements->at(i)->size(); ii++) {
      if (is_category(category, i, ii) == 1) { return ii; }
      if (is_category_non_recursive("Terminal", i, ii) == 1) { return -1; }
    }
  } 
  return -1;
}
int Text::sentence_backward_category_match(std::string category, int a, int b) {
  for (int i = 0; i < elements->size(); i++) {
    for (int ii = b-1; ii >= 0 && ii > b-20; ii--) {
      if (is_category(category, i, ii) == 1) { return ii; }
      if (is_category_non_recursive("Terminal", i, ii) == 1) { return -1; }
    }
  } 
  return -1;
}
// this is only used in nonchinese.cpp for the open-ended and backward matching
// of HTML/XML tags. Note that we will search backwards to the start of the document
// if no matches are found earlier (inefficient). And also that this is a complex
// match rather than a simple match. We provide two strings. It much match the first
// but not the second.
int Text::sentence_backward_html_match_complex(std::string is_a_category, std::string is_not_a_category, int a, int b) {
  for (int i = 0; i < elements->size(); i++) {
    for (int ii = b-1; ii >= 0; ii--) {
      if (is_category(is_a_category, i, ii) != -1 && is_category(is_not_a_category, i, ii) == -1) { return ii; }
    }
  } 
  return -1;
}






int Text::is_category(std::string category) {
  if (myclass.find(category) != std::string::npos) { return 1; }
  if (elements->size() > 0) {
    for (int i = 0; i < elements->size(); i++) {
    for (int ii = 0; ii < elements->at(i)->size(); ii++) {
    for (int iii = 0; iii < elements->at(i)->at(ii)->size(); iii++) {
      if (elements->at(i)->at(ii)->at(iii)->is_category(category) == 1) { return 1; }
    }
    }
    }
  }
  return 0;
}
int Text::is_category(std::string category, int a) {
  if (myclass.find(category) != std::string::npos) { return 1; }
  if (elements->size() > 0) {
    for (int ii = 0; ii < elements->at(a)->size(); ii++) {
    for (int iii = 0; iii < elements->at(a)->at(ii)->size(); iii++) {
      if (elements->at(a)->at(ii)->at(iii)->is_category(category) == 1) { return 1; }
    }
    }
  }
  return 0;
}
int Text::is_category(std::string category, int a, int b) {
  if (elements->size() < a+1 || a < 0) { return -1; }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1; }
  for (unsigned int ii = 0; ii < elements->at(a)->at(b)->size(); ii++) {
    if (elements->at(a)->at(b)->at(ii)->is_category(category) == 1) {
      return 1;
    }
  }
  return -1;
}
int Text::is_only_category_non_recursive(std::string category, int a, int b) {
  if (elements->size() < a+1 || a < 0) { return -1; }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1; }
  for (unsigned int ii = 0; ii < elements->at(a)->at(b)->size(); ii++) {
    if (elements->at(a)->at(b)->at(ii)->myclass.find(category) == std::string::npos) {
      return -1;
    }
  }
  if (elements->at(a)->at(b)->at(0)->myclass.find(category) != std::string::npos) { return 1; }
  return -1;
}
int Text::is_category(std::string category, int a, int b, int c) {
  if (elements->size() < a+1 || a < 0) { return -1; }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1; }
  if (elements->at(a)->at(b)->size() < c+1 || c < 0) { return -1; }
  if (elements->at(a)->at(b)->at(c)->is_category(category) == 1) {
    return 1;
  }
  return -1;
}
int Text::is_category_non_recursive(std::string category) {
  if (myclass.find(category) != std::string::npos) { return 1; }
  return 0;
}
int Text::is_category_non_recursive(std::string category, int a) {
  if (elements->size() < a+1) { return -1; }
  for (unsigned int i = 0; i < elements->at(a)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(a)->at(i)->size(); ii++) {
      if (elements->at(a)->at(i)->at(ii)->is_category_non_recursive(category) == 1) {
        return 1;
      }
    }
  }
  return -1;
}
int Text::is_category_non_recursive(std::string category, int a, int b) {
  if (elements->size() < a+1 || a < 0) { return -1; }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1; }
  for (unsigned int i = 0; i < elements->at(a)->at(b)->size(); i++) {
    if (elements->at(a)->at(b)->at(i)->is_category_non_recursive(category) == 1) {
      return 1;
    }
  }
  return -1;
}
int Text::is_category_non_recursive(std::string category, int a, int b, int c) {
  if (elements->size() < a+1 || a < 0) { return -1; }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1; }
  if (elements->at(a)->at(b)->size() < c+1) { return -1; }
  if (elements->at(a)->at(b)->at(c)->is_category_non_recursive(category) == 1) {
    return 1;
  }
  return -1;
}
int Text::append_text(Text *t, int a, int b) {
  if (elements->size() < a+1) { return -1; }
  if (elements->at(a)->size() < b+1) { return -1; }
  elements->at(a)->at(b)->push_back(t);
  return 1;
}
int Text::tag(std::string category, int a, int b) {
  if (elements->size() < a+1 || a < 0) { return -1; }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1; }
  for (unsigned int i = 0; i < elements->at(a)->at(b)->size(); i++) {
    elements->at(a)->at(b)->at(i)->myclass += ":" + category;
  }
  return 1;
}









std::string Text::debug() {
  std::string debug = "";
  if (elements->size() == 0) { return ""; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {


      
	if (encoding->output_encoding == 1) {
      if (ii == 0) {
        std::cout << elements->at(0)->at(i)->at(ii)->return_chinese() <<"\t" << elements->at(0)->at(i)->at(ii)->myclass << "\t" << elements->at(0)->at(i)->at(ii)->flag << "\t" << elements->at(0)->at(i)->at(ii)->confidence << "\t" << i << "\n";
      } else {
        std::cout << "..." << elements->at(0)->at(i)->at(ii)->return_chinese() <<"\t" << elements->at(0)->at(i)->at(ii)->myclass << "\t" << elements->at(0)->at(i)->at(ii)->flag << "\t" << elements->at(0)->at(i)->at(ii)->confidence << "\t" << i << "\n";
      }
        }

        // UTF8 Simplified
        if (encoding->output_encoding == 2 && encoding->output_script == 1) {
      if (ii == 0) {
        std::cout << elements->at(0)->at(i)->at(ii)->return_chinese_utf8s() <<"\t" << elements->at(0)->at(i)->at(ii)->myclass << "\t" << elements->at(0)->at(i)->at(ii)->flag << "\t" << elements->at(0)->at(i)->at(ii)->confidence << "\t" << i << "\n";
      } else {
        std::cout << "..." << elements->at(0)->at(i)->at(ii)->return_chinese_utf8s() <<"\t" << elements->at(0)->at(i)->at(ii)->myclass << "\t" << elements->at(0)->at(i)->at(ii)->flag << "\t" << elements->at(0)->at(i)->at(ii)->confidence << "\t" << i << "\n";
      }
        }

        // UTF8 Traditional
        if (encoding->output_encoding == 2 && encoding->output_script == 2) {
      if (ii == 0) {
        std::cout << elements->at(0)->at(i)->at(ii)->return_chinese_utf8c() <<"\t" << elements->at(0)->at(i)->at(ii)->myclass << "\t" << elements->at(0)->at(i)->at(ii)->flag << "\t" << elements->at(0)->at(i)->at(ii)->confidence << "\t" << i << "\n";
      } else {
        std::cout << "..." << elements->at(0)->at(i)->at(ii)->return_chinese_utf8c() <<"\t" << elements->at(0)->at(i)->at(ii)->myclass << "\t" << elements->at(0)->at(i)->at(ii)->flag << "\t" << elements->at(0)->at(i)->at(ii)->confidence << "\t" << i << "\n";
      }
        }
    }
  }
  return debug;
}



std::string Text::return_chinese(int b) {
  if (elements->size() == 0) { return ""; }
  if (elements->at(0)->size()-1 < b) { return ""; }
  return likely(0,b)->return_chinese();
}
std::string Text::return_chinese(int a, int b) {
  if (elements->size() == 0) { return ""; }
  if (elements->at(a)->size()-1 < b) { return ""; }
  return likely(a,b)->return_chinese();
}
std::string Text::return_chinese(int a, int b, int c) {
  if (elements->size() == 0) { return ""; }
  if (elements->at(a)->size()-1 < b) { return ""; }
  if (elements->at(a)->at(b)->size()-1 < c) { return ""; }
  return elements->at(a)->at(b)->at(c)->return_chinese();
}
std::string Text::return_gb2312_popup() {

  std::string results = "";
  std::string p = "";
  std::string e = "";
  std::string s = "";
  std::string t = "";

  if (elements->size() == 0) {
        post_english_spacing = 0;
        post_pinyin_spacing = 0;
	s = return_chinese();
	t = s;
	e = return_english_no_spacing();
	p = return_pinyin_no_spacing();

	e = escape_apostrophes(e);
	p = escape_apostrophes(p);

        results = "<span onclick=\"onWordClick()\" class=\"gb2312\" onmouseover=\"tip(event,'"+e+"','"+p+"','"+s+"','"+t+"')\" onmouseout=\"htip()\">"+s+"</span>";
  } else {
    for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
        results += likely(0, i)->return_gb2312_popup();
    }
  }
  return results;
}
std::string Text::return_gb2312_popup_for_editing(int edit_element) {

  std::string results = "";
  std::string p = "";
  std::string e = "";
  std::string s = "";
  std::string t = "";

  std::stringstream myStream1;
  myStream1 << edit_element;
  std::string element_id = myStream1.str();

  if (elements->size() == 0) {
        post_english_spacing = 0;
        post_pinyin_spacing = 0;
	s = return_chinese();
	t = s;
	e = return_english_no_spacing();
	p = return_pinyin_no_spacing();

	e = escape_apostrophes(e);
	p = escape_apostrophes(p);

        results = "<span ";
	results +="id=\"adso_" + element_id + "\" class=\"gb2312\" onclick=\"onWordClick()\" onmouseover=\"tip(event,'"+e+"','"+p+"','"+s+"','"+t+"','"+element_id+"')\" onmouseout=\"htip()\">"+s+"</span>";
  } else {
    for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
        edit_element += encoding->word_length(likely(0, i)->return_chinese_utf8s(), "utf8");
        results += likely(0, i)->return_gb2312_popup_for_editing(edit_element);
    }
  }
  return results;
}
std::string Text::return_popup() {

  std::string results = "";
  std::string p = "";
  std::string e = "";
  std::string s = "";
  std::string t = "";

  if (elements->size() == 0) {
        post_english_spacing = 0;
        post_pinyin_spacing = 0;
	s = return_chinese_utf8s();
	t = return_chinese_utf8c();
	if (encoding->input_script == 2) {
		t = s;
		s = return_chinese_utf8c();
	}
	e = return_english_no_spacing();
	p = return_pinyin_no_spacing();

	e = escape_apostrophes(e);
	p = escape_apostrophes(p);

        results = "<span onclick=\"onWordClick()\" onmouseover=\"tip(event,'"+e+"','"+p+"','"+s+"','"+t+"')\" onmouseout=\"htip()\">"+s+"</span>";
  } else {
    for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
        results += likely(0, i)->return_popup();
    }
  }
  return results;
}
std::string Text::return_popup_for_editing(int edit_element) {

  std::string results = "";
  std::string p = "";
  std::string e = "";
  std::string s = "";
  std::string t = "";

  std::stringstream myStream1;
  myStream1 << edit_element;
  std::string element_id = myStream1.str();

  if (elements->size() == 0) {
        post_english_spacing = 0;
        post_pinyin_spacing = 0;
	s = return_chinese_utf8s();
	t = return_chinese_utf8c();
	e = return_english_no_spacing();
	p = return_pinyin_no_spacing();

	e = escape_apostrophes(e);
	p = escape_apostrophes(p);

        results = "<span ";
	results +="id=\"adso_" + element_id + "\" onclick=\"onWordClick()\" onmouseover=\"tip(event,'"+e+"','"+p+"','"+s+"','"+t+"','"+element_id+"')\" onmouseout=\"htip()\">"+s+"</span>";
  } else {
    for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
        edit_element += encoding->word_length(likely(0, i)->return_chinese_utf8s(), "utf8");
        results += likely(0, i)->return_popup_for_editing(edit_element);
    }
  }
  return results;
}
std::string Text::return_popup_for_editing_five_fields(int edit_element) {

  std::string results = "";
  std::string p = "";
  std::string e = "";
  std::string s = "";
  std::string t = "";

  std::stringstream myStream1;
  myStream1 << edit_element;
  std::string element_id = myStream1.str();

  if (elements->size() == 1 && edit_element == 1) {
    if (elements->at(0)->size() == 1) {
      if (is_category_non_recursive("NonChinese",0,0) == 1) {
        results = "<span ";
	results +="id=\"adso_" + element_id + "\" onclick=\"onWordClick()\" onmousedown=\"adso_mousedown('"+element_id+"')\" onmouseup=\"adso_mouseup('"+element_id+"')\">"+return_chinese_utf8s()+"</span>";
	return results;
      }
    }
  }

  if (elements->size() == 0) {
        post_english_spacing = 0;
        post_pinyin_spacing = 0;
	s = return_chinese_utf8s();
	t = return_chinese_utf8c();
	e = return_english_no_spacing();
	p = return_pinyin_no_spacing();

	e = escape_apostrophes(e);
	p = escape_apostrophes(p);
	s = escape_apostrophes(s);
	t = escape_apostrophes(t);

	if (e == "\"") { 
		e = s; 
		p = s;
		s = s;
		t = s;
	}

        

        results = "<span ";
	results +="id=\"adso_" + element_id + "\" onclick=\"onWordClick()\" onmousedown=\"adso_mousedown('"+element_id+"')\" onmouseup=\"adso_mouseup('"+element_id+"')\" onmouseover=\"tip(event,'"+e+"','"+p+"','"+s+"','"+t+"','','"+element_id+"')\" onmouseout=\"htip()\">"+apostrophes_to_html(s)+"</span>";


  } else {
    for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
        edit_element += encoding->word_length(likely(0, i)->return_chinese_utf8s(), "utf8");
        results += likely(0, i)->return_popup_for_editing_five_fields(edit_element);
    }
  }
  return results;
}

std::string Text::return_chinese() {

  std::string results = "";
  std::string post = "";
  std::string pre = "";

  if (pre_chinese != NULL) { pre += pre_chinese->return_chinese(); }
  if (post_chinese != NULL) { post += post_chinese->return_chinese(); }

  if (chinese != "") { return pre + chinese + post; }
  if (elements->size() == 0) { return pre + "" + post; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
      results += likely(0, i)->return_chinese();
  }
  return pre + results + post;
}
std::string Text::return_chinese_utf8s() {

  std::string results = "";
  std::string post = "";
  std::string pre = "";

  if (pre_chinese != NULL) { pre += pre_chinese->return_chinese_utf8s(); }
  if (post_chinese != NULL) { post += post_chinese->return_chinese_utf8s(); }

  if (chinese_utf8s != "") { return pre + chinese_utf8s + post; }
  if (elements->size() == 0) { return pre + "" + post; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
      results += likely(0, i)->return_chinese_utf8s();
  }
  return pre + results + post;




  return chinese;
}
std::string Text::return_chinese_utf8c() {

  std::string results = "";
  std::string post = "";
  std::string pre = "";


  if (pre_chinese != NULL) { pre += pre_chinese->return_chinese_utf8c(); }
  if (post_chinese != NULL) { post += post_chinese->return_chinese_utf8c(); }

  if (chinese_utf8c != "") { return pre + chinese_utf8c + post; }
  if (elements->size() == 0) { return pre + generate_chinese_utf8c() + post; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
      results += likely(0, i)->return_chinese_utf8c();
  }
  return pre + results + post;
}
std::string Text::return_segmented_chinese() {
  if (elements->size() == 0) { return ""; }
  std::string output = "";
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    if (i > 0) { output += " "; }
    output += likely(0,i)->return_chinese_output_encoding();
  }

  return output;

}
std::string Text::return_vocab_list() {
  if (elements->size() == 0) { return ""; }

  std::vector<std::string> *vocab_list = new std::vector<std::string>;
  std::string output = "";
  

  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    vocab_list->push_back(likely(0,i)->return_chinese_utf8s() + "\t" + likely(0,i)->return_pinyin() + "\t" + likely(0,i)->return_english() + "\t" + likely(0,i)->myclass );
  }

  for (int i = 0; i < vocab_list->size(); i++) {
    output += vocab_list->at(i) + "<br/>\n";
  }

  delete vocab_list;
  return output;

}
std::string Text::return_vocab_list_with_traditional() {
  if (elements->size() == 0) { return ""; }

  std::vector<std::string> *vocab_list = new std::vector<std::string>;
  std::string output = "";

  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    vocab_list->push_back(likely(0,i)->return_chinese_utf8c() + "\t" + likely(0,i)->return_pinyin() + "\t" + likely(0,i)->return_english() + "\t" + likely(0,i)->myclass );
  }

  for (int i = 0; i < vocab_list->size(); i++) {
    output += vocab_list->at(i) + "<br/>\n";
  }

  delete vocab_list;
  return output;

}
std::string Text::return_english_no_spacing() {

  if (should_translate == 0) { return ""; }

  std::string results = "";
  std::string post = "";
  std::string pre = "";

  if (pre_english != NULL) { pre += pre_english->return_english(); }
  if (post_english != NULL) { post += post_english->return_english(); }
  if (english != "") { 
    results += pre;
    if (vtense != -1) { results = conjugate(english); }
    if (possessive == 1) { results = make_possessive(english); }
    if (plural == 1) { results = pluralize(english); }
    if (plural == 1 && possessive == 1) { results = make_possessive(pluralize(english)); }
    if (vtense == -1 && plural == 0 && possessive == 0) { results += english; }
    results += post;
    return results;
  }
  if (plural == 1) { 
	if (english != "") { return pre + pluralize(english) + post; } 
  }
  else { 
	if (english != "") { return pre + english + post; } 
  }
  if (elements->size() == 0) { return pre + "" + post; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
      results += likely(0, i)->return_english();
  }
  if (plural == 1) { return pre + pluralize(results) + post; }
  return pre + results + post;
}
int Text::plural_next_noun(int a, int b, int plural_value) {
  if (elements->size() == 0) { return -1; }
  if (elements->at(0)->size()-1 < b) { return -1; }
  for (int i = 1; i < 10; i++) {
    if (is_category_non_recursive("Noun",a,b+i) == 1 && is_category_non_recursive("Adjective",a,b+i) != 1) {
	for (int z = 0; z < elements->at(a)->at(b+i)->size(); z++) {
		elements->at(a)->at(b+i)->at(z)->set_plural(plural_value);
	}
	return b+i;
    } else {}
  }
  return -1;
}
std::string Text::make_possessive(std::string a) {
	return a + "'s";
}
int Text::set_possessive(int a) {
	possessive = a;
	return 1;
}
int Text::set_plural(int a) {
	plural = a;
	return 1;
}
std::string Text::return_english() {

  if (should_translate == 0) { return ""; }

  std::string results = "";
  std::string post = "";
  std::string pre = "";


  if (pre_english != NULL) { pre += pre_english->return_english(); }
  if (post_english != NULL) { post += post_english->return_english(); }
  if (english != "") { 
    results += pre;
    if (pre_english_spacing == 1) { results += " "; }
      else { results += english; }
    if (plural == 1) { results = pluralize(results); }
    if (possessive == 1) { results = make_possessive(results); }
    if (post_english_spacing == 1) { results += " "; }
    results += post;
    return results;
  }

  if (plural == 1) { if (english != "") { return pre + pluralize(english) + post; } }
  else { if (english != "") { return pre + english + post; } }
  if (elements->size() == 0) { return pre + "" + post; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
      results += likely(0, i)->return_english();
  }
  if (plural == 1) { return pre + pluralize(results) + post; }
  results = pre + results + post;
  if (possessive == 1) { results = make_possessive(results); }
  return results;
}
std::string Text::return_jyutpin() {

  std::string results = "";
  std::string post = "";
  std::string pre = "";

  // Pre Components
  if (pre_chinese != NULL) { pre += pre_chinese->return_jyutpin(); }
  if (post_chinese != NULL) { post += post_chinese->return_jyutpin(); }

  if (pinyin != "") { 
    results += pre;
    if (pre_pinyin_spacing == 1) { results += " "; }
    results += pinyin;
    if (post_pinyin_spacing == 1) { results += " "; }
    results += post;
    return results;
  }

  if (jyutpin != "") { return pre + jyutpin + post; }
  if (elements->size() == 0) { return pre + "" + post; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
      results += likely(0, i)->return_jyutpin();
  }
  return pre + results + post;
}
std::string Text::return_jyutpin_no_spacing() {

  std::string results = "";
  std::string post = "";
  std::string pre = "";

  // Pre Components
  if (pre_chinese != NULL) { pre += pre_chinese->return_jyutpin_no_spacing(); }
  if (post_chinese != NULL) { post += post_chinese->return_jyutpin_no_spacing(); }

  if (pinyin != "") { 
    results += pre;
    results += pinyin;
    results += post;
    return results;
  }

  if (jyutpin != "") { return pre + jyutpin + post; }
  if (elements->size() == 0) { return pre + "" + post; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
      results += likely(0, i)->return_jyutpin_no_spacing();
  }
  return pre + results + post;
}
std::string Text::generate_chinese() {
  std::string reseg1 = return_chinese_input_encoding();
  int totalwordlength = encoding->character_length(reseg1);
  int split_distance = 1;
  if (totalwordlength == 1) { return "UNKNOWN"; }
  if (totalwordlength >= 4) { split_distance = 2; }
  std::string myformer = "";
  std::string mylatter = "";
  int chunk = 0;
  for (unsigned int z = 0; z < split_distance && reseg1 != ""; z++) {
    chunk += encoding->first_character_length(reseg1);
  }
  if (chunk > reseg1.length()) { return "UNKNOWN"; }
  myformer = reseg1.substr(0, chunk);
  mylatter = reseg1.substr(chunk);
  Text *text4swap1 = new Text(this);
  text4swap1->init_text(myformer);
  Text *text4swap2 = new Text(this);
  text4swap2->init_text(mylatter);
  std::string revised_pinyin = text4swap1->return_chinese() + " " + text4swap2->return_chinese();
  delete text4swap1;
  delete text4swap2;
  chinese = revised_pinyin;
  return revised_pinyin;
}
std::string Text::generate_chinese_utf8s() {
  std::string reseg1 = return_chinese_input_encoding();
  int totalwordlength = encoding->character_length(reseg1);
  int split_distance = 1;
  if (totalwordlength == 1) { return "UNKNOWN"; }
  if (totalwordlength >= 4) { split_distance = 2; }
  std::string myformer = "";
  std::string mylatter = "";
  int chunk = 0;
  for (unsigned int z = 0; z < split_distance && reseg1 != ""; z++) {
    chunk += encoding->first_character_length(reseg1);
  }
  if (chunk > reseg1.length()) { return "UNKNOWN"; }
  myformer = reseg1.substr(0, chunk);
  mylatter = reseg1.substr(chunk);
  Text *text4swap1 = new Text(this);
  text4swap1->init_text(myformer);
  Text *text4swap2 = new Text(this);
  text4swap2->init_text(mylatter);
  std::string revised_pinyin = text4swap1->return_chinese_utf8s() + " " + text4swap2->return_chinese_utf8s();
  delete text4swap1;
  delete text4swap2;
  chinese_utf8s = revised_pinyin;
  return revised_pinyin;
}
std::string Text::generate_chinese_utf8c() {
  std::string reseg1 = return_chinese_input_encoding();
  int totalwordlength = encoding->character_length(reseg1);
  int split_distance = 1;
  if (totalwordlength == 1) { return "unknown"; }
  if (totalwordlength >= 4) { split_distance = 2; }
  std::string myformer = "";
  std::string mylatter = "";
  int chunk = 0;
  for (unsigned int z = 0; z < split_distance && reseg1 != ""; z++) {
    chunk += encoding->first_character_length(reseg1);
  }
  if (chunk > reseg1.length()) { return "unknown"; }
  myformer = reseg1.substr(0, chunk);
  mylatter = reseg1.substr(chunk);
  Text *text4swap1 = new Text(this);
  text4swap1->init_text(myformer);
  Text *text4swap2 = new Text(this);
  text4swap2->init_text(mylatter);
  std::string revised_pinyin = text4swap1->return_chinese_utf8c() + text4swap2->return_chinese_utf8c();
  delete text4swap1;
  delete text4swap2;
  chinese_utf8c = revised_pinyin;
  return revised_pinyin;
}
std::string Text::generate_pinyin() {
  if (is_category_non_recursive("ProperNoun") == 1) {
    return generate_pinyin("");
  } else {
    return generate_pinyin(" ");
  }
}
std::string Text::generate_pinyin(std::string spacing) {
  std::string reseg1 = return_chinese_input_encoding();
  int totalwordlength = encoding->character_length(reseg1);
  int split_distance = 1;
  if (totalwordlength == 0) { return ""; }
  if (totalwordlength == 1) { return return_chinese_output_encoding(); }
  if (totalwordlength == 2) { spacing = ""; }
  if (totalwordlength == 3) { split_distance = 1; }
  if (totalwordlength >= 4) { split_distance = 2; }
  if (totalwordlength > 4) { spacing = " "; } // phrases most likely
  std::string myformer = "";
  std::string mylatter = "";
  int temp_chunk = 0;
  int chunk = 0;
  for (unsigned int z = 0; z < split_distance && reseg1 != ""; z++) {
    temp_chunk = encoding->first_character_length(reseg1);
    chunk += temp_chunk;
    reseg1 = reseg1.substr(temp_chunk);
  }
  reseg1 = return_chinese_input_encoding();
  if (chunk > reseg1.length()) { return "UNKNOWN"; }
  myformer = reseg1.substr(0, chunk);
  mylatter = reseg1.substr(chunk);
  Text *text4swap1 = new Text(this);
  text4swap1->init_text(myformer);
  Text *text4swap2 = new Text(this);
  text4swap2->init_text(mylatter);
  std::string revised_pinyin = "";


  if  (spacing == "") {
    revised_pinyin = text4swap1->return_pinyin_no_spacing() + spacing + text4swap2->return_pinyin_no_spacing();
  } else {
    revised_pinyin = text4swap1->return_pinyin() + spacing + text4swap2->return_pinyin();
  }

  delete text4swap1;
  delete text4swap2;
  pinyin = revised_pinyin;
  return revised_pinyin;
}
std::string Text::return_pinyin_no_spacing() {

  std::string results = "";
  std::string post = "";
  std::string pre = "";

  // Pre Components
  if (pre_chinese != NULL) { pre += pre_chinese->return_pinyin_no_spacing(); }
  if (post_chinese != NULL) { post += post_chinese->return_pinyin_no_spacing(); }


  if (pinyin != "") { 
    results += pre;
    results += pinyin;
    results += post;
    return results;
  }

  /* Generate Pinyin Generates the Pinyin Using PRE and POST Elements Automatically */
  //if (elements->size() == 0) { return pre + generate_pinyin() + post; }
  if (elements->size() == 0) { return generate_pinyin(); }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    results += likely(0, i)->return_pinyin_no_spacing();
  }
  return pre + results + post;
}
std::string Text::return_pinyin() {

  std::string results = "";
  std::string post = "";
  std::string pre = "";

  // Pre Components
  if (pre_chinese != NULL) { pre += pre_chinese->return_pinyin(); }
  if (post_chinese != NULL) { post += post_chinese->return_pinyin(); }

  if (pinyin != "") { 
    results += pre;
    if (pre_pinyin_spacing == 1) { results += " "; }
    results += pinyin;
    if (post_pinyin_spacing == 1) { results += " "; }
    results += post;
    return results;
  }

  /* Generate Pinyin Generates the Pinyin Using PRE and POST Elements Automatically */
  //if (elements->size() == 0) { return pre + generate_pinyin() + post; }
  if (elements->size() == 0) { return generate_pinyin(); }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    results += likely(0, i)->return_pinyin();
  }
  return pre + results + post;
}
std::string Text::return_chinese_input_encoding() {
  if (encoding->input_encoding == 1) { return return_chinese(); }
  if (encoding->input_encoding == 2) {
    if (encoding->input_script == 1) { return return_chinese_utf8s(); }
    if (encoding->input_script == 2) { return return_chinese_utf8c(); }
    return return_chinese_utf8s(); 
  }
  return return_chinese();
}

std::string Text::return_chinese_output_encoding() {
  if (encoding->output_encoding == 1) { return return_chinese(); }
  if (encoding->output_encoding == 2) {
    if (encoding->output_script == 1) { return return_chinese_utf8s(); }
    if (encoding->output_script == 2) { return return_chinese_utf8c(); }
    return return_chinese_utf8s(); 
  }
  return return_chinese();
}



int Text::likely(int b) {
  int a = 0;
  if (elements->at(0)->size() < b+1) { throw "Asked to return non-existing text unit"; return 0; }
  int highest = 0;
  double highest_conf = -200;
  double my_conf = -200;
  for (unsigned int ii = 0; ii < elements->at(0)->at(b)->size(); ii++) {
    my_conf = elements->at(0)->at(b)->at(ii)->confidence;
    if (my_conf > highest_conf) { highest = ii; highest_conf = my_conf; }
  }
  return highest;
}
Text * Text::likely(int a, int b) {
  if (elements->size() < a+1) { throw "Asked to return non-existing text unit"; return NULL; }
  if (elements->at(a)->size() < b+1) { throw "Asked to return non-existing text unit"; return NULL; }
  int highest = 0;
  double highest_conf = -200;
  double my_conf = -200;
  for (unsigned int ii = 0; ii < elements->at(a)->at(b)->size(); ii++) {
    my_conf = elements->at(a)->at(b)->at(ii)->confidence;
    if (my_conf > highest_conf) { highest = ii; highest_conf = my_conf; }
  }
  return elements->at(a)->at(b)->at(highest);
}





Text * Text::text(int a, int b, std::string c) {
  if (elements->size() < a+1) { throw "Asked to return non-existing text unit"; return NULL; }
  if (elements->at(a)->size() < b+1) { throw "Asked to return non-existing text unit"; return NULL; }
  for (int unsigned i = 0; i < elements->at(a)->at(b)->size(); i++) {
    if (elements->at(a)->at(b)->at(i)->is_category_non_recursive(c) == 1) {
      return elements->at(a)->at(b)->at(i);
    }
  }
  throw "Error - Text asked to return text element that does not exist";
  return NULL;
}
Text * Text::text(int a, int b, int c) {
  if (elements->size() < a+1) { throw "Asked to return non-existing text unit"; return NULL; }
  if (elements->at(a)->size() < b+1) { throw "Asked to return non-existing text unit"; return NULL; }
  if (elements->at(a)->size() < c+1) { throw "Asked to return non-existing text unit"; return NULL; }
  return elements->at(a)->at(b)->at(c);
}





























/* Functions for End Unit Analysis */
int Text::pre_unify(Text *parent) {
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->pre_unify(this, 0, i, ii);
    }
  }
  } catch (...) { return -1; }
  return 1;
}
int Text::pre_unify(Text *parent, int a, int b, int c) {return 1;};

int Text::unify(Text *parent) {
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->unify(this, 0, i, ii);
    }
  }
  } catch (...) { return -1; }
  return 1;
}
int Text::unify(Text *parent, int a, int b, int c) {return 1;};

int Text::post_unify(Text *parent) {
  if (elements->size() == 0) { return -1; }
  try {
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->post_unify(this, 0, i, ii);
    }
  }
  } catch (...) {}
  return 1;
}
int Text::post_unify(Text *parent, int a, int b, int c) {return 1;};

int Text::combine(Text *parent) {
  if (elements->size() == 0) { return -1; }
  try {
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->combine(this, 0, i, ii);
    }
  }
  } catch (...) {}
  return 1;
}
int Text::combine(Text *parent, int a, int b, int c) {return 1;};

int Text::combine2(Text *parent) {
  if (elements->size() == 0) { return -1; }
  try {
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->combine2(this, 0, i, ii);
    }
  }
  } catch (...) {}
  return 1;
}
int Text::combine2(Text *parent, int a, int b, int c) {return 1;};

int Text::adjust_confidence(Text *parent) {
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->adjust_confidence(this, 0, i, ii);
    }
  }
  } catch (...) {}
  return 1;
}
int Text::adjust_confidence(Text *parent, int a, int b, int c) {return 1;};

int Text::identify_html_entities(Text *parent) {
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->identify_html_entities(this, 0, i, ii);
    }
  }
  } catch (...) {}
  return 1;
}
int Text::identify_html_entities(Text *parent, int a, int b, int c) {return 1;};

int Text::advanced(Text *parent) {
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->advanced(this, 0, i, ii);
    }
  }
  } catch (...) { return -1; } 
  return 1;
}
int Text::advanced(Text *parent, int a, int b, int c) {return 1;};

int Text::grammar(Text *parent) {
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int j = 0; j < elements->size(); j++) {
    for (unsigned int i = 0; i < elements->at(j)->size(); i++) {
      for (unsigned int ii = 0; ii < elements->at(j)->at(i)->size(); ii++) {
       elements->at(j)->at(i)->at(ii)->grammar(this, 0, i, ii);
      }
    }
  }
  } catch (...) { return -1; }
  return 1;
}
int Text::grammar(Text *parent, int a, int b, int c) {return 1;};

int Text::run_code(Text *parent) {
  int preceding_size = 0;
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int j = 0; j < elements->size(); j++) {
    int old_size = elements->at(j)->size();
    for (unsigned int i = 0; i < old_size; i++) {
      int old_size2 = elements->at(j)->at(i)->size();
      try {
      for (unsigned int ii = 0; ii < old_size2; ii++) {
	preceding_size = old_size2;
        int test = elements->at(j)->at(i)->at(ii)->run_code(this, j, i, ii);
	if (test == -2) { ii=old_size2+10; }
      }
      } catch (...) { 
      }
    }
  }
  } catch (...) { 
	return -1; 
  }
  return 1;
}
int Text::run_code(Text *parent, int a, int b, int c) {
  int trigger = 0;
  try {
    for (int z = 0; z < field_code->size(); z++) {
     if (field_code->at(z) != "") {
      int x = code->analyse_code(parent,field_code->at(z),a,b,c);
      if (x == -2) { return -2; }
     }
    } 
    if (elements->size() > 0) { run_code(this); }
  } catch (...) { return -2; }
  return 1;
};

int Text::adjust_spacing(Text *parent) {
  try {
  if (elements->size() == 0) { return -1; }
  for (unsigned int j = 0; j < elements->size(); j++) {
    for (unsigned int i = 0; i < elements->at(j)->size(); i++) {
      for (unsigned int ii = 0; ii < elements->at(j)->at(i)->size(); ii++) {
        elements->at(j)->at(i)->at(ii)->adjust_spacing(this, 0, i, ii);
      }
    }
  }
  } catch (...) { return -1; }
  return 1;
}
int Text::adjust_spacing(Text *parent, int a, int b, int c) {return 1;};








int Text::add_confidence(double benefit) {
	confidence += benefit;
	return 1;
}
int Text::add_confidence(std::string category, double benefit, int a, int b, int c) {
  if (myclass.find(category) != std::string::npos) { add_confidence(benefit); return -1; }
  if (elements->size() < a+1 || a < 0) { return -1; }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1;  }
  if (elements->at(a)->at(b)->size() < c+1 || c < 0) { return -1; }
  elements->at(a)->at(b)->at(c)->add_confidence(benefit);
  return 1;
}
int Text::add_confidence(std::string category, double benefit, int a, int b) {
  if (myclass.find(category) != std::string::npos) { add_confidence(benefit); return 1; }
  if (elements->size() < a+1 || a < 0) { return -1;  }
  if (elements->at(a)->size() < b+1 || b < 0) { return -1; }
  for (int i = 0; i < elements->at(a)->at(b)->size(); i++) {
    if (elements->at(a)->at(b)->at(i)->is_category(category) == 1) {
      elements->at(a)->at(b)->at(i)->add_confidence(benefit);
    }
  }
  return 1;
}










void Text::switch_units(int a, int b1, int b2) {

  if (elements->size() < a+1) { return; }
  if (elements->at(a)->size() < b1+1) { return; }
  if (elements->at(a)->size() < b2+1) { return; }
  if (b1 < 0 || b2 < 0) { return; }

  std::vector<Text *> *first = elements->at(a)->at(b1);
  std::vector<Text *> *second = elements->at(a)->at(b2);

  elements->at(a)->at(b1) = second;
  elements->at(a)->at(b2) = first;

  return;
}
int Text::resegment(int a, int b, int distance) {

  if (elements->size() < a+1) { return -1; }
  if (elements->at(a)->size() < b+1) { return -1; }
  std::string reseg1 = text(a,b,0)->return_chinese_input_encoding();
  std::string reseg2 = reseg1;

  if (elements->at(a)->at(b)->size() < b+2) {} else { reseg2 += text(a,b+1,0)->return_chinese_input_encoding(); }

  std::string myformer = "";
  std::string mylatter = "";


  int chunk = 0;
  for (unsigned int z = 0; z < distance && reseg1 != ""; z++) {
    chunk += encoding->first_character_length(reseg1);
  }

  if (chunk > reseg1.length()) { return -1; }

  myformer = reseg1.substr(0, chunk);
  mylatter = reseg1.substr(chunk);



  // Check Our Resegmentation Logic Holds
  /* Ambiguous resegmentation commands can cause looping, resulting in the same 
   * character attempting to resegment itself after a larger word has already
   * been resegmented. This can be avoided by checking to see if we in fact 
   * have anything to split up, and quitting if not.
   */
  if (myformer == "") { return -1; }
  if (mylatter == "") { return -1; }



  // we only delete the current unit we are resegmenting
  remove_element(a, b);
  if (elements->at(a)->at(b)->size() > 0) {
    mylatter += text(a,b,0)->return_chinese_input_encoding();
    remove_element(a, b);
  }
  
  Text *text4swap1 = new Text(this);
  text4swap1->init_text(myformer);

  Text *text4swap2 = new Text(this);
  text4swap2->init_text(mylatter);





  // Insert Last Elements First  
  int text4swapsize = text4swap2->elements->at(0)->size();
  for (unsigned int y = 0; y < text4swapsize; y++) {
    elements->at(a)->insert(elements->at(a)->begin()+b+y, text4swap2->elements->at(0)->at(y));
    text4swap2->elements->at(0)->at(y) = new std::vector<Text *>;
  }

  // The the First Word
  text4swapsize = text4swap1->elements->at(0)->size();
  for (unsigned int y = 0; y < text4swapsize; y++) {
    elements->at(a)->insert(elements->at(a)->begin()+b+y, text4swap1->elements->at(0)->at(y));
    text4swap1->elements->at(0)->at(y) = new std::vector<Text *>;
  }

  delete text4swap1;
  delete text4swap2;




  return 1;
}

int Text::remove_element(int a, int b) {
  if (elements->size()-1 < a) { return -1; }
  if (elements->at(a)->size()-1 < b) { return -1; }
  // Delete Internal Texts
  for (unsigned int iii = 0; iii < elements->at(a)->at(b)->size(); iii++) {
    delete elements->at(a)->at(b)->at(iii);
  }
  elements->at(a)->at(b)->clear();
  delete elements->at(a)->at(b);
  elements->at(a)->erase(elements->at(a)->begin()+b);
  return 1;
}

/* used to shift elements  */
int Text::shift_post_chinese(Text *source, int a, int b, std::string category, Text *destination) {
  if (source->elements->size()-1 < a) { return -1; }
  if (source->elements->at(a)->size()-1 < b) { return -1; }
  for (unsigned int i = 0; i < source->elements->at(a)->at(b)->size(); i++) {
    if (source->elements->at(a)->at(b)->at(i)->is_category_non_recursive(category) == 1) {
      shift_post_chinese(source, a, b, i, destination);
      return 1;
    }
  }
  return -1;
}
int Text::shift_post_chinese(Text *source, int a, int b, int c, Text *destination) {
  if (source->elements->size()-1 < a) { return -1; }
  if (source->elements->at(a)->size()-1 < b) { return -1; }
  if (source->elements->at(a)->at(b)->size()-1 < c) { return -1; }

  Text *temp = source->elements->at(a)->at(b)->at(c);
  source->elements->at(a)->at(b)->at(c) = new Text(this);

  // Erase
  for (unsigned int h = 0; h < source->elements->at(a)->at(b)->size(); h++) {
    delete source->elements->at(a)->at(b)->at(h); 
  }
  source->elements->at(a)->at(b)->clear();
  delete source->elements->at(a)->at(b);
  source->elements->at(a)->erase(source->elements->at(a)->begin()+b);

  // Relocate in our New Vector
  destination->add_post_chinese(temp); 

  return 1;
}
/* used to shift elements */
int Text::shift_pre_chinese(Text *source, int a, int b, int c, Text *destination) {
  if (source->elements->size()-1 < a) { return -1; }
  if (source->elements->at(a)->size()-1 < b) { return -1; }
  if (source->elements->at(a)->at(b)->size()-1 < c) { return -1; }

  Text *temp = source->elements->at(a)->at(b)->at(c);
  source->elements->at(a)->at(b)->at(c) = new Text(this);


  // Erase
  for (unsigned int h = 0; h < source->elements->at(a)->at(b)->size(); h++) {
    delete source->elements->at(a)->at(b)->at(h); 
  }
  source->elements->at(a)->at(b)->clear();
  delete source->elements->at(a)->at(b);
  source->elements->at(a)->erase(source->elements->at(a)->begin()+b);

  /* Removing this cauess reduplicated pinyin in output. I'm not sure why! */
  temp->return_pinyin();



  // Relocate in our New Vector
  destination->add_pre_chinese(temp); 

  return 1;
}
int Text::shift_pre_chinese(Text *source, int a, int b, std::string category, Text *destination) {
  if (source->elements->size()-1 < a) { return -1; }
  if (source->elements->at(a)->size()-1 < b) { return -1; }
  for (unsigned int i = 0; i < source->elements->at(a)->at(b)->size(); i++) {
    if (source->elements->at(a)->at(b)->at(i)->is_category_non_recursive(category) == 1) {
      shift_pre_chinese(source, a, b, i, destination);
      return 1;
    }
  }
  return -1;
}
int Text::adjust_confidence(double x) {
  confidence += x;
  return 1;
}
int Text::adjust_probability(double x) {
  probability += x;
  return 1;
}




std::string Text::output() {
  return "Output";
}
std::string Text::translate() {
  return "";
}
std::string Text::popup() {
  std::string html = "";
  return html;
}








// Manipulating Pre/Post Chinese and English Texts
void Text::add_pre_chinese_non_spaced(Text *x) {

	if (pre_chinese == NULL) {
		pre_chinese = x;
		x->post_pinyin_spacing = 0;
	} else {
		pre_chinese->add_pre_chinese_non_spaced(x);
	}
}
void Text::add_post_chinese_non_spaced(Text *x) {
	
	if (post_chinese == NULL) {
		post_chinese = x;
		post_pinyin_spacing = 0;
	} else {
		post_chinese->add_post_chinese_non_spaced(x);
	}
}
void Text::add_pre_english(Text *x) {
	if (pre_english == NULL) {
		pre_english = x;
	} else {
		pre_english->add_pre_english(x);
	}
}
void Text::add_pre_chinese(Text *x) {

	if (pre_chinese == NULL) {
		pre_chinese = x;
	} else {
		pre_chinese->add_pre_chinese(x);
	}
}
void Text::add_post_chinese(Text *x) {
	
	if (post_chinese == NULL) {
		post_chinese = x;
	} else {
		post_chinese->add_post_chinese(x);
	}
}
void Text::add_post_english(Text *x) {
	if (post_english == NULL) {
		post_english = x;
	} else {
		post_english->add_post_english(x);
	}
}
void Text::add_pre_english(std::string str) {
	if (pre_english == NULL) {
		pre_english = new Unit(this);
		pre_english->english = str;
	}
	else {
		pre_english->add_pre_english(str);
	}
};
void Text::add_post_english(std::string str) {
	if (post_english == NULL) {
		post_english = new Unit(this);
		post_english->english = str;
	}
	else {
		post_english->add_post_english(str);
	}
};


void Text::make_only(int a, int b, int c) {
  for (int i = 0, z = 0; i < elements->at(a)->at(b)->size(); i++, z++) {
    if (z != c) {
      delete elements->at(a)->at(b)->at(i);
      elements->at(a)->at(b)->erase(elements->at(a)->at(b)->begin()+i);
      i--; 
    }
  }
  return;
}
void Text::make_only(int a, int b, std::string category) {
  if (is_category_non_recursive(category, a, b) != 1) { return; }

  // Erase Non Supplied Texts
  for (int i = 0; i < elements->at(a)->at(b)->size(); i++) {
    if (elements->at(a)->at(b)->at(i)->is_category_non_recursive(category) != 1) {
      delete elements->at(a)->at(b)->at(i);
      elements->at(a)->at(b)->erase(elements->at(a)->at(b)->begin()+i);
      i--; 
    }
  }
  return;
}

void Text::make_only(int a, int b, Text *t) {
  if (elements->size()-1 < a) { return; }
  if (elements->at(a)->size()-1 < b) { return; }

  // Erase Non Supplied Texts
  for (int i = 0; i < elements->at(a)->at(b)->size(); i++) {
    if (elements->at(a)->at(b)->at(i) != t) {
      delete elements->at(a)->at(b)->at(i);
      elements->at(a)->at(b)->erase(elements->at(a)->at(b)->begin()+i);
      i--; 
    }
  }
  return;
}

void Text::run_extra_code_bulk(Text *t, std::vector<std::string> extra_code, int a, int b, int c) {
  try {
    if (elements->size() == 0) { 
      for (int y = 0; y < extra_code.size(); y++) {
        code->analyse_code(t,extra_code.at(y),a,b,c); 
      }
      return;
    }
    for (int i = 0; i < elements->size(); i++) {

      int old_size = elements->at(i)->size();
      for (int ii = 0; ii < old_size; ii++) {

	int existing_elements = elements->at(i)->at(ii)->size();
        for (int iii = 0; iii < existing_elements; iii++) {
          for (int y = 0; y < extra_code.size() && iii < existing_elements; y++) {
              elements->at(i)->at(ii)->at(iii)->run_extra_code_bulk(this, extra_code,i,ii,iii);
	      existing_elements = elements->at(i)->at(ii)->size();
            }
        }

        if (old_size > elements->at(i)->size()) {
          for (int z = old_size; z > elements->at(i)->size() && z > 0; z--) {
            ii--;
      	  } 
	  old_size = elements->at(i)->size();
        }

      }
 
    }
  } catch (...) {}
  return;
}
void Text::run_extra_code(Text *t, std::string extra_code, int a, int b, int c) {
  try {
    if (elements->size() == 0) { code->analyse_code(t,extra_code,a,b,c); return; }
    for (int i = 0; i < elements->size(); i++) {

      int old_size = elements->at(i)->size();
      for (int ii = 0; ii < old_size; ii++) {

	int existing_elements = elements->at(i)->at(ii)->size();
        for (int iii = 0; iii < existing_elements; iii++) {
          elements->at(i)->at(ii)->at(iii)->run_extra_code(this, extra_code,i,ii,iii);
	  existing_elements = elements->at(i)->at(ii)->size();
        }

        if (old_size > elements->at(i)->size()) {
          for (int z = old_size; z > elements->at(i)->size() && z > 0; z--) {
            ii--;
      	  } 
	  old_size = elements->at(i)->size();
        }

      }
 
    }
  } catch (...) {}
  return;
}
void Text::run_extra_code_non_recursive(Text *t, std::string extra_code, int a, int b, int c) {
  code->analyse_code(this,extra_code,a,b,c);
  return;
}






void Text::set_pre_english_spacing(int x) { pre_english_spacing = x; }
void Text::set_post_english_spacing(int x) { post_english_spacing = x; }
void Text::set_pre_pinyin_spacing(int x) { pre_pinyin_spacing = x; }
void Text::set_post_pinyin_spacing(int x) { post_pinyin_spacing = x; }



void Text::set_english(std::string x) { english = x; }
void Text::set_pinyin(std::string x) { pinyin = x; }
void Text::set_myclass(std::string x) { myclass = x; }
void Text::set_chinese(std::string x) { chinese = x; }
void Text::set_chinese_utf8s(std::string x) { chinese_utf8s = x; }
void Text::set_chinese_utf8c(std::string x) { chinese_utf8c = x; }


std::string Text::pluralize(std::string pl) {

	if (flag.find("PLUR") != std::string::npos) { return pl; }
	if (pl == "") { return pl; }

	if (pl.substr(pl.length()-1) == "s") { pl += "es"; return pl; }
	if (pl.substr(pl.length()-1) == "x") { pl += "es"; return pl; }
	if (pl.length() < 3) { pl += "s"; return pl; }
	if (pl.substr(pl.length()-2) == "sy") { pl = pl.substr(0, pl.length()-2) + "sies"; return pl; }
	if (pl.substr(pl.length()-2) == "fy") { pl = pl.substr(0, pl.length()-2) + "fies"; return pl; }
	if (pl.substr(pl.length()-2) == "cy") { pl = pl.substr(0, pl.length()-2) + "cies"; return pl; }
	if (pl.substr(pl.length()-2) == "gy") { pl = pl.substr(0, pl.length()-2) + "gies"; return pl; }
	if (pl.substr(pl.length()-2) == "ly") { pl = pl.substr(0, pl.length()-2) + "lies"; return pl; }
	if (pl.substr(pl.length()-2) == "my") { pl = pl.substr(0, pl.length()-2) + "mies"; return pl; }
	if (pl.substr(pl.length()-2) == "ny") { pl = pl.substr(0, pl.length()-2) + "nies"; return pl; }
	if (pl.substr(pl.length()-2) == "ry") { pl = pl.substr(0, pl.length()-2) + "ries"; return pl; }
	if (pl.substr(pl.length()-2) == "ty") { pl = pl.substr(0, pl.length()-2) + "ties"; return pl; }
	if (pl.substr(pl.length()-2) == "py") { pl = pl.substr(0, pl.length()-2) + "pies"; return pl; } 
	if (pl.substr(pl.length()-2) == "ff") { return pl; }
	if (pl.length() < 4) { pl += "s"; return pl; }
	if (pl.substr(pl.length()-3) == "ife") { pl = pl.substr(0, pl.length()-3) + "ives"; return pl; }
	if (pl.substr(pl.length()-3) == "ief") { pl = pl.substr(0, pl.length()-3) + "ieves"; return pl; }
	if (pl.substr(pl.length()-3) == "man") { pl = pl.substr(0, pl.length()-3) + "men"; return pl; }
	if (pl.substr(pl.length()-3) == "ing") { return pl; }
	if (pl.substr(pl.length()-3) == "sis") { pl = pl.substr(0, pl.length()-3) + "ses"; return pl; }


	// Really irregular words
	if (pl.length() >= 5) {if (pl.substr(pl.length()-5) == "child") { pl += "ren"; return pl; } }
	if (pl.length() >= 6) {if (pl.substr(pl.length()-6) == "person") { pl = pl.substr(0, pl.length()-6) + "people"; return pl; }}

	if (pl.length() < 5) { pl += "s"; return pl; }
	if (pl.substr(pl.length()-4) == "foot") {pl = pl.substr(0, pl.length()-4) + "feet"; return pl; }

        if (pl.find(" of ") != std::string::npos) {
		std::string initial = pl.substr(0, pl.find(" of "));
		std::string postial = pl.substr(pl.find(" of "));
		return pluralize(initial) + postial;
	}


	pl += "s";
	return pl;

}

int Text::shift_pre_chinese_to_all_category(int a, int b, std::string category, Text *toadd) {

 	if (is_category(category,a,b) == -1) { return -1; }
	for (int i = 0; i < elements->at(a)->at(b)->size(); i++) {
		if (elements->at(a)->at(b)->at(i)->myclass.find(category) != std::string::npos) {
			Text *verb_unit  = text(a,b,i);
			Text *new_unit   = new Unit(this);
			toadd->clone_values(new_unit);
			verb_unit->add_pre_chinese(new_unit);
		}
	}
	return 1;
}


int Text::shift_post_chinese_to_all_category(int a, int b, std::string category, Text *toadd) {

 	if (is_category(category,a,b) == -1) { return -1; }
	for (int i = 0; i < elements->at(a)->at(b)->size(); i++) {
		if (elements->at(a)->at(b)->at(i)->myclass.find(category) != std::string::npos) {
			Text *verb_unit  = text(a,b,i);
			Text *new_unit   = new Unit(this);
			toadd->clone_values(new_unit);
                        verb_unit->return_chinese_utf8c(); // strange bugfix, remove and the last le is repeated for shuai1huai4le5 and other compounds. Cause unknown.
			verb_unit->add_post_chinese(new_unit);
		}
	}
	return 1;
}


std::string Text::conjugate(std::string x) {
	if (memory->verb_conjugation == 0) { return x; }
	return this->conjugate(x,this->vtense);
}
std::string Text::conjugate(std::string x, int vtense2) {
	
	if (vtense2 == -1) { return x; }	
	if (vtense2 == 0) { return x; }	

        /*********************************
	# -1 - not yet set
	# 0 -- infinitive
	# 1 -- participle
	# 2 -- gerund
	# 3 -- indicative -- present
	# 4 -- indicative -- perfect
	# 5 -- indicative -- past
	# 6 -- indicative -- pluperfect
	# 7 -- indicative -- future
	# 8 -- indicative -- future perfect
	# 9 -- conditional -- present
	# 10 -- conditional -- perfect
	# 11 -- imperative
	# 12 -- conjunctive -- present
	# 13 -- conjunctive -- perfect
	# 14 -- conjunctive -- past
	# 15 -- conjunctive -- pluperfect
	# 16 -- past participle
	# 17 -- future tense         	
	*********************************/

	std::string pre_verb = "";
	std::string our_verb = "";
	std::string pst_verb = "";


	/* Identify Segment to Conjugate */

	if (x.find("to ") == std::string::npos) { return x; }
	int t1 = x.find("to ");
   	if (t1 > 0) { pre_verb = x.substr(0, t1); our_verb = x.substr(t1+3); }
	if (t1 == 0) { 
		pre_verb = ""; our_verb = ""; 
		if (x.length() > 3) { 
			our_verb = x.substr(t1+3); 
		} 
	}
	if (our_verb.find(" ") != std::string::npos) {
		t1 = our_verb.find(" ");
		if (our_verb.length() > t1+1) {
			pst_verb = our_verb.substr(t1+1);
			our_verb = our_verb.substr(0, t1);
		} else {
			pst_verb = "";
		}
	}






	// Create the Appropriate String -- hack since conj is an int
	std::string conjugation = "_03";
	if (conj == 1) { conjugation = "_01"; }
	if (conj == 2) { conjugation = "_02"; }
	if (conj == 3) { conjugation = "_03"; }
	if (conj == 4) { conjugation = "_04"; }
	if (conj == 5) { conjugation = "_05"; }
	if (conj == 6) { conjugation = "_06"; }


	/*****************************************8
	Database Calls for Irregular Verb Forms  not yet implemented

	// Return Quietly if No Verb Connection has Been Made
	// if (sentence->text->adso->connected_to_verb_db == 0) { return; }


	// Irregular verbs require database access
	if 	(vtense2 == 0) 	{ 
		sentence->text->adso->query_verb("SELECT _00 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); 
	}
	if 	(vtense2 == 1) 	{ sentence->text->adso->query_verb("SELECT _01 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 2) 	{ sentence->text->adso->query_verb("SELECT _02 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 3) 	{ sentence->text->adso->query_verb("SELECT _03" + conjugation + " FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 4) 	{ sentence->text->adso->query_verb("SELECT _04" + conjugation + " FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 5) 	{ sentence->text->adso->query_verb("SELECT _05" + conjugation + " FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 6) 	{ sentence->text->adso->query_verb("SELECT _06 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 7) 	{ sentence->text->adso->query_verb("SELECT _07 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 8) 	{ sentence->text->adso->query_verb("SELECT _08 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 9) 	{ sentence->text->adso->query_verb("SELECT _09 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 10) 	{ sentence->text->adso->query_verb("SELECT _10 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 11) 	{ sentence->text->adso->query_verb("SELECT _11 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 12) 	{ sentence->text->adso->query_verb("SELECT _12 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 13) 	{ sentence->text->adso->query_verb("SELECT _13 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 14) 	{ sentence->text->adso->query_verb("SELECT _14 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 15) 	{ sentence->text->adso->query_verb("SELECT _15 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }
	if 	(vtense2 == 16) 	{ sentence->text->adso->query_verb("SELECT _16 FROM vindex WHERE _00 LIKE BINARY \'to " + verb2trans + "\'"); }


	if (sentence->text->adso->query_results->size() > 0) { 
		verb_trans = sentence->text->adso->query_results->at(0); 
		our_verb = verb_trans;
		return;
	}
	*********************************************************************/




	// Otherwise Guess (not in database)
	std::string verb2trans = our_verb;
	std::string verb_trans = our_verb;


	if (vtense2 == 0) { }
	if (vtense2 == 1) { vtense = 5; }  // testing this...
	if (vtense2 == 2) {
		if (verb2trans[verb2trans.length()-1] == 's') {
			verb_trans = verb2trans.substr(0, verb2trans.length()-1) + "ing";		
		} else {
			if (verb2trans[verb2trans.length()-1] == 'e') {
				if (verb2trans[verb2trans.length()-2] == 'e') {
					verb_trans += "ing"; 
				} else {
					verb_trans = verb2trans.substr(0, verb2trans.length()-1) + "ing"; 
				}
			} else {
				verb_trans = verb2trans + "ing";
			}
		}
		our_verb = verb_trans;
	}
	if (vtense2 == 3) { 
		if (verb2trans[verb2trans.length()-1] == 'e') {
			if (conj != 3) { verb_trans = verb2trans; }
			else { verb_trans = verb2trans + "s"; }
			our_verb = verb_trans;
		}
		if (verb2trans[verb2trans.length()-1] == 'y') {
			if (conj != 3) { verb_trans = verb2trans; }
			else { 
				if (verb2trans.length()-2 > 0) {
					if (
						verb2trans[verb2trans.length()-2] == 'a' ||
						verb2trans[verb2trans.length()-2] == 'e' ||
						verb2trans[verb2trans.length()-2] == 'i' ||
						verb2trans[verb2trans.length()-2] == 'o' ||
						verb2trans[verb2trans.length()-2] == 'u'
					) {
						verb_trans = verb2trans.substr(0, verb2trans.length()-1) + "yes"; 
					} else {
						verb_trans = verb2trans.substr(0, verb2trans.length()-1) + "ies"; 
					}
				} else {
				verb_trans = verb2trans.substr(0, verb2trans.length()-1) + "ies"; 
				}
			}
			our_verb = verb_trans;
		} 
		if (verb2trans[verb2trans.length()-1] == 's') {
			if (conj != 3) { verb_trans = verb2trans; }
			else { verb_trans = verb2trans + "es"; }
			our_verb = verb_trans;
		} else {
			if (conj != 3) { verb_trans = verb2trans; }
			else { 
				verb_trans = verb2trans + "s"; 
			}
			our_verb = verb_trans;
		}
	}
	if (vtense2 == 4) {
		if (verb2trans[verb2trans.length()-1] != 'e') {
			verb_trans = verb2trans + "e";
		}
		verb_trans += "d";
		our_verb = verb_trans;
	}
	if (vtense2 == 7) {
		our_verb = "will " + verb_trans;
	}
	if (vtense2 == 11) { our_verb = verb_trans;  }
	if (vtense2 == 12) { our_verb = verb_trans;  }
	if (vtense2 == 5 || vtense2 == 16) { 
		if (verb2trans[verb2trans.length()-1] == 'w') {
			verb_trans = verb2trans + "n";
			our_verb = verb_trans; 
		} else {
			if (verb2trans[verb2trans.length()-1] == 'e') {
				verb_trans = verb2trans + "d";
				our_verb = verb_trans; 
			} else {
				if (verb2trans[verb2trans.length()-1] == 'l') {
					verb_trans = verb2trans + "ed";
					our_verb = verb_trans; 
				} else {
					if (verb2trans[verb2trans.length()-1] == 'y') {
						verb_trans = verb2trans + "ed";
						our_verb = verb_trans; 
					} else {
						if (verb2trans[verb2trans.length()-1] == 'y') {
							verb_trans = verb2trans.substr(0, verb2trans.length()-1) + "ied";
							our_verb = verb_trans; 
						} else {
							verb_trans = verb2trans + "ed";
							our_verb = verb_trans;
						}
					}
				}
			}
		}
	}
	


	if (pre_verb != "") { our_verb = pre_verb + " " + our_verb; }
	if (pst_verb != "") { our_verb = our_verb + " " + pst_verb; }
	return our_verb;

}

std::string Text::stripped_of_tones(std::string temp) {

	while (temp.find("1") != std::string::npos) { temp = temp.substr(0, temp.find("1")) + temp.substr(temp.find("1")+1); }
	while (temp.find("2") != std::string::npos) { temp = temp.substr(0, temp.find("2")) + temp.substr(temp.find("2")+1); }
	while (temp.find("3") != std::string::npos) { temp = temp.substr(0, temp.find("3")) + temp.substr(temp.find("3")+1); }
	while (temp.find("4") != std::string::npos) { temp = temp.substr(0, temp.find("4")) + temp.substr(temp.find("4")+1); }
	while (temp.find("5") != std::string::npos) { temp = temp.substr(0, temp.find("5")) + temp.substr(temp.find("5")+1); }

	return temp;

}

int Text::map_ontology_to_class(Text *t, Ontology *ontology) {
  try {
  if (elements->size() == 0) {

    std::string temp = return_chinese();
    for (int i = 0; i < ontology->ontology_names->size(); i++) {
      for (int j = 0; j < ontology->ontology_contents->at(i)->size(); j++) {
        if (temp == ontology->ontology_contents->at(i)->at(j)) { myclass+= ":Ontology_" + ontology->ontology_names->at(i); }
      }
    }

  }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    for (unsigned int ii = 0; ii < elements->at(0)->at(i)->size(); ii++) {
      elements->at(0)->at(i)->at(ii)->map_ontology_to_class(this, ontology);
    }
  }
  } catch (...) { return -1; } 
  return 1;
}


void Text::frequency_reset(Text *t, Adso *original_adso) {
  std::string dbquery = "";
  try {
    dbquery = "UPDATE expanded_unified SET FREQ=0,FREQ2=0";
    original_adso->command_string(dbquery);
    std::cout << dbquery << std::endl;
    for (int i = 0; i < 7000; i++) {
      std::stringstream myStream1;
      myStream1 << i;
      dbquery = "UPDATE _" + myStream1.str() + " SET FREQ=0,FREQ2=0";
      try {
      original_adso->command_string(dbquery);
      } catch (...) {}
      std::cout << dbquery << std::endl;
    }
  } catch (...) { return; }
  return;
}


void Text::frequency_count(Text *t, Adso *original_adso) {
  std::string dbquery = "";
  try {
  if (elements->size() == 0) { return; }
  for (unsigned int i = 0; i < elements->at(0)->size(); i++) {
    dbquery = "UPDATE expanded_unified SET FREQ=FREQ+1 WHERE CHINESE LIKE BINARY \"" + elements->at(0)->at(i)->at(0)->chinese + "\"";
    original_adso->command_string(dbquery);
    std::cout << dbquery << std::endl;
    dbquery = "UPDATE _" + table + " SET FREQ=FREQ+1 WHERE CHINESE LIKE BINARY \"" + elements->at(0)->at(i)->at(0)->chinese + "\"";
    original_adso->command_string(dbquery);
    std::cout << dbquery << std::endl;
  }
  } catch (...) { return; }
  return;
}



std::string Text::escape_apostrophes(std::string fullt) {

        unsigned int x = fullt.find("'");
        while (x != std::string::npos) {
                fullt.replace(x, 1, "`");
                x = fullt.find("'", x+2);
        }

	/* UTF8 Apostrophe */
        x = fullt.find("’");
        while (x != std::string::npos) {
                fullt.replace(x, 3, "`");
                x = fullt.find("’",x+2);
        }

        return fullt;

}
std::string Text::apostrophes_to_html(std::string fullt) {

        unsigned int x = fullt.find("'");
        while (x != std::string::npos) {
                fullt.replace(x, 1, "&apos;");
                x = fullt.find("'", x+2);
        }
        return fullt;

}





