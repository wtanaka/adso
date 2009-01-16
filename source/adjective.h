#ifndef ADJECTIVE_H
#define ADJECTIVE_H

#include "unit.h"

class Adjective: public Unit {

	public:
		Adjective(Text *t);
		~Adjective();

		int adjust_confidence(Text *t, int a, int b, int c);
};




#endif

