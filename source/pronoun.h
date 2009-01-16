#ifndef PRONOUN_H
#define PRONOUN_H

#include "noun.h"
#include "text.h"

class Pronoun: public Noun {

	public:
		Pronoun(Text *t);
		~Pronoun();

		virtual int adjust_confidence(Text *t, int a, int b, int c);
		virtual int advanced(Text *t, int a, int b, int c);

		std::string make_possessive(std::string x);
};




#endif

