#ifndef DETERMINER_H
#define DETERMINER_H

#include "special.h"
#include "text.h"
#include "unit.h"

class Determiner: public Unit {

	public:
		Determiner(Text *t);
		~Determiner();

		int adjust_confidence(Text *t, int a, int b, int c);
};


#endif
