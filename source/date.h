#ifndef DATE_H
#define DATE_H

#include "unit.h"
#include "text.h"

class Date: public Unit {

	public:
		Date(Text *t);
		Date(Text *t, Text *a, Text *b);
		~Date();

		virtual int combine2(Text *t, int a, int b, int c);

};


#endif
