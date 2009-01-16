#include "address.h"
#include "text.h"
#include "noun.h"

Address::Address(Text *t): Noun(t) { 
	myclass += ":Address"; 
};
Address::~Address() {}

