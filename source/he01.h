#ifndef HE01_H
#define HE01_H

#include "special.h"

class He01: public Special {

	public:
		He01(Text *t);
		~He01();

		int advanced(Text *t, int a, int b, int c);
};




#endif

