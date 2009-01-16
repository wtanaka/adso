#ifndef ZHEN01_H
#define ZHEN01_H

#include "special.h"
#include "text.h"

class Zhen01: public Special {

	public:
		Zhen01(Text *t);
		~Zhen01();

		int unify(Text *t, int a, int b, int c);
		std::string generate_township_name();
};




#endif

