#ifndef CUN01_H
#define CUN01_H

#include "geography.h"
#include "text.h"

class Cun01: public Geography {

	public:
		Cun01(Text *t);
		~Cun01();



                int unify(Text *t, int a, int b, int c);
                std::string generate_village_name();
};


#endif
