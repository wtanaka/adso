#ifndef PUNCTUATION_H
#define PUNCTUATION_H

#include "unit.h"
#include "text.h"

class Punctuation: public Unit {

	public:
		Punctuation(Text *t);
		~Punctuation();

		std::string return_chinese();
		std::string return_chinese_utf8s();
		std::string return_chinese_utf8c();
		std::string return_pinyin();
		std::string return_english();
		std::string return_jyutpin();
		std::string return_popup();

		int pre_unify(Text *parent, int a, int b, int c);
		int adjust_spacing(Text *parent, int a, int b, int c);

};




#endif

