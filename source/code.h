#ifndef CODE_H
#define CODE_H

#include <vector>
#include <string>

class Text;

class Code {

	private:
		std::vector<std::string> *tokens;
		std::vector<std::string> *compounds;
		std::vector<std::string> *compound_xml;
		std::vector<std::string> *compound_xml_action;
		void set_helper(Text *x, int a, int b, int c, std::string field, std::string value);
		std::string itoa(int x);

	public:
		Code();
		~Code();

		int analyse_code(Text *x, std::string c, int x, int y, int z);
		int process_code(Text *x, std::string c, int x, int y, int z);

		int are_parens_balanced(std::string x);
		void tokenize(std::string x);

		std::string return_closing_boolean(std::string x);
		std::string return_opening_boolean(std::string x);


		/* XML Functions */
		int print(Text *x, std::string c, int x, int y, int z);
		int is_class(Text *x, std::string c, int x, int y, int z);
		int is_class2(Text *x, std::string c, int x, int y, int z);
		int not_class(Text *x, std::string c, int x, int y, int z);
		int statistical_machine_translation(Text *x, std::string c, int x, int y, int z);
		int is_chinese(Text *x, std::string c, int x, int y, int z);
		int is_chinese2(Text *x, std::string c, int x, int y, int z);
		int not_chinese(Text *x, std::string c, int x, int y, int z);
		int define_compound(Text *x, std::string c, int x, int y, int z);
		int compound_execute(Text *x, std::string c, int x, int y, int z);
		int compound_chain_execute(Text *x, std::string c, int x, int y, int z);
		int compound_bonus(Text *x, std::string c, int x, int y, int z);
		int compound_bonus2(Text *x, std::string c, int x, int y, int z);
		int compound_length(Text *x, std::string c, int x, int y, int z);
		int compound_length2(Text *x, std::string c, int x, int y, int z);
		int is_compound(Text *x, std::string c, int x, int y, int z);
		int is_compound2(Text *x, std::string c, int x, int y, int z);
		int not_compound(Text *x, std::string c, int x, int y, int z);
		int tag(Text *x, std::string c, int x, int y, int z);
		int beginning(Text *x, std::string c, int x, int y, int z);
		int ending(Text *x, std::string c, int x, int y, int z);
		int subclause(Text *x, std::string c, int x, int y, int z);
		int add_post_text(Text *x, std::string c, int x, int y, int z);
		int add_pre_text(Text *x, std::string c, int x, int y, int z);

		int last(Text *x, std::string c, int x, int y, int z);
		int lastloop(Text *x, std::string c, int x, int y, int z);
		int lastword(Text *x, std::string c, int x, int y, int z);
		int lastwordexact(Text *x, std::string c, int x, int y, int z);
		int lastwordloop(Text *x, std::string c, int x, int y, int z);
		int next(Text *x, std::string c, int x, int y, int z);
		int nextloop(Text *x, std::string c, int x, int y, int z);
		int nextword(Text *x, std::string c, int x, int y, int z);
		int nextwordexact(Text *x, std::string c, int x, int y, int z);
		int nextwordloop(Text *x, std::string c, int x, int y, int z);
		int contains(Text *x, std::string c, int x, int y, int z);
		int match(Text *x, std::string c, int x, int y, int z);
		int matchexact(Text *x, std::string c, int x, int y, int z);
		int textmatch(Text *x, std::string c, int x, int y, int z);
		int bonus(Text *x, std::string c, int x, int y, int z);
		int bonus2(Text *x, std::string c, int x, int y, int z);
		int boost(Text *x, std::string c, int x, int y, int z);
		int resegment(Text *x, std::string c, int x, int y, int z);
		int delete_entry(Text *x, std::string c, int x, int y, int z);
		int make_only_entry(Text *x, std::string c, int x, int y, int z);
		int not_translate(Text *x, std::string c, int x, int y, int z);
		int possessive(Text *x, std::string c, int x, int y, int z);
		int pluralize(Text *x, std::string c, int x, int y, int z);
		int plural_next(Text *x, std::string c, int x, int y, int z);
		
		int is_number(Text *x, std::string c, int x, int y, int z);
		int length(Text *x, std::string c, int x, int y, int z);
		int tense(Text *x, std::string c, int x, int y, int z);
		int insert(Text *x, std::string c, int x, int y, int z);
		int set(Text *x, std::string c, int x, int y, int z);
		int switch_units(Text *x, std::string c, int x, int y, int z);
		int transform_01(Text *x, std::string c, int x, int y, int z);
		int reduce(Text *x, std::string c, int x, int y, int z);


		//int combine(Text *x, std::string c, int location);
		//int set_pre_translation(Text *x, std::string c, int location);
		//int set_translation(Text *x, std::string c, int location);
		//int set_post_translation(Text *x, std::string c, int location);



};

#endif


