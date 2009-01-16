#include "polisher.h"
#include <string>

/* This class basically polishes English text produced by the Adso 
 * software. It will look for awkward phrases and replace them with 
 * more readable English.
 */
Polisher::Polisher() {
	uncapitalize = 0;
}
Polisher::~Polisher() {}

std::string Polisher::return_polished_english(std::string x) {

	  x = replace_text(x, " , ", ", ");
	  x = replace_text(x, " . ", ". ");
	  x = replace_text(x, " : ", ": ");
	  x = replace_text(x, " \" ", "\" ");
	x = replace_text(x, "\n ", "\n");
	x = replace_text(x, "  ", " ");
	x = replace_text(x, "on today", "today");
	x = replace_text(x, "having not", "not having");
	x = replace_text(x, " the the ", " the ");
	x = replace_text(x, "from in ", "since ");
	x = replace_text(x, " for at ", " for ");
	x = replace_text(x, " for since ", " ever since ");
	x = replace_text(x, "the some ", "a certain ");
	x = replace_text(x, "from since ", "since ");
	x = replace_text(x, "since from ", "since ");
	x = replace_text(x, " for to ", " in order to ");
	x = replace_text(x, "in before ", "before ");

	x = replace_text(x, ",000 million ", " billion ");
	x = replace_text(x, "000 million ", " billion ");
	x = replace_text(x, "1100 million ", "1.1 billion ");
	x = replace_text(x, "1200 million ", "1.2 billion ");
	x = replace_text(x, "1300 million ", "1.3 billion ");
	x = replace_text(x, "1400 million ", "1.4 billion ");
	x = replace_text(x, "1500 million ", "1.5 billion ");
	x = replace_text(x, "1600 million ", "1.6 billion ");
	x = replace_text(x, "1700 million ", "1.7 billion ");
	x = replace_text(x, "1800 million ", "1.8 billion ");
	x = replace_text(x, "1900 million ", "1.9 billion ");
	x = replace_text(x, "2100 million ", "2.1 billion ");
	x = replace_text(x, "2200 million ", "2.2 billion ");
	x = replace_text(x, "2300 million ", "2.3 billion ");
	x = replace_text(x, "2400 million ", "2.4 billion ");
	x = replace_text(x, "2500 million ", "2.5 billion ");
	x = replace_text(x, "2600 million ", "2.6 billion ");
	x = replace_text(x, "2700 million ", "2.7 billion ");
	x = replace_text(x, "2800 million ", "2.8 billion ");
	x = replace_text(x, "2900 million ", "2.9 billion ");
	x = replace_text(x, "3100 million ", "3.1 billion ");
	x = replace_text(x, "3200 million ", "3.2 billion ");
	x = replace_text(x, "3300 million ", "3.3 billion ");
	x = replace_text(x, "3400 million ", "3.4 billion ");
	x = replace_text(x, "3500 million ", "3.5 billion ");
	x = replace_text(x, "3600 million ", "3.6 billion ");
	x = replace_text(x, "3700 million ", "3.7 billion ");
	x = replace_text(x, "3800 million ", "3.8 billion ");
	x = replace_text(x, "3900 million ", "3.9 billion ");
	x = replace_text(x, "4100 million ", "4.1 billion ");
	x = replace_text(x, "4200 million ", "4.2 billion ");
	x = replace_text(x, "4300 million ", "4.3 billion ");
	x = replace_text(x, "4400 million ", "4.4 billion ");
	x = replace_text(x, "4500 million ", "4.5 billion ");
	x = replace_text(x, "4600 million ", "4.6 billion ");
	x = replace_text(x, "4700 million ", "4.7 billion ");
	x = replace_text(x, "4800 million ", "4.8 billion ");
	x = replace_text(x, "4900 million ", "4.9 billion ");
	x = replace_text(x, "5100 million ", "5.1 billion ");
	x = replace_text(x, "5200 million ", "5.2 billion ");
	x = replace_text(x, "5300 million ", "5.3 billion ");
	x = replace_text(x, "5400 million ", "5.4 billion ");
	x = replace_text(x, "5500 million ", "5.5 billion ");
	x = replace_text(x, "5600 million ", "5.6 billion ");
	x = replace_text(x, "5700 million ", "5.7 billion ");
	x = replace_text(x, "5800 million ", "5.8 billion ");
	x = replace_text(x, "5900 million ", "5.9 billion ");
	x = replace_text(x, "6100 million ", "6.1 billion ");
	x = replace_text(x, "6200 million ", "6.2 billion ");
	x = replace_text(x, "6300 million ", "6.3 billion ");
	x = replace_text(x, "6400 million ", "6.4 billion ");
	x = replace_text(x, "6500 million ", "6.5 billion ");
	x = replace_text(x, "6600 million ", "6.6 billion ");
	x = replace_text(x, "6700 million ", "6.7 billion ");
	x = replace_text(x, "6800 million ", "6.8 billion ");
	x = replace_text(x, "6900 million ", "6.9 billion ");
	x = replace_text(x, "7100 million ", "7.1 billion ");
	x = replace_text(x, "7200 million ", "7.2 billion ");
	x = replace_text(x, "7300 million ", "7.3 billion ");
	x = replace_text(x, "7400 million ", "7.4 billion ");
	x = replace_text(x, "7500 million ", "7.5 billion ");
	x = replace_text(x, "7600 million ", "7.6 billion ");
	x = replace_text(x, "7700 million ", "7.7 billion ");
	x = replace_text(x, "7800 million ", "7.8 billion ");
	x = replace_text(x, "7900 million ", "7.9 billion ");
	x = replace_text(x, "8100 million ", "8.1 billion ");
	x = replace_text(x, "8200 million ", "8.2 billion ");
	x = replace_text(x, "8300 million ", "8.3 billion ");
	x = replace_text(x, "8400 million ", "8.4 billion ");
	x = replace_text(x, "8500 million ", "8.5 billion ");
	x = replace_text(x, "8600 million ", "8.6 billion ");
	x = replace_text(x, "8700 million ", "8.7 billion ");
	x = replace_text(x, "8800 million ", "8.8 billion ");
	x = replace_text(x, "8900 million ", "8.9 billion ");
	x = replace_text(x, "9100 million ", "9.1 billion ");
	x = replace_text(x, "9200 million ", "9.2 billion ");
	x = replace_text(x, "9300 million ", "9.3 billion ");
	x = replace_text(x, "9400 million ", "9.4 billion ");
	x = replace_text(x, "9500 million ", "9.5 billion ");
	x = replace_text(x, "9600 million ", "9.6 billion ");
	x = replace_text(x, "9700 million ", "9.7 billion ");
	x = replace_text(x, "9800 million ", "9.8 billion ");
	x = replace_text(x, "9900 million ", "9.9 billion ");

	x = replace_text(x, " years long", " years");
	x = replace_text(x, " to to ", " to ");
	x = replace_text(x, " for from ", " from ");
	x = replace_text(x, "years of time", "years");
	x = replace_text(x, "to be to be ", "to be ");


	// UTF8 is not in the backend database, so a Quick Fix Here
	x = replace_text(x, "…", "...");
	x = replace_text(x, "……", "......");
	x = replace_text(x, "—", "--");
	x = replace_text(x, "‘", "\"");
	x = replace_text(x, "’", "\"");


		// Pinyin Conversion

	return x;
}

std::string Polisher::convert_pinyin(std::string x) {

                x = replace_text(x, "5", "");

		x = replace_text(x, "v1", "ǖ");
		x = replace_text(x, "v2", "ǘ");
		x = replace_text(x, "v3", "ǚ");
		x = replace_text(x, "v4", "ǜ");
		x = replace_text(x, "v5", "ü");
		x = replace_text(x, "ve1", "ǖe");
		x = replace_text(x, "ve2", "ǘe");
		x = replace_text(x, "ve3", "ǚe");
		x = replace_text(x, "ve4", "ǜe");
		x = replace_text(x, "ve5", "üe");
		x = replace_text(x, "vn1", "ǖn");
		x = replace_text(x, "vn2", "ǘn");
		x = replace_text(x, "vn3", "ǚn");
		x = replace_text(x, "vn4", "ǜn");
		x = replace_text(x, "vn5", "ün");

		x = replace_text(x, "a1", "ā");
		x = replace_text(x, "a2", "á");
		x = replace_text(x, "a3", "ǎ");
		x = replace_text(x, "a4", "à");
		x = replace_text(x, "a5", "a");
		x = replace_text(x, "ai1", "āi");
		x = replace_text(x, "ai2", "ái");
		x = replace_text(x, "ai3", "ǎi");
		x = replace_text(x, "ai4", "ài");
		x = replace_text(x, "ai5", "ai");
		x = replace_text(x, "an1", "ān");
		x = replace_text(x, "an2", "án");
		x = replace_text(x, "an3", "ǎn");
		x = replace_text(x, "an4", "àn");
		x = replace_text(x, "an5", "an");
		x = replace_text(x, "ao1", "āo");
		x = replace_text(x, "ao2", "áo");
		x = replace_text(x, "ao3", "ǎo");
		x = replace_text(x, "ao4", "ào");
		x = replace_text(x, "ao5", "ao");
		x = replace_text(x, "ang1", "āng");
		x = replace_text(x, "ang2", "áng");
		x = replace_text(x, "ang3", "ǎng");
		x = replace_text(x, "ang4", "àng");
		x = replace_text(x, "ang5", "ang");
		x = replace_text(x, "e1", "ē");
		x = replace_text(x, "e2", "é");
		x = replace_text(x, "e3", "ě");
		x = replace_text(x, "e4", "è");
		x = replace_text(x, "e5", "e");


		x = replace_text(x, "en1", "ēn");
		x = replace_text(x, "en2", "én");
		x = replace_text(x, "en3", "ěn");
		x = replace_text(x, "en4", "èn");
		x = replace_text(x, "en5", "en");
		x = replace_text(x, "er1", "ēr");
		x = replace_text(x, "er2", "ér");
		x = replace_text(x, "er3", "ěr");
		x = replace_text(x, "er4", "èr");
		x = replace_text(x, "er5", "er");
		x = replace_text(x, "eng1", "ēng");
		x = replace_text(x, "eng2", "éng");
		x = replace_text(x, "eng3", "ěng");
		x = replace_text(x, "eng4", "èng");
		x = replace_text(x, "eng5", "eng");
		x = replace_text(x, "ei1", "ēi");
		x = replace_text(x, "ei2", "éi");
		x = replace_text(x, "ei3", "ěi");
		x = replace_text(x, "ei4", "èi");
		x = replace_text(x, "ei5", "ei");

		x = replace_text(x, "i1", "ī");
		x = replace_text(x, "i2", "í");
		x = replace_text(x, "i3", "ǐ");
		x = replace_text(x, "i4", "ì");
		x = replace_text(x, "i5", "i");
		x = replace_text(x, "in1", "īn");
		x = replace_text(x, "in2", "ín");
		x = replace_text(x, "in3", "ǐn");
		x = replace_text(x, "in4", "ìn");
		x = replace_text(x, "in5", "in");
		x = replace_text(x, "ing1", "īng");
		x = replace_text(x, "ing2", "íng");
		x = replace_text(x, "ing3", "ǐng");
		x = replace_text(x, "ing4", "ìng");
		x = replace_text(x, "ing5", "ing");

		x = replace_text(x, "o1", "ō");
		x = replace_text(x, "o2", "ó");
		x = replace_text(x, "o3", "ǒ");
		x = replace_text(x, "o4", "ò");
		x = replace_text(x, "o5", "o");
		x = replace_text(x, "ou1", "ōu");
		x = replace_text(x, "ou2", "óu");
		x = replace_text(x, "ou3", "ǒu");
		x = replace_text(x, "ou4", "òu");
		x = replace_text(x, "ou5", "ou");
		x = replace_text(x, "ong1", "ōng");
		x = replace_text(x, "ong2", "óng");
		x = replace_text(x, "ong3", "ǒng");
		x = replace_text(x, "ong4", "òng");
		x = replace_text(x, "ong5", "ong");
		
		x = replace_text(x, "u1", "ū");
		x = replace_text(x, "u2", "ú");
		x = replace_text(x, "u3", "ǔ");
		x = replace_text(x, "u4", "ù");
		x = replace_text(x, "u5", "u");
		x = replace_text(x, "ue1", "ūe");
		x = replace_text(x, "ue2", "úe");
		x = replace_text(x, "ue3", "ǔe");
		x = replace_text(x, "ue4", "ùe");
		x = replace_text(x, "ue5", "ue");
		x = replace_text(x, "ui1", "ūi");
		x = replace_text(x, "ui2", "úi");
		x = replace_text(x, "ui3", "ǔi");
		x = replace_text(x, "ui4", "ùi");
		x = replace_text(x, "ui5", "uie");
		x = replace_text(x, "un1", "ūn");
		x = replace_text(x, "un2", "ún");
		x = replace_text(x, "un3", "ǔn");
		x = replace_text(x, "un4", "ùn");
		x = replace_text(x, "un5", "un");

  return x;

}

std::string Polisher::replace_text(std::string fulltext, std::string match, std::string replace) {

	unsigned int x = fulltext.find(match);
	while (x != std::string::npos) {
		fulltext.replace(x, match.length(), replace);
		x = fulltext.find(match);
	}

	return fulltext;

}


