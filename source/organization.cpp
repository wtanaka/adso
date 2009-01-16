#include "organization.h"
#include "propernoun.h"
#include "text.h"


Organization::Organization(Text *t): ProperNoun(t) { myclass += ":Organization";};
Organization::~Organization() {}

