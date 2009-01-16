#ifndef HOUR_H
#define HOUR_H

#include "time.h"

class Hour: public Time {

	public:
		Hour(Text *t, Text *a, Text *b);
		Hour(Text *t);
		~Hour();

		std::string itoa(int x);
		int combine(Text *t, int a, int b, int c);
};




#endif

