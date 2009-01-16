#ifndef TIME_H
#define TIME_H

#include "unit.h"
#include "text.h"

class Time: public Unit {

	public:
		Time(Text *t, Text *a, Text *b);
		Time(Text *t);
		~Time();

		virtual int combine(Text *t, int a, int b, int c);


};




#endif

