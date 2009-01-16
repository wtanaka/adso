#include "encoding.h"
#include <string.h>
#include <iostream>
#include "adso.h"
#include "text.h"


using namespace std;

Encoding::Encoding() {

	input_encoding = 0;
	output_encoding = 0;
	input_script = 0;
	output_script = 0;

	internal_encoding = 1;
	internal_script = 1;

};
Encoding::~Encoding() {}

std::string Encoding::report_encoding() {
  if (input_encoding == 0) { return "unknown"; }
  if (input_encoding == 1) { return "gb2312"; }
  if (input_encoding == 2) { return "utf8"; }
  return "unknown";
}
std::string Encoding::report_script() {
  if (input_script == 0) { return "unknown"; }
  if (input_script == 1) { return "simplified"; }
  if (input_script == 2) { return "traditional"; }
  return "unknown";
}
int Encoding::analyse_encoding(Text *text) {

	std::string t = text->fulltext;

	if (t == "") { throw "No text supplied for encoding analysis."; }

	int test_gb2312 = 0;
	int test_utf8s = 0;
	int test_utf8c = 0;

	if (t.find("çš„") != std::string::npos) { test_utf8s++; }
	if (t.find("æ˜¯") != std::string::npos) { test_utf8s++; }
	if (t.find("åœ°") != std::string::npos) { test_utf8s++; }
	if (t.find("å¾—") != std::string::npos) { test_utf8s++; }
	if (t.find("äº†") != std::string::npos) { test_utf8s++; }
	if (t.find("è¿‡") != std::string::npos) { test_utf8s++; }

	// Common GB2312 Characters
	if (t.find("µÄ") != std::string::npos) { test_gb2312++; }
	if (t.find("ÊÇ") != std::string::npos) { test_gb2312++; }
	if (t.find("Ëµ") != std::string::npos) { test_gb2312++; }
	if (t.find("µØ") != std::string::npos) { test_gb2312++; }
	if (t.find("µÃ") != std::string::npos) { test_gb2312++; }
	if (t.find("ÁË") != std::string::npos) { test_gb2312++; }
	if (t.find("¹ý") != std::string::npos) { test_gb2312++; }
	if (t.find("À´") != std::string::npos) { test_gb2312++; }
	if (t.find("È¥") != std::string::npos) { test_gb2312++; }

	if (test_gb2312 > test_utf8s) { input_encoding = 1; input_script = 1; output_encoding = 1; output_script = 1; return 1; }

        if (test_gb2312 == 0 && test_utf8s == 0) {
	  if (t.find("gb2312") != std::string::npos) { return 1; }    
	  if (t.find("GB2312") != std::string::npos) { return 1; }    
	  if (t.find("GB18030") != std::string::npos) { return 1; }    
	  if (t.find("utf8") != std::string::npos) { test_utf8s++; }    
	  if (t.find("utf-8") != std::string::npos) { test_utf8s++; }    
	  if (t.find("UTF8") != std::string::npos) { test_utf8s++; }    
	  if (t.find("UTF-8") != std::string::npos) { test_utf8s++; }    
        } 


	/* We determine the encoding of a text by creating three 
	 * new Text units, for which we explicitly specify 
	 * the encoding and script. We force our engine to parse
	 * a representative sample of our input text, and see which 
	 * of the Text units has the most likely correct results of 
	 * parsing. In the absense of any better evidence, we assume 
	 * that we're processing GB2312.
	 */
	Encoding *gb2312 = new Encoding();
	gb2312->input_encoding = 1;
	gb2312->input_script = 1;

	Encoding *utf8s = new Encoding();
	utf8s->input_encoding = 2;
	utf8s->input_script = 1;

	Encoding *utf8c = new Encoding();
	utf8c->input_encoding = 2;
	utf8c->input_script = 2;

	Text *text_gb2312 = new Text(text->adso, text->code, gb2312, text->feedback, text->memory, text->ontology, text->parser, text->polisher);
	Text *text_utf8s = new Text(text->adso, text->code, utf8s, text->feedback, text->memory, text->ontology, text->parser, text->polisher);
	Text *text_utf8c = new Text(text->adso, text->code, utf8c, text->feedback, text->memory, text->ontology, text->parser, text->polisher);


	std::string text_to_segment = t;
	if (text_to_segment.length() > 100) { 
		text_to_segment = text_to_segment.substr(0, 100); 
	}

	text_gb2312->init_text(text_to_segment);
	text_utf8s->init_text(text_to_segment);
	text_utf8c->init_text(text_to_segment);

	int alength = 0;
	int blength = 0;
	int clength = 0;

        if (text_gb2312->elements->size() > 0) { alength = text_gb2312->elements->at(0)->size(); };
        if (text_utf8s->elements->size() > 0) { blength = text_utf8s->elements->at(0)->size(); };
        if (text_utf8c->elements->size() > 0) { clength = text_utf8c->elements->at(0)->size(); };


	// Delete our Three Texts
	delete text_gb2312;
	delete text_utf8s;
	delete text_utf8c;	

	if (alength <= blength && alength <= clength) { input_encoding = 1; input_script = 1; output_encoding = 1; output_encoding = 1; }
	if (blength <= alength && blength <= clength) { input_encoding = 2; input_script = 1; output_encoding = 2; output_script = 1; }
	if (clength <= alength && clength <= blength) { input_encoding = 2; input_script = 2; output_encoding = 2; output_script = 2; }
	if (blength == clength) { input_script = 1; output_script = 1; }

	if (input_encoding == 0) { throw "Unable to guess input encoding."; }
	if (input_script == 0) { throw "Unable to guess input script."; }

	return 1;
}

int Encoding::first_character_length(std::string chinese) {
  if (input_encoding == 1) { return gb2312_character_length(chinese); }
  if (input_encoding == 2) { return utf8_character_length(chinese); }
  return 0;
}
int Encoding::gb2312_character_length(std::string chinese) {
	int l = chinese.length();
	if (l == 0) { return 0; }
	if (l == 1) { return 1; }
	return 2; 
}
int Encoding::character_length(std::string chinese) {
  int total_chars = 0;
  while (chinese.length() > 0 ) {

    int first_char = 0;
    if (input_encoding == 1) { first_char = gb2312_character_length(chinese); }
    if (input_encoding == 2) { first_char = utf8_character_length(chinese); }

    if (first_char > chinese.length()) { total_chars++; return total_chars; }
    else {
      chinese = chinese.substr(first_char);
      total_chars++;
    }
  }
  return total_chars;
}
int Encoding::utf8_character_length(std::string chinese) {
	int l = chinese.length();
	if (l == 0) { return 0; }
	if (l == 1) { return 1; }
	
	unsigned int charlen = 3;
	int v = chinese[0];

	if (v > 0) { 
		charlen = 1; 
	} else {
		if (v < -127) { charlen = 4; }
		if (v < -32 && charlen == 3) { charlen = 2; }
	}

	if (charlen >= chinese.length()) { return chinese.length(); }
	if (charlen <= chinese.length()) {  return charlen; }

	return charlen;

}
int Encoding::character_length(std::string chinese, std::string enco) {
	if (enco == "gb2312") { return gb2312_character_length(chinese); }
	if (enco == "utf8") { return utf8_character_length(chinese); }
	return gb2312_character_length(chinese);
}
int Encoding::word_length(std::string chinese, std::string enco) {
	int total_length = 0;
	int this_length = 0;

	while (chinese.length() > 0) {

		this_length = 0;

		if (enco == "gb2312") { this_length = gb2312_character_length(chinese); }
		if (enco == "utf8") { this_length = utf8_character_length(chinese); }

		total_length += this_length;

		if (this_length > chinese.length()) { chinese = ""; }
	 	else { chinese = chinese.substr(this_length); }

	}
	return total_length;
}


