#ifndef OTHER_H
#define OTHER_H

#include "unit.h"
#include "text.h"

class Other: public Unit {

	public:
		Other(Text *t);
		~Other();

		int adjust_confidence(Text *t, int a, int b, int c);
};




#endif

