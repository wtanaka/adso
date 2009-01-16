#ifndef NOUN_H
#define NOUN_H

#include "unit.h"

class Noun: public Unit {

	public:
		Noun(Text *t);
		~Noun();


		virtual int combine(Text *t, int a, int b, int c);


};




#endif

