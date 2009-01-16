#include "punctuation.h"
#include "unit.h"
#include "text.h"
#include <iostream>

Punctuation::Punctuation(Text *t): Unit(t) { 
	myclass += ":Punctuation"; 
}
Punctuation::~Punctuation() {}



std::string Punctuation::return_chinese() {
  if (asciify_punctuation == 1) {
	return english;
    return "x";
  }
  return Text::return_chinese();
}
std::string Punctuation::return_chinese_utf8s() {
  if (asciify_punctuation == 1) {
    return english;
  }
  return Text::return_chinese_utf8s();
}
std::string Punctuation::return_chinese_utf8c() {
  if (asciify_punctuation == 1) {
    return english;
  }
  return Text::return_chinese_utf8c();
}

std::string Punctuation::return_popup() {
  return return_chinese_utf8s();
}

int Punctuation::pre_unify(Text *t, int a, int b, int c) {

	confidence++; 

	// Additional Information
  	if (chinese == " ") {	myclass += ":Space:Terminal"; english = " ";};
  	if (chinese == "¡£") {	myclass += ":Terminal:Period"; english = ". "; };
	if (chinese == "£®") {	myclass += ":Terminal:Period"; english = ". "; };
  	if (chinese == "£¿") {	myclass += ":Terminal:Question"; english = "? ";};
  	if (chinese == "£¡") {	myclass += ":Terminal:Exclamation"; english = "! "; };
  	if (chinese == "¡¤") {	myclass += ":Dot"; english = "-"; };
  	if (chinese == "£¬") {	myclass += ":Comma"; english = ", "; };
	if (chinese == "£º") {	myclass += ":Colon"; english = ": "; };
	if (chinese == "¡¢") {  myclass += ":Comma"; english = ", "; };
	if (chinese == "£­") {  myclass += ":Dash"; english = "-"; };

  	if (chinese == "£¨") {	myclass += ":OpeningBracket"; english = "("; };
  	if (chinese == "£©") {	myclass += ":ClosingBracket"; english = ")"; };
  	if (chinese == "¡·") {	myclass += ":ClosingBracket:ClosingBookBracket"; english = "]"; }
  	if (chinese == "¡¶") {	myclass += ":OpeningBracket:OpeningBookBracket"; english = "["; }
	if (chinese == "¡¾") {	myclass += ":OpeningBracket"; english = "["; }
	if (chinese == "¡¿") {	myclass += ":ClosingBracket"; english = "]"; };
  	if (chinese == "¡°") {	myclass += ":OpeningQuote"; english = "\""; };
  	if (chinese == "¡±") {	myclass += ":ClosingQuote"; english = "\""; };

	return 1;
};

std::string Punctuation::return_english() { if (english != "") { return Text::return_english(); } return return_chinese(); }
std::string Punctuation::return_pinyin() { if (english != "") { return return_english(); } return return_chinese(); }
std::string Punctuation::return_jyutpin() { return return_chinese(); }

int Punctuation::adjust_spacing(Text *parent, int main_vector, int element_vector, int option) {

  if (myclass.find("OpeningBracket") != std::string::npos) { 
    post_english_spacing = 0;
    post_pinyin_spacing = 0;
  }
  if (myclass.find("OpeningBookBracket") != std::string::npos) { 
    post_english_spacing = 0;
    post_pinyin_spacing = 0;
  }
  if (myclass.find("OpeningQuote") != std::string::npos) { 
    post_english_spacing = 0;
    post_pinyin_spacing = 0;
  }

  if (myclass.find("ClosingQuote") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }
  if (myclass.find("ClosingBracket") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }
  if (myclass.find("ClosingBookBracket") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }
  if (myclass.find("Terminal") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }
  if (myclass.find("Comma") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }
  if (myclass.find("Colon") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }
  if (myclass.find("Dot") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }
  if (myclass.find("Dash") != std::string::npos) { 
    if (element_vector > 0) {
      for (int i = 0; i < parent->elements->at(main_vector)->at(element_vector-1)->size(); i++) {
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_english_spacing = 0;
        parent->elements->at(main_vector)->at(element_vector-1)->at(i)->post_pinyin_spacing = 0;
      }
    }
  }

  return 1;
}
