#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include "propernoun.h"
#include "text.h"

class Organization: public ProperNoun {

	public:
		Organization(Text *t);
		~Organization();

};




#endif

