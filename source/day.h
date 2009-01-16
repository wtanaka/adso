#ifndef DAY_H
#define DAY_H

#include "date.h"
#include "text.h"

class Day: public Date {

	public:
		Day(Text *t, Text *a, Text *b);
		Day(Text *t);
		~Day();

		std::string return_day(int x);
		virtual int combine(Text *t, int a, int b, int c);
};


#endif
