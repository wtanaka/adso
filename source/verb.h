#ifndef VERB_H
#define VERB_H

#include "unit.h"

class Verb: public Unit {

	private:

	public:
		Verb(Text *t);
		~Verb();

		virtual std::string return_english();

		virtual int unify(Text *t, int a, int b, int c);
		virtual int adjust_confidence(Text *t, int a, int b, int c);
		virtual int advanced(Text *t, int a, int b, int c);

};




#endif

