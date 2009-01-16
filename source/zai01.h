#ifndef ZAI01_H
#define ZAI01_H

#include "special.h"
#include "text.h"

class Zai01: public Special {

	public:
		Zai01(Text *t);
		~Zai01();

		virtual int advanced(Text *t, int a, int b, int c);
};




#endif

