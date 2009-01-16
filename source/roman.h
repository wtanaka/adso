#ifndef ROMAN_H
#define ROMAN_H

#include "unit.h"
#include "text.h"

class Roman: public Unit {

	public:
		Roman(Text *t);
		~Roman();

		int pre_unify(Text *parent, int a, int b, int c);


};




#endif

