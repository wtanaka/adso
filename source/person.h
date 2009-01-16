#ifndef PERSON_H
#define PERSON_H

#include "propernoun.h"
#include "text.h"

class Person: public ProperNoun {

	public:
		Person(Text *t);
		~Person();


		int combine(Text *parent, int a, int b, int c);
		int combine2(Text *parent, int a, int b, int c);
		int advanced(Text *parent, int a, int b, int c);

};




#endif

