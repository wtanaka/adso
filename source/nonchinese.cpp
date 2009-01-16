#include "nonchinese.h"
#include "text.h"
#include "punctuation.h"
#include <sstream>
#include <vector>
#include "encoding.h"

NonChinese::NonChinese(Text *text): Unit(text) { myclass += ":NonChinese";};
NonChinese::~NonChinese() {}

std::string NonChinese::return_english_no_spacing() {
  return return_pinyin_no_spacing();
}
std::string NonChinese::generate_pinyin() {
  return return_chinese();
}
std::string NonChinese::return_popup() {
  return return_chinese();
}

int NonChinese::pre_unify(Text *parent, int a, int b, int c) {

	// SET ALL VARIANTS TO OUR CHINESE
	chinese_utf8s = chinese;
	chinese_utf8c = chinese;
	chinese_big5 = chinese;

	// Use of ASCII Punctuation Common in Chinese Text
	if (chinese == "\n") { myclass += ":Punctuation:Terminal:Newline"; }
	if (chinese == "?") { myclass += ":Punctuation:Terminal:Question"; }
	if (chinese == "!") { myclass += ":Punctuation:Terminal:Exclamation"; }
	if (chinese == ",") { myclass += ":Punctuation:Comma"; }
	if (chinese == ":") { myclass += ":Punctuation:Colon"; }
	if (chinese == ";") { myclass += ":Punctuation:Semi-Colon"; }
	if (chinese == ".") { myclass += ":Punctuation:Terminal:Period"; }
	if (chinese == " ") { myclass += ":Space:Punctuation"; }
	if (chinese == "\"") { myclass += ":Punctuation:DoubleQuote"; }
	if (chinese == "'") { myclass += ":Punctuation:SingleQuote"; }
	if (chinese == "(") { myclass += ":Punctuation:OpeningBracket"; }
	if (chinese == "<") { myclass += ":Punctuation:OpeningBracket"; }
	if (chinese == "{") { myclass += ":Punctuation:OpeningBracket"; }
	if (chinese == "[") { myclass += ":Punctuation:OpeningBracket"; }
	if (chinese == "(") { myclass += ":Punctuation:OpeningBracket"; }
	if (chinese == "<") { myclass += ":Punctuation:ClosingBracket"; }
	if (chinese == "{") { myclass += ":Punctuation:ClosingBracket"; }
	if (chinese == "[") { myclass += ":Punctuation:ClosingBracket"; }
	if (chinese == ")") { myclass += ":Punctuation:ClosingBracket"; }


	/* Break NonChinese Elements at Closing Tags */
	if (chinese == ">") { return 1; }



	/* Unify NonChinese Elements */
	std::string next = parent->return_chinese(a, b+1, 0);
	int stop = 0;
	


	if (split_nonchinese_on_punctuation == 1) {
		if (chinese == "\n") { return 1; }
		if (chinese[0] == '?') { return 1; }
		if (chinese[0] == '!') { return 1; }
		if (chinese[0] == '.') { return 1; }
		if (chinese[0] == ':') { return 1; }
		if (chinese[0] == ',') { return 1; }
		if (chinese[0] == ';') { return 1; }
		if (chinese[0] == '(') { return 1; }
		if (chinese[0] == ')') { return 1; }
		if (chinese[0] == '<') { return 1; }
		if (chinese[0] == '>') { return 1; }
		while (parent->is_category_non_recursive("NonChinese", a, b+1) == 1 && next != "\n") {
		  if (next == "\n") { break; }
		  if (next[0] == '?') { break; }
		  if (next[0] == '!') { break; }
		  if (next[0] == '.') { break; }
		  if (next[0] == ',') { break; }
		  if (next[0] == ':') { break; }
		  if (next[0] == ';') { break; }
		  if (next[0] == '(') { break; }
		  if (next[0] == ')') { break; }
		  if (next[0] == '<') { break; }
		  if (next[0] == '<') { break; }
		  if (next[0] == '>') {
		    if (chinese[0] == '<') { myclass = "Unit:Punctuation:XML"; }
		    shift_post_chinese(parent, a, b+1, "NonChinese", this);
	            /* this is the end of XML -- do not further unify across numbers/nonchihnese elements */
		    stop = 1;
		    break;
		  }
		  shift_post_chinese(parent, a, b+1, "NonChinese", this);
		  next = parent->return_chinese(a, b+1, 0);
		}
	} else {
		while (parent->is_category_non_recursive("NonChinese", a, b+1) == 1 && next != "\n") {
		  if (next[0] == '<') { break; }
		  if (next[0] == '>') {
		    if (chinese[0] == '<') { myclass = "Unit:Punctuation:XML"; }
		    shift_post_chinese(parent, a, b+1, "NonChinese", this);
	            /* this is the end of XML -- do not further unify across numbers/nonchihnese elements */
		    stop = 1;
		    break;
		  }
		  shift_post_chinese(parent, a, b+1, "NonChinese", this);
		  next = parent->return_chinese(a, b+1, 0);
		}
	}



	/* Unify Numbers if HTML Processing to keep URLS and Other Items Consistent */
/*
	while ((parent->is_category_non_recursive("Number", a, b+1) == 1 || parent->is_category_non_recursive("NonChinese", a, b+1) == 1) && next != "\n" && stop != 1) {

		next = parent->return_chinese(a, b+1, 0);

		if (next[0] == '>') { break; }
		if (next[0] == '<') { break; }
		if (next[0] == ' ') { break; }

		while (parent->is_category_non_recursive("Number", a, b+1) == 1 && next != "\n") {
		  if (next[0] == '<') { break; }
		  if (next[0] == '>') {
		    if (chinese[0] == '<') { myclass = "Unit:Punctuation:XML"; }
		    shift_post_chinese(parent, a, b+1, "Number", this);
		    stop = 1;
		    break;
		  }
		  shift_post_chinese(parent, a, b+1, "Number", this);
		  next = parent->return_chinese(a, b+1, 0);
		  myclass += ":Number";
		}


		next = parent->return_chinese(a, b+1, 0);
		while (parent->is_category_non_recursive("NonChinese", a, b+1) == 1 && next != "\n") {
		  if (next[0] == '<') { break; }
		  if (next[0] == '>') {
		    if (chinese[0] == '<') { myclass = "Unit:Punctuation:XML"; }
		    shift_post_chinese(parent, a, b+1, "NonChinese", this);
		    stop = 1;
		    break;
		  }
		  shift_post_chinese(parent, a, b+1, "NonChinese", this);
		  next = parent->return_chinese(a, b+1, 0);
		}
	}
*/

	/* XML Analysis */
	if (chinese[0] == '<') {
		std::string myxml = return_chinese();

		/* Opening Closing */
		if (myxml.find("/>") != std::string::npos) { myclass += ":ClosingXML"; }
		if (myxml.find("</") != std::string::npos) { myclass += ":ClosingXML"; }
		if (myxml[myxml.length()-1] == '>') { if (myclass.find("ClosingXML") == std::string::npos) { myclass += ":OpeningXML"; }}
	}






	return 1;
}


std::string NonChinese::return_english() { return return_chinese(); }
std::string NonChinese::return_pinyin() { return return_chinese(); }
std::string NonChinese::return_jyutpin() { return return_chinese(); }
int NonChinese::identify_html_entities(Text *parent, int a, int b, int c) {


	if (chinese == "<") { 

		std::string temp = return_chinese();
		std::vector<std::string> *y = new std::vector<std::string>;

		// Strip the Opening and Closing Tag
		temp = temp.substr(1);
		if (temp[temp.length()-1] == '>') { temp = temp.substr(0,temp.length()-1); }

		tokenize(temp,y);

		if (y->size() > 0) {
			std::string x = y->at(a);
			for (int i = 0; i < x.length(); i++) { x[i] = toupper(x[i]); }


			if (x == "IMG") { myclass+=":HTML_IMG"; }
			process_html_tag(parent,y,"SCRIPT",x,a,b);
			process_html_tag(parent,y,"A",x,a,b);
			process_html_tag(parent,y,"P",x,a,b);
			process_html_tag(parent,y,"BR",x,a,b);
			process_html_tag(parent,y,"B",x,a,b);
			process_html_tag(parent,y,"STRING",x,a,b);
			process_html_tag(parent,y,"EM",x,a,b);
			process_html_tag(parent,y,"I",x,a,b);
			process_html_tag(parent,y,"H1",x,a,b);
			process_html_tag(parent,y,"H2",x,a,b);
			process_html_tag(parent,y,"H3",x,a,b);
			process_html_tag(parent,y,"H4",x,a,b);
			process_html_tag(parent,y,"H5",x,a,b);
			process_html_tag(parent,y,"H6",x,a,b);
			process_html_tag(parent,y,"DIV",x,a,b);
			process_html_tag(parent,y,"SPAN",x,a,b);
		}


		y->clear();
		delete y;
	}



  	return 1;
}





void NonChinese::process_html_tag(Text *t, std::vector<std::string> *y, std::string tag_look_for, std::string tag_given, int a, int b) {
	if (tag_given == tag_look_for) { 
		myclass += ":OpeningHTML_" + tag_look_for;
		catch_class_and_id_tags(t, y, a, b);
	}
	if (tag_given == ("/"+tag_look_for)) { 
		std::string opening_tag = "OpeningHTML_" + tag_look_for;
		std::string closed_opening_tag = "ClosedOpeningHTML_" + tag_look_for;
		std::string closing_tag = "ClosingHTML_" + tag_look_for;
		std::string range_tag = "HTML_" + tag_look_for;
		int opening_tag_location = t->sentence_backward_html_match_complex(opening_tag,closed_opening_tag,a,b);

		if (opening_tag_location > -1) {

			std::string class_for_tagging = "";
			std::string id_for_tagging = "";
			if (t->likely(a,opening_tag_location)->html_class != "") {
				class_for_tagging = "HTML_CLASS_" + t->likely(a,opening_tag_location)->html_class;
			}
			if (t->likely(a,opening_tag_location)->html_id != "") {
				id_for_tagging = "HTML_ID_" + t->likely(a,opening_tag_location)->html_id;
			}
			if (t->likely(a,opening_tag_location)->html_src != "") {
				id_for_tagging = "HTML_SRC(" + t->likely(a,opening_tag_location)->html_src+")";
			}
			if (t->likely(a,opening_tag_location)->html_href != "") {
				id_for_tagging = "HTML_HREF(" + t->likely(a,opening_tag_location)->html_href+")";
			}


			for (int z= opening_tag_location; z<=b;z++) { 
				if (z == opening_tag_location) {
					t->tag(closed_opening_tag,a,z); 
					if (class_for_tagging != "") { t->tag(class_for_tagging,a,z); } 
					if (id_for_tagging != "") { t->tag(id_for_tagging,a,z); }
				} else {
					if (z != b) {
						t->tag(range_tag,a,z); 
						if (class_for_tagging != "") { t->tag(class_for_tagging,a,z); } 
						if (id_for_tagging != "") { t->tag(id_for_tagging,a,z); }
					} else {
						t->tag(closing_tag,a,z); 
						if (class_for_tagging != "") { t->tag(class_for_tagging,a,z); } 
						if (id_for_tagging != "") { t->tag(id_for_tagging,a,z); }
					}
				}
			}
		}
		
	}
	return;
}
void NonChinese::catch_class_and_id_tags(Text *t, std::vector<std::string> *y, int a, int b) {

	for (int c = 1; c < y->size() && html_class == ""; c++) {
		html_class = process_class(t, y->at(c), a, b);
	}
	for (int c = 1; c < y->size() && html_id == ""; c++) {
		html_id = process_id(t, y->at(c), a, b);
	}
	for (int c = 1; c < y->size() && html_href == ""; c++) {
		html_href = process_href(t, y->at(c), a, b);
	}
	for (int c = 1; c < y->size() && html_src == ""; c++) {
		html_src = process_src(t, y->at(c), a, b);
	}

	return;
}
std::string NonChinese::process_class(Text *t, std::string temp, int a, int b) {

	// Strip the Opening and Closing Tag
	if (temp.length() >= 6) { 

		std::string temp2 = temp.substr(0,6);
		for (int i = 0; i < temp2.length(); i++) { temp2[i] = toupper(temp2[i]); }
		if (temp2 == "CLASS=") {
			if (temp.length() >= 7) {
				std::string match = temp.substr(6);			

				if (match.length() >= 1) { if (match[0] == '"') { match = match.substr(1); } }
				if (match.length() >= 1) { if (match[match.length()-1] == '"') { match = match.substr(0, match.length()-1); } }
				return match;
			}
		}
	}

	return "";
}
std::string NonChinese::process_id(Text *t, std::string temp, int a, int b) {

	// Strip the Opening and Closing Tag
	if (temp.length() >= 3) { 

		std::string temp2 = temp.substr(0,3);
		for (int i = 0; i < temp2.length(); i++) { temp2[i] = toupper(temp2[i]); }
		if (temp2 == "ID=") {
			if (temp.length() >= 4) {
				std::string match = temp.substr(3);			
				if (match.length() >= 1) { if (match[0] == '"') { match = match.substr(1); } }
				if (match.length() >= 1) { if (match[match.length()-1] == '"') { match = match.substr(0, match.length()-1); } }
				return match;
			}
		}
	}
	return "";
}
std::string NonChinese::process_href(Text *t, std::string temp, int a, int b) {

	// Strip the Opening and Closing Tag
	if (temp.length() >= 5) { 
		std::string temp2 = temp.substr(0,5);
		for (int i = 0; i < temp2.length(); i++) { temp2[i] = toupper(temp2[i]); }
		if (temp2 == "HREF=") {
			if (temp.length() >= 6) {
				std::string match = temp.substr(5);			
				if (match.length() >= 1) { if (match[0] == '"') { match = match.substr(1); } }
				if (match.length() >= 1) { if (match[match.length()-1] == '"') { match = match.substr(0, match.length()-1); } }
				return match;
			}
		}

	}
	return "";
}
std::string NonChinese::process_src(Text *t, std::string temp, int a, int b) {

	// Strip the Opening and Closing Tag
	if (temp.length() >= 3) { 

		std::string temp2 = temp.substr(0,4);
		for (int i = 0; i < temp2.length(); i++) { temp2[i] = toupper(temp2[i]); }
		if (temp2 == "SRC=") {
			if (temp.length() >= 5) {
				std::string match = temp.substr(4);			
				if (match.length() >= 1) { if (match[0] == '"') { match = match.substr(1); } }
				if (match.length() >= 1) { if (match[match.length()-1] == '"') { match = match.substr(0, match.length()-1); } }
				return match;
			}
		}

	}
	return "";
}


void NonChinese::tokenize(std::string x, std::vector<std::string> *y) {
  std::stringstream ss;
  std::string buf;
  ss << x;
  y->clear();
  while (ss>>buf) {y->push_back(buf);}
  return;
}



