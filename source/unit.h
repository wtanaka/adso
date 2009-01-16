#ifndef UNIT_H
#define UNIT_H


#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "text.h"

class Adso;

class Unit: public Text {

	private:




	public:
		Unit(Text *text, Text *a, Text *b);
		Unit(Text *text);
		~Unit();


};

#endif
