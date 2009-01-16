#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "unit.h"

class Auxiliary: public Unit {

	public:
		Auxiliary(Text *t);
		~Auxiliary();

		virtual int adjust_confidence(Text *t, int a, int b, int c);

		
};




#endif

