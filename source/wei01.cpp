#include "wei01.h"
#include "special.h"
#include "text.h"


Wei01::Wei01(Text *t): Special(t) { myclass += ":Wei01";};
Wei01::~Wei01() {}


int Wei01::advanced(Text *t, int a, int b, int c) {

	return 1;
}
