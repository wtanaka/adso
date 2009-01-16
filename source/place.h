#ifndef PLACE_H
#define PLACE_H

#include "propernoun.h"
#include "text.h"

class Place: public ProperNoun {

	public:
		Place(Text *t);
		~Place();
	
		virtual int combine(Text *t, int a, int b, int c);

};

#endif

