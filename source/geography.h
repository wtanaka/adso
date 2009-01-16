#ifndef GEOGRAPHY_H
#define GEOGRAPHY_H

#include "place.h"
#include "text.h"

class Geography: public Place {

	public:
		Geography(Text *t);
		~Geography();

};



#endif
