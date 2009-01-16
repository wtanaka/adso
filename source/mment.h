#ifndef MMENT_H
#define MMENT_H

#include "unit.h"
#include "text.h"

class Mment: public Unit {

	public:
		Mment(Text *t);
		~Mment();

		virtual int adjust_confidence(Text *t, int a, int b, int c);
};




#endif

