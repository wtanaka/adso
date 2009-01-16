#ifndef YU01_H
#define YU01_H

#include "special.h"

class Yu01: public Special {

	public:
		Yu01(Text *t);
		~Yu01();

		int advanced(Text *t, int a, int b, int c);
};




#endif

