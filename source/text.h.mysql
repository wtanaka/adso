#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class Adso;
class Code;
class Encoding;
class Feedback;
class Memory;
class Ontology;
class Parser;
class Polisher;

class Text {


	public:

		/* avoids creating a new Text element for simple mergers */
		Text *pre_chinese;
		Text *post_chinese;
		Text *pre_english;
		Text *post_english;

		int split_nonchinese_on_punctuation;
		int asciify_punctuation;
		int should_translate;
		int integer_representation;
		int code_analysed;
		float decimal_representation;
		int frequency_int;
		float frequency_float;
	
		// Variables useful for End Elements
		std::string myclass;		// what class this is
		std::string flag;

		std::string generate_spacing;

		std::string chinese;
		std::string chinese_utf8s;
		std::string chinese_utf8c;
		std::string chinese_big5;

		std::string english;
		std::string french;
		std::string german;
		std::string japanese;
		std::string spanish;
		std::string italian;
		std::string arabic;
		std::string russian;
		std::string portuguese;
		std::string korean;
		std::string hebrew;
		std::string farsi;

		std::string pinyin;
		std::string jyutpin;

		std::string table;


		int location;			// location in supra element
		int beginning;			// beginning of sentence
		int ending;			// ending of sentence
		int capitalize;
		int full_definitions;

		int pre_english_spacing;
		int post_english_spacing;
		int pre_pinyin_spacing;
		int post_pinyin_spacing;


		// HTML Markup
		std::string html_class;
		std::string html_id;
		std::string html_href;
		std::string html_src;

		double confidence;
		double probability;

		std::vector<std::string> *field_english;
		std::vector<std::string> *field_pinyin;
		std::vector<std::string> *field_code;
		std::vector<std::string> *field_pkey;
		std::vector<std::string> *field_newstrack;
		std::vector<double>      *field_rank;

		Text* linked_unit;


	
		// Variables Useful for Certain Units
		int plural;	// plural (nouns)
		int negative;	// negative (verbs)
		int possessive;	// possessive marker (nouns)
		int vtense;	// verbs
		int conj;	// conjugation (verbs)





		// Variables Required for Top-Level Management
		Adso *adso;
		Encoding *encoding;
		Parser *parser;
		Polisher *polisher;
		Code *code;	
		Feedback *feedback;
		Memory *memory;
		Ontology *ontology;

		std::string fulltext;
		std::string fulltext_gb2312;
		std::vector<std::vector<std::vector<Text *> *> *> *elements;


		int init(Text *t);
		int init(Adso *a, Code *c, Encoding *e, Feedback *f, Memory *m, Ontology *o, Parser *pa, Polisher *po);



		Text(Adso *a, Code *c, Encoding *e, Feedback *f, Memory *m, Ontology *o, Parser *pa, Polisher *po);
		Text(Text *t);
		Text(Text *reference, Text *a, Text *b);
		virtual ~Text();

		
		int init_text(std::string t);
		int init_markup(std::string m);
		int append_text(Text *x, int a, int b);
		void clone_values(Text *x);
		void append_clone_values(Text *x);
		

		virtual std::string conjugate(std::string x);
		virtual std::string conjugate(std::string x, int conjugate_tense);
		std::string pluralize(std::string x);
		int plural_next_noun(int a, int b, int plural_value);
		int map_ontology_to_class(Text *t, Ontology *ont);

		// Functions to Identify Text Units
		int is_category(std::string category);
		int is_category(std::string category, int a);
		int is_category(std::string category, int a, int b);
		int is_category(std::string category, int a, int b, int c);
		int is_category_non_recursive(std::string category);
		int is_category_non_recursive(std::string category, int a);
		int is_category_non_recursive(std::string category, int a, int b);
		int is_category_non_recursive(std::string category, int a, int b, int c);
		int is_only_category_non_recursive(std::string category, int a, int b);
		int sentence_forward_word_match(std::string category, int a, int b);
		int sentence_forward_category_match(std::string category, int a, int b);
		int sentence_backward_word_match(std::string category, int a, int b);
		int sentence_backward_category_match(std::string category, int a, int b);
		int sentence_backward_html_match_complex(std::string is_category, std::string is_not_category, int a, int b);
		int tag(std::string tag, int a, int b);



		// Functions to Manipulate Text Units
		int shift_pre_chinese(Text *source, int source_a, int source_b, int source_c, Text *destination);
		int shift_pre_chinese(Text *source, int source_a, int source_b, std::string category, Text *destination);
		int shift_post_chinese(Text *source, int source_a, int source_b, int source_c, Text *destination);
		int shift_post_chinese(Text *source, int source_a, int source_b, std::string category, Text *destination);
		int shift_post_chinese_to_all_category(int a, int b, std::string category, Text *toshift);
		int shift_pre_chinese_to_all_category(int a, int b, std::string category, Text *toshift);

		int adjust_confidence(double x);
		int adjust_probability(double x);

		int remove_element(int a, int b);


		void set_post_english_spacing(int x);
		void set_pre_english_spacing(int x);
		void set_post_pinyin_spacing(int x);
		void set_pre_pinyin_spacing(int x);



		Text * likely(int, int);
		Text * text(int, int, int);
		Text * text(int, int, std::string);
		int likely(int location);



		/* Functions to Resegment Texts */
		virtual int resegment(int a, int b, int char_distance);
		virtual void switch_units(int a, int b1, int b2);



		/* Analytic Functions for End Units */
		virtual int pre_unify(Text *parent);
		virtual int pre_unify(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int unify(Text *parent);
		virtual int unify(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int post_unify(Text *parent);
		virtual int post_unify(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int combine(Text *parent);
		virtual int combine(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int combine2(Text *parent);
		virtual int combine2(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int adjust_confidence(Text *parent);
		virtual int adjust_confidence(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int advanced(Text *parent);
		virtual int advanced(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int grammar(Text *parent);
		virtual int grammar(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int run_code(Text *parent);
		virtual int run_code(Text *parent, int main_vector, int element_vector, int option_vector);
		virtual int adjust_spacing(Text *parent);
		virtual int adjust_spacing(Text *parent, int main_vector, int element_vector, int option_vector);

		virtual void frequency_count(Text *parent, Adso *original_adso);
		virtual void frequency_reset(Text *parent, Adso *original_adso);
		virtual int identify_html_entities(Text *parent);
		virtual int identify_html_entities(Text *parent, int main_vector, int element_vector, int option_vector);


		virtual int add_confidence(double benefit);
		virtual int add_confidence(std::string category, double benefit, int a, int b);
		virtual int add_confidence(std::string category, double benefit, int a, int b, int c);

		virtual void add_pre_chinese_non_spaced(Text *t);
		virtual void add_post_chinese_non_spaced(Text *t);
		virtual void add_pre_chinese(Text *t);
		virtual void add_post_chinese(Text *t);
		virtual void add_pre_english(Text *t);
		virtual void add_post_english(Text *t);
		virtual void add_pre_english(std::string t);
		virtual void add_post_english(std::string t);

		virtual void make_only(int a, int b, int c);
		virtual void make_only(int a, int b, Text *);
		virtual void make_only(int a, int b, std::string category);

		virtual void run_extra_code(Text *text, std::string extra_code, int a, int b, int c);
		virtual void run_extra_code_bulk(Text *text, std::vector<std::string> extra_code, int a, int b, int c);
		virtual void run_extra_code_non_recursive(Text *text, std::string extra_code, int a, int b, int c);





		virtual void set_english(std::string x);
		virtual void set_pinyin(std::string x);
		virtual void set_myclass(std::string x);
		virtual void set_chinese(std::string x);
		virtual void set_chinese_utf8s(std::string x);
		virtual void set_chinese_utf8c(std::string x);


		virtual int set_possessive(int a);
		virtual int set_plural(int a);
		virtual std::string make_possessive(std::string x);
		std::string stripped_of_tones(std::string x);



		// Output Functions
		std::string debug();
		std::string output();
		std::string translate();
		std::string popup();
		


		virtual std::string generate_chinese();
		virtual std::string generate_chinese_utf8s();
		virtual std::string generate_chinese_utf8c();
		virtual std::string generate_pinyin(std::string spacing);
		virtual std::string generate_pinyin();
		virtual std::string return_chinese(int a, int b, int c);
		virtual std::string return_chinese(int a, int b);
		virtual std::string return_chinese(int b);
		virtual std::string return_chinese();
		virtual std::string return_chinese_utf8s();
		virtual std::string return_chinese_utf8c();
		virtual std::string return_chinese_output_encoding();
		virtual std::string return_chinese_input_encoding();
		virtual std::string return_english();
		virtual std::string return_segmented_chinese();
		virtual std::string return_vocab_list();
		virtual std::string return_vocab_list_with_traditional();
		virtual std::string return_english_no_spacing();
		virtual std::string return_gb2312_popup();
		virtual std::string return_gb2312_popup_for_editing(int edit_element_id);
		virtual std::string return_popup();
		virtual std::string return_popup_for_editing(int edit_element_id);
		virtual std::string return_popup_for_editing_five_fields(int edit_element_id);
		virtual std::string return_pinyin_no_spacing();
		virtual std::string return_pinyin();
		virtual std::string return_jyutpin_no_spacing();
		virtual std::string return_jyutpin();

		virtual std::string escape_apostrophes(std::string fulltext);
		virtual std::string apostrophes_to_html(std::string fulltext);


};

#endif



