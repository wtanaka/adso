#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "unit.h"

class Directional: public Unit {

	public:
		Directional(Text *t);
		~Directional();

		virtual int adjust_confidence(Text *t,int a, int b, int c);
};




#endif

