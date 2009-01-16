#ifndef LU01_H
#define LU01_H

#include "special.h"

class Lu01: public Special {

	public:
		Lu01(Text *t);
		~Lu01();

		int unify(Text *t, int a, int b, int c);
		std::string generate_road_name();

};




#endif

