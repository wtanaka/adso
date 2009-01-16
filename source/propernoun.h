#ifndef PROPERNOUN_H
#define PROPERNOUN_H

#include "noun.h"
#include "text.h"

class ProperNoun: public Noun {

	public:
		ProperNoun(Text *t);
		~ProperNoun();

};


#endif
