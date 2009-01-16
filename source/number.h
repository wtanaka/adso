#ifndef NUMBER_H
#define NUMBER_H

#include "unit.h"
#include <sstream>

class Number: public Unit {

	private: 

		long unsigned int whole_number;
		float decimal_number;
		float full_number;
		int starts_with_zero;
		int plural_next;
		std::string following_pinyin;

	public:

		Number(Text *text);
		~Number();

		virtual int pre_unify(Text *parent, int a, int b, int c);
		virtual int unify(Text *parent, int a, int b, int c);
		virtual int post_unify(Text *parent, int a, int b, int c);
		virtual int adjust_confidence(Text *parent, int a, int b, int c);
		virtual int advanced(Text *parent, int a, int b, int c);



		virtual void generate_numbers();
		virtual int convert2number(std::string ch);
		virtual int is_complex_number(std::string ch);

		std::string what_is_my_pinyin(int x);
		std::string generate_complex_pinyin(int x);
		std::string add_commas_to_number(std::string x);

		std::string return_numeric_chinese();
		std::string suffix(std::string x);

		std::string return_pinyin();
		std::string return_pinyin_no_spacing();
	
};

#endif


