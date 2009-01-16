#ifndef COUNTRY_H
#define COUNTRY_H

#include "place.h"
#include "text.h"

class Country: public Place {

	public:
		Country(Text *t);
		~Country();


		int adjust_confidence(Text *t, int a, int b, int c);
		int advanced(Text *t, int a, int b, int c);

};


#endif
