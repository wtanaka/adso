#ifndef PHONETIC_H
#define PHONETIC_H

#include "unit.h"
#include "text.h"

class Phonetic: public Unit {

	public:
		Phonetic(Text *t);
		~Phonetic();

		int unify(Text *parent, int a, int b, int c);
		int combine(Text *parent, int a, int b, int c);

		std::string return_english();

};




#endif

