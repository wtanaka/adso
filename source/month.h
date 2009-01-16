#ifndef MONTH_H
#define MONTH_H

#include "month.h"
#include "text.h"
#include "date.h"

class Month: public Date {

	public:
		Month(Text *t);
		Month(Text *t, Text *a, Text *b);
		~Month();

		std::string return_month(int x);
		int combine(Text *text, int a, int b, int c);
};




#endif

