#ifndef PREPOSITION_H
#define PREPOSITION_H

#include "unit.h"

class Preposition: public Unit {

	public:
		Preposition(Text *t);
		~Preposition();

		virtual int adjust_confidence(Text *t, int a, int b, int c);
};




#endif

