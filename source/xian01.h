#ifndef XIAN01_H
#define XIAN01_H

#include "special.h"
#include "text.h"

class Xian01: public Special {

	public:
		Xian01(Text *t);
		~Xian01();

		int unify(Text *t, int a, int b, int c);
		std::string generate_county_name();
};




#endif

