#include "text.h"
#include "unit.h"
#include <string>

Unit::Unit(Text *text, Text *a, Text *b) : Text(text, a, b) {
	myclass += "Unit";
	post_english_spacing = 1;
	post_pinyin_spacing = 1;
};
Unit::Unit(Text *text) : Text(text) {
	myclass += "Unit";
	post_english_spacing = 1;
	post_pinyin_spacing = 1;
};
Unit::~Unit() {};


