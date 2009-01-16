#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>

/*
 * This class contains the interface to all of the functions that 
 * grab information from translated text on the fly to create/generate
 * new content, or get definitions for existing content. At the present 
 * they largely interface with files that can be processed manually 
 * although this can change in the future as we gain the ability 
 * to process large volumes of files in real-time (ie. search).
 */
class Feedback {

	public:
		Feedback();
		~Feedback();

		void aspect_words(std::string x, std::string y, std::string pin);
		void plural_words(std::string x, std::string y, std::string pin);
		void phonetic_words(std::string x, void *x, std::string pin);
};


#endif
