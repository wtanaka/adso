#ifndef ZHI01_H
#define ZHI01_H

#include "special.h"
#include "text.h"

class Zhi01: public Special {

	public:
		Zhi01(Text *t);
		~Zhi01();

		virtual int advanced(Text *t, int a, int b, int c);

};




#endif

