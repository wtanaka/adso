#ifndef CITY_H
#define CITY_H

#include "place.h"
#include "text.h"

class City: public Place {

	public:
		City(Text *t);
		~City();
};

#endif

