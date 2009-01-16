#ifndef YEAR_H
#define YEAR_H

#include "date.h"
#include "text.h"

class Year: public Date {

	public:
		Year(Text *t, Text *a, Text *b);
		Year(Text *t);
		~Year();

		virtual int combine(Text *t, int a, int b, int c);

};




#endif

