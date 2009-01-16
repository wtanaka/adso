#ifndef JIANG01_H
#define JIANG01_H

#include "special.h"
#include "text.h"
class Jiang01: public Special {

	public:
		Jiang01(Text *t);
		~Jiang01();

		virtual int adjust_confidence(Text *t, int a, int b, int c);
};




#endif

