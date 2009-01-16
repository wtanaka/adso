#ifndef POLISHER_H
#define POLISHER_H

#include <string>

class Polisher {

	public:
		Polisher();
		~Polisher();

		int uncapitalize;
		std::string return_polished_english(std::string x);
		std::string convert_pinyin(std::string x); // numeric 2 tonal utf8
		std::string replace_text(std::string a, std::string b, std::string c);	

};


#endif
