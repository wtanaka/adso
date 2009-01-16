

#define USE_COMPILED = 1
//#define USE_MYSQL = 1
//#define USE_SQLITE = 1

#include "parser.h"
#include "text.h"
#include "adso.h"
#include "encoding.h"
#include <string.h>
#include <iostream>
#include <vector>

//#include <mysql.h>

#ifdef USE_COMPILED
#include "database/compiled_database.h"
#endif

#include "verb.h"
#include "adjective.h"
#include "adverb.h"
#include "xing.h"
#include "noun.h"
#include "conjunction.h"
#include "unit.h"
#include "nonchinese.h"
#include "number.h"

#include "address.h"
#include "auxiliary.h"
#include "ba01.h"
#include "bei01.h"
#include "bi01.h"
#include "bing01.h"
#include "bu01.h"
#include "cadverb.h"
#include "special.h"

#include "cai01.h"
#include "chengyu.h"
#include "chu01.h"
#include "city.h"
#include "complement.h"
#include "cong01.h"
#include "country.h"
#include "cun01.h"
#include "dang01.h"
#include "dao01.h"
#include "date.h"
#include "day.h"
#include "de01.h"
#include "de02.h"
#include "determiner.h"

#include "geography.h"
#include "place.h"
#include "propernoun.h"

#include "directional.h"
#include "dui01.h"
#include "duiyu01.h"
#include "earthlybranch.h"
#include "er01.h"
#include "ershi01.h"
#include "eryan01.h"
#include "fou01.h"
#include "gei01.h"
#include "gen01.h"
#include "hangxian01.h"
#include "he01.h"
#include "heavenlystem.h"
#include "hou01.h"
#include "hour.h"
#include "jiang01.h"
#include "jiu01.h"
#include "ke01.h"
#include "le01.h"
#include "li01.h"
#include "lu01.h"
#include "measure.h"

#include "meiyou01.h"
#include "men01.h"
#include "minute.h"
#include "mment.h"
#include "month.h"
#include "name.h"
#include "onomat.h"
#include "organization.h"
#include "orguess.h"
#include "other.h"
#include "person.h"
#include "phonetic.h"
#include "phrase.h"
#include "prem.h"
#include "preposition.h"
#include "pronoun.h"
#include "punctuation.h"
#include "quan01.h"
#include "qu01.h"
#include "roman.h"
#include "second.h"
#include "shang01.h"
#include "shi01.h"
#include "shi02.h"
#include "shi03.h"
#include "suo01.h"
#include "temporal.h"
#include "time.h"
#include "wei01.h"
#include "xia01.h"
#include "xian01.h"
#include "year.h"
#include "yi01.h"
#include "you01.h"
#include "you02.h"
#include "you03.h"
#include "yu01.h"
#include "yu02.h"
#include "yu03.h"
#include "yue01.h"
#include "zai01.h"
#include "zhe01.h"
#include "zhen01.h"
#include "zhengzai01.h"
#include "zhi01.h"
#include "zhi02.h"
#include "zhijian01.h"
#include "zhiyi01.h"
#include "zhiyou01.h"
#include "zhong01.h"
#include "zhou01.h"
#include "zhu01.h"
#include "zi01.h"
#include "ziji01.h"




Parser::Parser() {
	results = new std::vector<std::string>;
	no_phrases = 0;
#ifdef USE_COMPILED
	compiled_database = new Compiled_Database();
#endif
};
Parser::~Parser() {
	delete results;
#ifdef USE_COMPILED
	delete compiled_database;
#endif
}


void Parser::parse(Text *text) {
#ifdef USE_COMPILED
        parse_against_compiled_database(text);
	return;
#endif
	longest_word_match(text);
	return;
}











void Parser::add_option_from_compiled_database(Text *text, std::string english, std::string pinyin, std::string flag, std::string code, std::string table_key, std::string chinese, std::string chinese_utf8s, std::string chinese_utf8c, std::string big5, std::string newstrack, int new_item) {

			int added = 0;

			if (table_key == "-1") { 

				if (chinese == "0") { add_option(text, new Number(text), "0", "", "ling2", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "1") { add_option(text, new Number(text), "1", "", "yi1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "2") { add_option(text, new Number(text), "2", "", "er4", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "3") { add_option(text, new Number(text), "3", "", "san1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "4") { add_option(text, new Number(text), "4", "", "si4", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "5") { add_option(text, new Number(text), "5", "", "wu3", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "6") { add_option(text, new Number(text), "6", "", "liu4", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "7") { add_option(text, new Number(text), "7", "", "qi1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "8") { add_option(text, new Number(text), "8", "", "ba1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
				if (chinese == "9") { add_option(text, new Number(text), "9", "", "jiu3", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }

				add_option(text, new NonChinese(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; return; 

			}
			if (flag.find("NOUN") != std::string::npos) { add_option(text, new Noun(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("VERB") != std::string::npos) { add_option(text, new Verb(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ADVB") != std::string::npos) { add_option(text, new Adverb(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ADJT") != std::string::npos) { add_option(text, new Adjective(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("XING") != std::string::npos) { add_option(text, new Xing(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CONJ") != std::string::npos) { add_option(text, new Conjunction(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ADDRESS") != std::string::npos) { add_option(text, new Address(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("AUXV") != std::string::npos) { add_option(text, new Auxiliary(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BA01") != std::string::npos) { add_option(text, new Ba01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BEI01") != std::string::npos) { add_option(text, new Bei01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BI01") != std::string::npos) { add_option(text, new Bi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BING01") != std::string::npos) { add_option(text, new Bing01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BU01") != std::string::npos) { add_option(text, new Bu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CAD") != std::string::npos) { add_option(text, new Cadverb(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SPECIAL") != std::string::npos) { add_option(text, new Special(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CAI01") != std::string::npos) { add_option(text, new Cai01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CHENGYU") != std::string::npos) { add_option(text, new Chengyu(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CHU01") != std::string::npos) { add_option(text, new Chu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CITY") != std::string::npos) { add_option(text, new City(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("COMPLEMENT") != std::string::npos) { add_option(text, new Complement(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CONG01") != std::string::npos) { add_option(text, new Cong01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("COUNTRY") != std::string::npos) { add_option(text, new Country(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CUN01") != std::string::npos) { add_option(text, new Cun01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DANG01") != std::string::npos) { add_option(text, new Dang01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DAO01") != std::string::npos) { add_option(text, new Dao01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DATE") != std::string::npos) { add_option(text, new Date(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DAY") != std::string::npos) { add_option(text, new Day(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DE01") != std::string::npos) { add_option(text, new De01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DE02") != std::string::npos) { add_option(text, new De02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DETERMINER") != std::string::npos) { add_option(text, new Determiner(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PROPERNOUN") != std::string::npos) { add_option(text, new ProperNoun(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("GEOGRAPHY") != std::string::npos) { add_option(text, new Geography(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PLACE") != std::string::npos) { add_option(text, new Place(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DIRECTIONAL") != std::string::npos) { add_option(text, new Directional(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DUI01") != std::string::npos) { add_option(text, new Dui01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DUIYU01") != std::string::npos) { add_option(text, new Duiyu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("EARTHLYBRANCH") != std::string::npos) { add_option(text, new Place(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ER01") != std::string::npos) { add_option(text, new Er01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ERSHI01") != std::string::npos) { add_option(text, new Ershi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ERYAN01") != std::string::npos) { add_option(text, new Eryan01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("FOU01") != std::string::npos) { add_option(text, new Fou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("GEI01") != std::string::npos) { add_option(text, new Gei01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("GEN01") != std::string::npos) { add_option(text, new Gen01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HANGXIAN01") != std::string::npos) { add_option(text, new Hangxian01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HE01") != std::string::npos) { add_option(text, new He01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HEAVENLYSTEM") != std::string::npos) { add_option(text, new HeavenlyStem(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HOU01") != std::string::npos) { add_option(text, new Hou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HOUR") != std::string::npos) { add_option(text, new Hour(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("JIANG01") != std::string::npos) { add_option(text, new Jiang01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("JIU01") != std::string::npos) { add_option(text, new Jiu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("KE01") != std::string::npos) { add_option(text, new Ke01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("LE01") != std::string::npos) { add_option(text, new Le01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("LU01") != std::string::npos) { add_option(text, new Lu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("LI01") != std::string::npos) { add_option(text, new Li01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MW") != std::string::npos) { add_option(text, new Measure(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MEIYOU01") != std::string::npos) { add_option(text, new Meiyou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MEN01") != std::string::npos) { add_option(text, new Men01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MINUTE") != std::string::npos) { add_option(text, new Minute(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MEASUREMENT") != std::string::npos) { add_option(text, new Mment(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MMENT") != std::string::npos) { add_option(text, new Mment(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MONTH") != std::string::npos) { add_option(text, new Month(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("NAME") != std::string::npos) { add_option(text, new Name(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("NUM") != std::string::npos) { add_option(text, new Number(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ONOMAT") != std::string::npos) { add_option(text, new Onomat(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ORG") != std::string::npos) { add_option(text, new Organization(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("UNIFO") != std::string::npos) { add_option(text, new Orguess(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("OTHR") != std::string::npos) { add_option(text, new Other(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PERSON") != std::string::npos) { add_option(text, new Person(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PHONETIC") != std::string::npos) { add_option(text, new Phonetic(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PHRASE") != std::string::npos) { add_option(text, new Phrase(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PREM") != std::string::npos) { add_option(text, new Prem(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PREP") != std::string::npos) { add_option(text, new Preposition(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PRONOUN") != std::string::npos) { add_option(text, new Pronoun(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PUNCT") != std::string::npos) { add_option(text, new Punctuation(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("QUAN01") != std::string::npos) { add_option(text, new Quan01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("QU01") != std::string::npos) { add_option(text, new Qu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ROMAN") != std::string::npos) { add_option(text, new Roman(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SECOND") != std::string::npos) { add_option(text, new Second(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHANG01") != std::string::npos) { add_option(text, new Shang01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHI01") != std::string::npos) { add_option(text, new Shi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHI02") != std::string::npos) { add_option(text, new Shi02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHI03") != std::string::npos) { add_option(text, new Shi03(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SUO01") != std::string::npos) { add_option(text, new Suo01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("TEMPORAL") != std::string::npos) { add_option(text, new Temporal(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("TIME") != std::string::npos) { add_option(text, new Time(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("WEI01") != std::string::npos) { add_option(text, new Wei01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("XIA01") != std::string::npos) { add_option(text, new Xia01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("XIAN01") != std::string::npos) { add_option(text, new Xian01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YEAR") != std::string::npos) { add_option(text, new Year(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YI01") != std::string::npos) { add_option(text, new Yi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YOU01") != std::string::npos) { add_option(text, new You01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YOU02") != std::string::npos) { add_option(text, new You02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YOU03") != std::string::npos) { add_option(text, new You03(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YU01") != std::string::npos) { add_option(text, new Yu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YU02") != std::string::npos) { add_option(text, new Yu02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YU03") != std::string::npos) { add_option(text, new Yu03(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YUE01") != std::string::npos) { add_option(text, new Yue01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZAI01") != std::string::npos) { add_option(text, new Zai01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHE01") != std::string::npos) { add_option(text, new Zhe01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHEN01") != std::string::npos) { add_option(text, new Zhen01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHENGZAI001") != std::string::npos) { add_option(text, new Zhengzai01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHI01") != std::string::npos) { add_option(text, new Zhi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHI02") != std::string::npos) { add_option(text, new Zhi02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHIJIAN01") != std::string::npos) { add_option(text, new Zhijian01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHIYI01") != std::string::npos) { add_option(text, new Zhiyi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHIYOU01") != std::string::npos) { add_option(text, new Zhiyou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHONG01") != std::string::npos) { add_option(text, new Zhong01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHOU01") != std::string::npos) { add_option(text, new Zhou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHU01") != std::string::npos) { add_option(text, new Zhu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZI01") != std::string::npos) { add_option(text, new Zi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZIJI01") != std::string::npos) { add_option(text, new Ziji01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (added == 0) { add_option(text, new Unit(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); }

			new_item = 0;


	return;

}





void Parser::add_option(Text *maintext, Text *subtext, std::string chinese, std::string english, std::string pinyin, std::string flag, std::string code, std::string table_pkey, std::string chinese_utf8s, std::string chinese_utf8c, std::string chinese_big5, std::string newstrack, int new_item) {

	subtext->field_rank->push_back(0.0);
	subtext->field_english->push_back(english);
	subtext->field_pinyin->push_back(pinyin);
	subtext->field_code->push_back(code);
	subtext->field_pkey->push_back(table_pkey);
	subtext->field_newstrack->push_back(newstrack);

	subtext->chinese = chinese;
	subtext->english = english;
	subtext->pinyin = pinyin;
	subtext->flag = flag;
	subtext->chinese_utf8s = chinese_utf8s;
	subtext->chinese_utf8c = chinese_utf8c;
	subtext->chinese_big5 = chinese_big5;

	/* in case this is our first insertion */
	if (maintext->elements->size() == 0) { maintext->elements->push_back(new std::vector<std::vector<Text *> *>); }

	/* If this is a new item, add item to first elements vector */
	if (new_item == 1) { maintext->elements->at(0)->push_back(new std::vector<Text *>); } 
        maintext->elements->at(0)->at(maintext->elements->at(0)->size()-1)->push_back(subtext);
	return;

};
void Parser::populate_text_elements(std::string str, Text *text, std::string mytable, std::string search_field) {

	std::string chinese = "";
	std::string big5 = "";
	std::string chinese_utf8s = "";
	std::string chinese_utf8c = "";
	std::string pinyin = "";

	std::string english = "";
	std::string flag = "";
	std::string code = "";
	std::string newstrack = "";
	std::string table_key = "";

	int new_item = 1;

	// NonChinese Words (ASCII and Numbers, etc)
	if (mytable == "") {

		// We have no idea what encoding this is, or even whether it is 
		// a Chinese or Non-Chinese Element. We are here because we 
		// cannot find this character/word in our database. Despite this
		// the character will be added to the "chinese" variable.
		chinese = str;
		chinese_utf8s = str;
		chinese_utf8c = str;
		big5 = str;

		if (str == "0") { add_option(text, new Number(text), "0", "", "ling2", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "1") { add_option(text, new Number(text), "1", "", "yi1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "2") { add_option(text, new Number(text), "2", "", "er4", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "3") { add_option(text, new Number(text), "3", "", "san1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "4") { add_option(text, new Number(text), "4", "", "si4", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "5") { add_option(text, new Number(text), "5", "", "wu3", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "6") { add_option(text, new Number(text), "6", "", "liu4", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "7") { add_option(text, new Number(text), "7", "", "qi1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "8") { add_option(text, new Number(text), "8", "", "ba1", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		if (str == "9") { add_option(text, new Number(text), "9", "", "jiu3", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); return; }
		add_option(text, new NonChinese(text), chinese, chinese, chinese, "", "", "-1", chinese_utf8s, chinese_utf8c, big5, "", 1); 
		return;
	 }	
	try {

		//*results = text->adso->select_query("ENGLISH, PINYIN, FLAG, CODE, pkey, CHINESE, CHINESE_UTF8_S, CHINESE_UTF8_C, CHINESE_BIG5, NEWSTRACK", mytable, search_field, str);
		*results = text->adso->select_query("ENGLISH, PINYIN, FLAG, CODE, pkey, CHINESE, CHINESE_UTF8_S, CHINESE_UTF8_C", mytable, search_field, str);

		for (unsigned int i = 0, c = 0; c <= results->size()/10; c++, i+=10) {

			int added = 0;

			english = results->at(i+0);
			pinyin = results->at(i+1);
			flag = results->at(i+2);
			code = results->at(i+3);
			table_key = results->at(i+4);
			chinese = results->at(i+5);
			chinese_utf8s = results->at(i+6);
			chinese_utf8c = results->at(i+7);
			big5 = "";
			newstrack = "";

			if (flag.find("NOUN") != std::string::npos) { add_option(text, new Noun(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("VERB") != std::string::npos) { add_option(text, new Verb(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ADVB") != std::string::npos) { add_option(text, new Adverb(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ADJT") != std::string::npos) { add_option(text, new Adjective(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("XING") != std::string::npos) { add_option(text, new Xing(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CONJ") != std::string::npos) { add_option(text, new Conjunction(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ADDRESS") != std::string::npos) { add_option(text, new Address(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("AUXV") != std::string::npos) { add_option(text, new Auxiliary(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BA01") != std::string::npos) { add_option(text, new Ba01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BEI01") != std::string::npos) { add_option(text, new Bei01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BI01") != std::string::npos) { add_option(text, new Bi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BING01") != std::string::npos) { add_option(text, new Bing01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("BU01") != std::string::npos) { add_option(text, new Bu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CAD") != std::string::npos) { add_option(text, new Cadverb(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SPECIAL") != std::string::npos) { add_option(text, new Special(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CAI01") != std::string::npos) { add_option(text, new Cai01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CHENGYU") != std::string::npos) { add_option(text, new Chengyu(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CHU01") != std::string::npos) { add_option(text, new Chu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CITY") != std::string::npos) { add_option(text, new City(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("COMPLEMENT") != std::string::npos) { add_option(text, new Complement(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CONG01") != std::string::npos) { add_option(text, new Cong01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("COUNTRY") != std::string::npos) { add_option(text, new Country(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("CUN01") != std::string::npos) { add_option(text, new Cun01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DANG01") != std::string::npos) { add_option(text, new Dang01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DAO01") != std::string::npos) { add_option(text, new Dao01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DATE") != std::string::npos) { add_option(text, new Date(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DAY") != std::string::npos) { add_option(text, new Day(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DE01") != std::string::npos) { add_option(text, new De01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DE02") != std::string::npos) { add_option(text, new De02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DETERMINER") != std::string::npos) { add_option(text, new Determiner(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PROPERNOUN") != std::string::npos) { add_option(text, new ProperNoun(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("GEOGRAPHY") != std::string::npos) { add_option(text, new Geography(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PLACE") != std::string::npos) { add_option(text, new Place(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DIRECTIONAL") != std::string::npos) { add_option(text, new Directional(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DUI01") != std::string::npos) { add_option(text, new Dui01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("DUIYU01") != std::string::npos) { add_option(text, new Duiyu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("EARTHLYBRANCH") != std::string::npos) { add_option(text, new Place(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ER01") != std::string::npos) { add_option(text, new Er01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ERSHI01") != std::string::npos) { add_option(text, new Ershi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ERYAN01") != std::string::npos) { add_option(text, new Eryan01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("FOU01") != std::string::npos) { add_option(text, new Fou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("GEI01") != std::string::npos) { add_option(text, new Gei01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("GEN01") != std::string::npos) { add_option(text, new Gen01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HANGXIAN01") != std::string::npos) { add_option(text, new Hangxian01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HE01") != std::string::npos) { add_option(text, new He01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HEAVENLYSTEM") != std::string::npos) { add_option(text, new HeavenlyStem(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HOU01") != std::string::npos) { add_option(text, new Hou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("HOUR") != std::string::npos) { add_option(text, new Hour(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("JIANG01") != std::string::npos) { add_option(text, new Jiang01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("JIU01") != std::string::npos) { add_option(text, new Jiu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("KE01") != std::string::npos) { add_option(text, new Ke01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("LE01") != std::string::npos) { add_option(text, new Le01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("LU01") != std::string::npos) { add_option(text, new Lu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("LI01") != std::string::npos) { add_option(text, new Li01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MW") != std::string::npos) { add_option(text, new Measure(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MEIYOU01") != std::string::npos) { add_option(text, new Meiyou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MEN01") != std::string::npos) { add_option(text, new Men01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MINUTE") != std::string::npos) { add_option(text, new Minute(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MEASUREMENT") != std::string::npos) { add_option(text, new Mment(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MMENT") != std::string::npos) { add_option(text, new Mment(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MMENT") != std::string::npos) { add_option(text, new Mment(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("MONTH") != std::string::npos) { add_option(text, new Month(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("NAME") != std::string::npos) { add_option(text, new Name(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("NUM") != std::string::npos) { add_option(text, new Number(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ONOMAT") != std::string::npos) { add_option(text, new Onomat(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ORG") != std::string::npos) { add_option(text, new Organization(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("UNIFO") != std::string::npos) { add_option(text, new Orguess(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("OTHR") != std::string::npos) { add_option(text, new Other(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PERSON") != std::string::npos) { add_option(text, new Person(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PHONETIC") != std::string::npos) { add_option(text, new Phonetic(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PHRASE") != std::string::npos) { add_option(text, new Phrase(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PREM") != std::string::npos) { add_option(text, new Prem(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PREP") != std::string::npos) { add_option(text, new Preposition(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PRONOUN") != std::string::npos) { add_option(text, new Pronoun(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("PUNCT") != std::string::npos) { add_option(text, new Punctuation(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("QUAN01") != std::string::npos) { add_option(text, new Quan01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("QU01") != std::string::npos) { add_option(text, new Qu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ROMAN") != std::string::npos) { add_option(text, new Roman(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SECOND") != std::string::npos) { add_option(text, new Second(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHANG01") != std::string::npos) { add_option(text, new Shang01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHI01") != std::string::npos) { add_option(text, new Shi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHI02") != std::string::npos) { add_option(text, new Shi02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SHI03") != std::string::npos) { add_option(text, new Shi03(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("SUO01") != std::string::npos) { add_option(text, new Suo01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("TEMPORAL") != std::string::npos) { add_option(text, new Temporal(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("TIME") != std::string::npos) { add_option(text, new Time(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("WEI01") != std::string::npos) { add_option(text, new Wei01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("XIA01") != std::string::npos) { add_option(text, new Xia01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("XIAN01") != std::string::npos) { add_option(text, new Xian01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YEAR") != std::string::npos) { add_option(text, new Year(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YI01") != std::string::npos) { add_option(text, new Yi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YOU01") != std::string::npos) { add_option(text, new You01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YOU02") != std::string::npos) { add_option(text, new You02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YOU03") != std::string::npos) { add_option(text, new You03(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YU01") != std::string::npos) { add_option(text, new Yu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YU02") != std::string::npos) { add_option(text, new Yu02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YU03") != std::string::npos) { add_option(text, new Yu03(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("YUE01") != std::string::npos) { add_option(text, new Yue01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZAI01") != std::string::npos) { add_option(text, new Zai01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHE01") != std::string::npos) { add_option(text, new Zhe01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHEN01") != std::string::npos) { add_option(text, new Zhen01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHENGZAI001") != std::string::npos) { add_option(text, new Zhengzai01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHI01") != std::string::npos) { add_option(text, new Zhi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHI02") != std::string::npos) { add_option(text, new Zhi02(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHIJIAN01") != std::string::npos) { add_option(text, new Zhijian01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHIYI01") != std::string::npos) { add_option(text, new Zhiyi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHIYOU01") != std::string::npos) { add_option(text, new Zhiyou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHONG01") != std::string::npos) { add_option(text, new Zhong01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHOU01") != std::string::npos) { add_option(text, new Zhou01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZHU01") != std::string::npos) { add_option(text, new Zhu01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZI01") != std::string::npos) { add_option(text, new Zi01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (flag.find("ZIJI01") != std::string::npos) { add_option(text, new Ziji01(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); added++; new_item = 0; }
			if (added == 0) { add_option(text, new Unit(text), chinese, english, pinyin, flag, code, table_key, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item); }

			new_item = 0;
		}
	} catch (...) {
//		add_option(text, new Unit(text), str, english, "", "", "", "-1", chinese_utf8s, chinese_utf8c, big5, newstrack, 0);
	}
}















void Parser::longest_word_match(Text *text) {

	std::string temp = text->fulltext;

	std::string key = "";
	std::string query = "";
	std::string first_char = "";
	std::string word = "";


	std::string current_match = "";
	std::string current_table = "";
	std::string where1 = "";
	std::string where2 = "";
	std::string pkey = "pkey";

	std::string search_field = "CHINESE";
	std::string search_index = "character_index";
	if (text->encoding->input_encoding == 2) { search_field = "CHINESE_UTF8_S"; search_index = "utf8s_index"; }
	if (text->encoding->input_script == 2) { search_field = "CHINESE_UTF8_C"; search_index = "utf8c_index"; pkey = "first"; }



	int first_char_length = 0;
	int wordlength = 0;
	unsigned int current_match_size = 0;

	first_char_length = text->encoding->first_character_length(temp);
	
	while (first_char_length > 0) {

		// Default to a Single Character	
		wordlength = first_char_length;
		if (temp.length() < first_char.length()) { first_char_length = 1; }
 
		first_char = temp.substr(0, first_char_length);
		while (first_char.find("%") != std::string::npos || first_char.find("\\") != std::string::npos || first_char.find('\"') != std::string::npos || first_char.find("_") != std::string::npos || first_char.find("\?") != std::string::npos) {
			first_char = temp[0];
			temp = temp.substr(1);
			populate_text_elements(first_char, text, "", search_field);
			first_char_length = text->encoding->first_character_length(temp);
			first_char = temp.substr(0, first_char_length);
		}

		if (first_char.length() > 0) {

		// Use Database to Identify Longer Matches
		*results = text->adso->select_query(pkey, search_index, "name", first_char);


		if (results->size() > 0) {

			key = results->at(0);

			// Fetch All Possibilities
			current_table = "_" + key;
			current_match = first_char;
			current_match_size = first_char_length;
			*results = text->adso->select_query_wildcard(search_field, current_table, search_field, where2);


			// find the largest match
			for (unsigned int i = 0; i < results->size(); i++) {
				if (results->at(i).length() > current_match_size) {
					if (temp.find(results->at(i)) == 0) {
						current_match = results->at(i);
						current_match_size = current_match.length();
					}
				}
			}

			wordlength = current_match_size;

		} else {

			// Not Found in Index - (ASCII?) add as single char
			current_table = "";
			wordlength = 1;
		}


		// Add Word 
		word = temp.substr(0, wordlength);
		temp = temp.substr(wordlength);
		populate_text_elements(word, text, current_table, search_field);


		// Prepare for Next Loop
		first_char_length = text->encoding->first_character_length(temp);

		} // first_char.length() > 0
   	} // while
	return;
}


#ifdef USE_COMPILED
void Parser::parse_against_compiled_database(Text *text) {

	std::string temp = text->fulltext;
	std::vector<int> matches;

	std::string key = "";
	std::string query = "";
	std::string first_char = "";
	std::string word = "";
	std::string current_match = "";
	std::string tempstr = "";
	std::string pkey = "";
	std::string pos = "";

	int new_item = 1;
	int table = -1;
	int first_char_length = 0;
	int wordlength = 0;
	unsigned int current_match_size = 1;
	int search_index = 3;  // 	3 = GB2312
			       //	4 = UTF-8 Simplified
			       //	5 = UTF-8 Traditional
	if (text->encoding->input_encoding == 2) { search_index = 4; }



	first_char_length = text->encoding->first_character_length(temp);
	while (first_char_length > 0) {

		// Default to a Single Character	
		wordlength = first_char_length;
		first_char = temp.substr(0, first_char_length);


		// Ask for the TABLE
                table = -1; // get the pkey table
		if (search_index == 3) { table = compiled_database->search_index_gb2312(first_char); }
		
		// Question Mark can act problematically due to encoding issues
		if (first_char.find('?') != std::string::npos) { table = -1; }


		if (table != -1) {

			current_match = first_char;
			current_match_size = first_char_length;

			// Get Everything from that Table
			//char * (*answer)[11];
			char * (*answer)[11] = (char * (*)[11]) compiled_database->return_table(table);
  			for (int i = 0;;i++) {
				pkey = answer[i][0];
				if (pkey.find("@") != std::string::npos) { break; }
				tempstr = answer[i][1];
				if (tempstr.length() < current_match_size) {
				} else { 
			
					// See if these are equal
					if (tempstr.length() > current_match_size) {
						if (tempstr.length() <= temp.length()) {
							if (tempstr == temp.substr(0, tempstr.length())) {
                                                                if (no_phrases == 0) {
                                                     	                current_match_size = tempstr.length();
                                                                } else {
                                                                        pos = answer[i][5];
                                                                        if (pos.find("PHRASE") == std::string::npos) {
                                                                        	current_match_size = tempstr.length();
                                                                	}
                                                         	}
 

							}
						}
					}
				}
			}


			int new_item = 1;
  			for (int i = 0;;i++) {
				pkey = answer[i][0];
				if (pkey.find("@") != std::string::npos) { break; }
				tempstr = answer[i][1];
				if (tempstr.length() == current_match_size) {
					if (tempstr == temp.substr(0, tempstr.length())) {

						std::string english = answer[i][6];
						std::string pinyin = answer[i][7];
						std::string chinese = answer[i][1];
						std::string chinese_utf8s = answer[i][2];
						std::string chinese_utf8c = answer[i][3];
						std::string big5 = answer[i][4];
						std::string flag = answer[i][5];
						std::string code = answer[i][8];
						std::string table_key = answer[i][0];
						std::string newstrack = "";
						add_option_from_compiled_database(text, english, pinyin, flag, code, table_key, chinese, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item);
						new_item = 0;
					}
				}
			}

			wordlength = current_match_size;

		} else {
			if (search_index == 4) { 
//				table = compiled_database->search_index_utf8s(first_char);
				table = compiled_database->search_index_utf8s(first_char);
				if (first_char.find("?") != std::string::npos) { table = -1; }
				if (table != -1) {

					current_match = first_char;
					current_match_size = first_char_length;

					// Get Everything from that Table
					//char * (*answer)[11];
					char * (*answer)[11] = (char * (*)[11]) compiled_database->return_table(table);
  					for (int i = 0;;i++) {
						pkey = answer[i][0];
						if (pkey.find("@") != std::string::npos) { break; }
						tempstr = answer[i][2];
						if (tempstr.length() < current_match_size) {
						} else { 
				
							// See if these are equal
							if (tempstr.length() > current_match_size) {
								if (tempstr.length() <= temp.length()) {
									if (tempstr == temp.substr(0, tempstr.length())) {
        		                                                        if (no_phrases == 0) {
                		                                                        current_match_size = tempstr.length();
                        		                                        } else {
		                                                                	pos = answer[i][5];
											if (pos.find("PHRASE") == std::string::npos) {
                		                                                        	current_match_size = tempstr.length();
											}
										}
									}
								}
							}
						}
					}


					new_item = 1;
		  			for (int i = 0;;i++) {
						pkey = answer[i][0];
						if (pkey.find("@") != std::string::npos) { break; }
						tempstr = answer[i][2];
						if (tempstr.length() == current_match_size) {
							if (tempstr == temp.substr(0, tempstr.length())) {

								std::string english = answer[i][6];
								std::string pinyin = answer[i][7];
								std::string chinese = answer[i][1];
								std::string chinese_utf8s = answer[i][2];
								std::string chinese_utf8c = answer[i][3];
								std::string big5 = answer[i][4];
								std::string flag = answer[i][5];
								std::string code = answer[i][8];
								std::string table_key = answer[i][0];
								std::string newstrack = "";
								add_option_from_compiled_database(text, english, pinyin, flag, code, table_key, chinese, chinese_utf8s, chinese_utf8c, big5, newstrack, new_item);
								new_item = 0;
							}
						}
					}
					wordlength = current_match_size;
				} else {
					wordlength = 1;
					word = temp.substr(0, wordlength);
					add_option_from_compiled_database(text, "", "", "", "", "-1", word, word, word, word, "", 1);
					new_item = 0;
				}
			} else {
				// Add as ASCII
				wordlength = 1;
				word = temp.substr(0, wordlength);
				add_option_from_compiled_database(text, "", "", "", "", "-1", word, word, word, word, "", 1);
				new_item = 0;
			}
		}


		if (new_item == 1) {
			wordlength = 1;
			word = temp.substr(0, wordlength);
			temp = temp.substr(wordlength);
			add_option_from_compiled_database(text, word, "", "", "", "-1", word, word, word, "", "", new_item);
		}

		// Prepare for Next Loop
                if (temp.length() > wordlength) {
		  temp = temp.substr(wordlength);
		  first_char_length = text->encoding->first_character_length(temp);
		} else {
                  temp = "";
                  first_char_length = 0;
                }
	}
	return;
}
#endif



