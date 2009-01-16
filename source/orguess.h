#ifndef ORGUESS_H
#define ORGUESS_H

#include "organization.h"
#include "text.h"

class Orguess: public Organization {

	public:
		Orguess(Text *t);
		~Orguess();

		int unify(Text *t, int a, int b, int c);
};




#endif

