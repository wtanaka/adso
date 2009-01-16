#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iterator>
#include <vector>


#include "database/compiled_database.h"

class Text;

class Parser {

	public:

		std::vector<std::string> *results;

		Compiled_Database *compiled_database;

		Parser();
		~Parser();

		void parse(Text *text);
		void parse_textbook_markup(Text *text);
		void parse_against_compiled_database(Text *text);
		void longest_word_match(Text *t);
		void populate_text_elements(std::string word, Text *text, std::string current_table, std::string search_field);
		void add_option(Text *maintext, Text *subtext, std::string chinese, std::string english, std::string pinyin, std::string flag, std::string code, std::string table_pkey, std::string chinese_utf8s, std::string chinese_utf8c, std::string chinese_big5, std::string newstrack, int new_item, int freq1, float freq2,std::string table);
		void add_option_from_compiled_database(Text *maintext, std::string chinese, std::string english, std::string pinyin, std::string flag, std::string code, std::string table_pkey, std::string chinese_utf8s, std::string chinese_utf8c, std::string chinese_big5, std::string newstrack, int new_item, int freq1, float freq2,std::string table);

};



#endif
