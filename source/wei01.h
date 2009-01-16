#ifndef WEI01_H
#define WEI01_H

#include "special.h"
#include "text.h"

class Wei01: public Special {

	public:
		Wei01(Text *t);
		~Wei01();

		virtual int advanced(Text *t, int a, int b, int c);
};




#endif

