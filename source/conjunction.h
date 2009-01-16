#ifndef CONJUNCTION_H
#define CONJUNCTION_H

#include "unit.h"

class Conjunction: public Unit {

	public:
		Conjunction(Text *t);
		~Conjunction();


		virtual int adjust_confidence(Text *t, int a, int b, int c);
};




#endif

