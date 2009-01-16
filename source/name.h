#ifndef NAME_H
#define NAME_H

#include "noun.h"
#include "text.h"

class Name: public Noun {
	
	private:
		int pinyin_generated;
		int length;
		std::string name;

	public:
		Name(Text *t);
		~Name();

		virtual int pre_unify(Text *t, int a, int b, int c);
		virtual int combine(Text *t, int a, int b, int c);
		virtual int adjust_confidence(Text *t, int a, int b, int c);

		virtual std::string return_english();
		virtual std::string return_english_no_spacing();
		virtual void set_english(std::string x);
		virtual void set_pinyin(std::string x);

		virtual std::string return_pinyin();
		virtual std::string return_pinyin_no_spacing();

		std::vector<std::string> *likely;
		std::vector<std::string> *unlikely;

};




#endif

