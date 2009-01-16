#include "minute.h"
#include "adsotime.h"
#include "text.h"


Minute::Minute(Text *t, Text *a, Text *b): Time(t,a,b) { myclass += ":Minute";};
Minute::Minute(Text *t): Time(t) { myclass += ":Minute";};
Minute::~Minute() {}

