#include "second.h"
#include "adsotime.h"
#include "text.h"


Second::Second(Text *t, Text *a, Text *b): Time(t, a, b) { myclass += ":Second";};
Second::Second(Text *t): Time(t) { myclass += ":Second";};
Second::~Second() {}

