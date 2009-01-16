#include "zhi02.h"
#include "special.h"
#include "text.h"


Zhi02::Zhi02(Text *t): Special(t) { myclass += ":Zhi02"; should_translate = 0; confidence+=2; };
Zhi02::~Zhi02() {}

