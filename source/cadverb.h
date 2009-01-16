#ifndef CADVERB_H
#define CADVERB_H

#include "unit.h"

class Cadverb: public Unit {

	public:
		Cadverb(Text *t);
		~Cadverb();


		int adjust_confidence(Text *t, int a, int b, int c);
};


#endif
