#ifndef MINUTE_H
#define MINUTE_H

#include "adsotime.h"
#include "text.h"

class Minute: public Time {

	public:
		Minute(Text *t, Text *a, Text *b);
		Minute(Text *t);
		~Minute();

};




#endif

