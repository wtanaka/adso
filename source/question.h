#ifndef QUESTION_H
#define QUESTION_H

#include "unit.h"
#include "text.h"

class Question: public Unit {

	public:
		Question(Text *t);
		~Question();
};


#endif
