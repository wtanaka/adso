#ifndef ENCODING_H
#define ENCODING_H



class Adso;
class Text;

#include <string>

class Encoding {


	public:

		/* 0 = unknown, 1 = gb2312, 2 = utf8 */
		int input_encoding;
		int output_encoding;
		int internal_encoding;

		/* 0 = unknown, 1 = simplified, 2 = traditional */
		int input_script;
		int output_script;
		int internal_script;


		Encoding();
		~Encoding();

		int analyse_encoding(Text *text); // 1 - gb2312, 2- UTF8  // 3 - UTF8 trad // 4 - UTF8 - simp
		int first_character_length(std::string chinese);
		int utf8_character_length(std::string chinese);
		int gb2312_character_length(std::string chinese);




		std::string report_script();
		std::string report_encoding();


		std::string convert(std::string chinese, std::string incode, std::string excode);
		std::string return_substr(std::string chinese, int startpoint, int length);
		int character_length(std::string chinese);
		int character_length(std::string chinese, std::string enco);
		int word_length(std::string chinese, std::string enco);
 

};

#endif
