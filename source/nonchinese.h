#ifndef NONCHINESE_H
#define NONCHINESE_H

#include "unit.h"

class NonChinese: public Unit {

	public:
		NonChinese(Text *text);
		~NonChinese();

		virtual int pre_unify(Text *parent, int a, int b, int c);
		virtual int identify_html_entities(Text *parent, int a, int b, int c);

		void tokenize(std::string x, std::vector<std::string> *y);

		virtual std::string generate_pinyin();
		virtual std::string return_english_no_spacing();
		virtual std::string return_english();
		virtual std::string return_popup();
		virtual std::string return_pinyin();
		virtual std::string return_jyutpin();


		std::string process_class(Text *t, std::string c, int a, int b);
		std::string process_id(Text *t, std::string c, int a, int b);
		std::string process_src(Text *t, std::string c, int a, int b);
		std::string process_href(Text *t, std::string c, int a, int b);


		void catch_class_and_id_tags(Text *t, std::vector<std::string> *y, int a, int b);
		void process_html_tag(Text *t, std::vector<std::string> *y, std::string g, std::string h, int a, int b);
};





#endif

