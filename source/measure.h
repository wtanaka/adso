#ifndef MEASURE_H
#define MEASURE_H

#include "unit.h"

class Measure: public Unit {

	public:
		Measure(Text *t);
		~Measure();

		virtual int adjust_confidence(Text *t, int a, int b, int c);
		virtual int advanced(Text *t, int a, int b, int c);
};




#endif

