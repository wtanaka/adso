# Makefile for the Adso Translation System
#
COMPILER = g++ 
#
#
#USE_SQLITE=1
#
#
#
# This Works with MySQL
CCFLAGS = -I/usr/include/mysql 
#-mtune=i486 -fno-strength-reduce -static
CCLIBS  = -L/usr/lib/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lc -lnss_files -lnss_dns -lresolv -lc -lnss_files -lnss_dns -lresolv
#CCLIBS  = -L/usr/lib/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lc -lnss_files -lnss_dns -lresolv -lc -lnss_files -lnss_dns -lresolv -lsqlite3
#
#
# Default Compile with SQLite
#CCFLAGS = -mtune=i486 -fno-strength-reduce 
#CCLIBS  = 
#CCFLAGS = -I/usr/include/mysql -fno-strength-reduce -static
#CCFLAGS = -static -static-libgcc
#CCFLAGS = -static -Wall -O3
#CCFLAGS = -static -Wall -O3
#CCFLAGS =
#CCLIBS  = -lsqlite3 -static -static-libgcc
#CCLIBS  = 
#
#
adso: database.o adso.o code.o encoding.o feedback.o main.o memory.o ontology.o parser.o polisher.o text.o unit.o nonchinese.o noun.o number.o verb.o adverb.o adjective.o conjunction.o xing.o address.o auxiliary.o ba01.o bei01.o bi01.o bing01.o bu01.o cadverb.o special.o cai01.o chengyu.o chu01.o city.o complement.o cong01.o country.o cun01.o dang01.o dao01.o date.o day.o de01.o de02.o determiner.o geography.o propernoun.o place.o directional.o dui01.o duiyu01.o earthlybranch.o er01.o ershi01.o eryan01.o fou01.o gei01.o gen01.o hangxian01.o he01.o heavenlystem.o hou01.o hour.o jiang01.o jiu01.o ke01.o le01.o li01.o lu01.o measure.o meiyou01.o men01.o minute.o mment.o month.o name.o onomat.o organization.o orguess.o other.o person.o phonetic.o phrase.o prem.o preposition.o pronoun.o punctuation.o quan01.o qu01.o roman.o second.o shang01.o shi01.o shi02.o shi03.o suo01.o temporal.o time.o wei01.o xia01.o xian01.o year.o yi01.o you01.o you02.o you03.o yu01.o yu02.o yu03.o yue01.o zai01.o zhe01.o zhen01.o zhengzai01.o zhi01.o zhi02.o zhijian01.o zhiyi01.o zhiyou01.o zhong01.o zhou01.o zhu01.o zi01.o ziji01.o question.o 
	${COMPILER} -o adso database.o adso.o code.o encoding.o feedback.o main.o memory.o ontology.o parser.o polisher.o text.o unit.o nonchinese.o noun.o number.o verb.o adverb.o adjective.o conjunction.o xing.o address.o auxiliary.o ba01.o bei01.o bi01.o bing01.o bu01.o cadverb.o special.o cai01.o chengyu.o chu01.o city.o complement.o cong01.o country.o cun01.o dang01.o dao01.o date.o day.o de01.o de02.o determiner.o geography.o propernoun.o place.o directional.o dui01.o duiyu01.o earthlybranch.o er01.o ershi01.o eryan01.o fou01.o gei01.o gen01.o hangxian01.o he01.o heavenlystem.o hou01.o hour.o jiang01.o jiu01.o ke01.o le01.o li01.o lu01.o measure.o meiyou01.o men01.o minute.o mment.o month.o name.o onomat.o organization.o orguess.o other.o person.o phonetic.o phrase.o prem.o preposition.o pronoun.o punctuation.o quan01.o qu01.o roman.o second.o shang01.o shi01.o shi02.o shi03.o suo01.o temporal.o time.o wei01.o xia01.o xian01.o year.o yi01.o you01.o you02.o you03.o yu01.o yu02.o yu03.o yue01.o zai01.o zhe01.o zhen01.o zhengzai01.o zhi01.o zhi02.o zhijian01.o zhiyi01.o zhiyou01.o zhong01.o zhou01.o zhu01.o zi01.o ziji01.o question.o ${CCLIBS}


# Recent Changes to Database Classes
#compiled_database.o: database/compiled_database.cpp database/compiled_database.h
#	${COMPILER} ${CCFLAGS} -c database/compiled_database.cpp 
database.o: mysql_database.cpp mysql_database.h
	${COMPILER} ${CCFLAGS} -o database.o -c mysql_database.cpp
#database.o: sqlite_database.cpp sqlite_database.h
#	${COMPILER} ${CCFLAGS} -o database.o -c sqlite_database.cpp
#database.o: ghost_database.cpp ghost_database.h
#	${COMPILER} ${CCFLAGS} -o database.o -c ghost_database.cpp
adso.o: adso.cpp adso.h
	${COMPILER} ${CCFLAGS} -c adso.cpp 
code.o: code.cpp code.h
	${COMPILER} ${CCFLAGS} -c code.cpp 
encoding.o: encoding.cpp encoding.h
	${COMPILER} ${CCFLAGS} -c encoding.cpp 
feedback.o: feedback.cpp feedback.h 
	${COMPILER} ${CCFLAGS} -c feedback.cpp
main.o: main.cpp
	${COMPILER} ${CCFLAGS} -c main.cpp 
memory.o:  memory.cpp memory.h
	${COMPILER} ${CCFLAGS} -c memory.cpp
nonchinese.o:  nonchinese.cpp nonchinese.h
	${COMPILER} ${CCFLAGS} -c nonchinese.cpp
noun.o:  noun.cpp noun.h
	${COMPILER} ${CCFLAGS} -c noun.cpp
number.o:  number.cpp number.h
	${COMPILER} ${CCFLAGS} -c number.cpp
ontology.o: ontology.cpp ontology.h
	${COMPILER} ${CCFLAGS} -c ontology.cpp 
parser.o: parser.cpp
	${COMPILER} ${CCFLAGS} -c parser.cpp
polisher.o: polisher.cpp
	${COMPILER} ${CCFLAGS} -c polisher.cpp
text.o: text.cpp text.h
	${COMPILER} ${CCFLAGS} -c text.cpp 
unit.o: unit.cpp unit.h
	${COMPILER} ${CCFLAGS} -c unit.cpp 
verb.o: verb.cpp verb.h
	${COMPILER} ${CCFLAGS} -c verb.cpp 
adverb.o: adverb.cpp adverb.h
	${COMPILER} ${CCFLAGS} -c adverb.cpp 
adjective.o: adjective.cpp adjective.h
	${COMPILER} ${CCFLAGS} -c adjective.cpp 
conjunction.o: conjunction.cpp conjunction.h
	${COMPILER} ${CCFLAGS} -c conjunction.cpp 
xing.o: xing.cpp xing.h
	${COMPILER} ${CCFLAGS} -c xing.cpp 
address.o: address.cpp address.h
	${COMPILER} ${CCFLAGS} -c address.cpp 
auxiliary.o: auxiliary.cpp auxiliary.h
	${COMPILER} ${CCFLAGS} -c auxiliary.cpp 
ba01.o: ba01.cpp ba01.h
	${COMPILER} ${CCFLAGS} -c ba01.cpp 
bei01.o: bei01.cpp bei01.h
	${COMPILER} ${CCFLAGS} -c bei01.cpp 
bi01.o: bi01.cpp bi01.h
	${COMPILER} ${CCFLAGS} -c bi01.cpp 
bing01.o: bing01.cpp bing01.h
	${COMPILER} ${CCFLAGS} -c bing01.cpp 
bu01.o: bu01.cpp bu01.h
	${COMPILER} ${CCFLAGS} -c bu01.cpp 
cadverb.o: cadverb.cpp cadverb.h
	${COMPILER} ${CCFLAGS} -c cadverb.cpp 
special.o: special.cpp special.h
	${COMPILER} ${CCFLAGS} -c special.cpp 
cai01.o: cai01.cpp cai01.h
	${COMPILER} ${CCFLAGS} -c cai01.cpp 
chengyu.o: chengyu.cpp chengyu.h
	${COMPILER} ${CCFLAGS} -c chengyu.cpp 
chu01.o: chu01.cpp chu01.h
	${COMPILER} ${CCFLAGS} -c chu01.cpp 
city.o: city.cpp city.h
	${COMPILER} ${CCFLAGS} -c city.cpp 
complement.o: complement.cpp complement.h
	${COMPILER} ${CCFLAGS} -c complement.cpp 
cong01.o: cong01.cpp cong01.h
	${COMPILER} ${CCFLAGS} -c cong01.cpp 
country.o: country.cpp country.h
	${COMPILER} ${CCFLAGS} -c country.cpp 
cun01.o: cun01.cpp cun01.h
	${COMPILER} ${CCFLAGS} -c cun01.cpp 
dang01.o: dang01.cpp dang01.h
	${COMPILER} ${CCFLAGS} -c dang01.cpp 
dao01.o: dao01.cpp dao01.h
	${COMPILER} ${CCFLAGS} -c dao01.cpp 
date.o: date.cpp date.h
	${COMPILER} ${CCFLAGS} -c date.cpp 
day.o: day.cpp day.h
	${COMPILER} ${CCFLAGS} -c day.cpp 
de01.o: de01.cpp de01.h
	${COMPILER} ${CCFLAGS} -c de01.cpp 
de02.o: de02.cpp de02.h
	${COMPILER} ${CCFLAGS} -c de02.cpp 
determiner.o: determiner.cpp determiner.h
	${COMPILER} ${CCFLAGS} -c determiner.cpp 
place.o: place.cpp place.h
	${COMPILER} ${CCFLAGS} -c place.cpp 
propernoun.o: propernoun.cpp propernoun.h
	${COMPILER} ${CCFLAGS} -c propernoun.cpp 
geography.o: geography.cpp geography.h
	${COMPILER} ${CCFLAGS} -c geography.cpp 

directional.o: directional.cpp directional.h
	${COMPILER} ${CCFLAGS} -c directional.cpp 
dui01.o: dui01.cpp dui01.h
	${COMPILER} ${CCFLAGS} -c dui01.cpp 
duiyu01.o: duiyu01.cpp duiyu01.h
	${COMPILER} ${CCFLAGS} -c duiyu01.cpp 
earthlybranch.o: earthlybranch.cpp earthlybranch.h
	${COMPILER} ${CCFLAGS} -c earthlybranch.cpp 
er01.o: er01.cpp er01.h
	${COMPILER} ${CCFLAGS} -c er01.cpp 
ershi01.o: ershi01.cpp ershi01.h
	${COMPILER} ${CCFLAGS} -c ershi01.cpp 
eryan01.o: eryan01.cpp eryan01.h
	${COMPILER} ${CCFLAGS} -c eryan01.cpp 
fou01.o: fou01.cpp fou01.h
	${COMPILER} ${CCFLAGS} -c fou01.cpp 
gei01.o: gei01.cpp gei01.h
	${COMPILER} ${CCFLAGS} -c gei01.cpp 
gen01.o: gen01.cpp gen01.h
	${COMPILER} ${CCFLAGS} -c gen01.cpp 
hangxian01.o: hangxian01.cpp hangxian01.h
	${COMPILER} ${CCFLAGS} -c hangxian01.cpp 
he01.o: he01.cpp he01.h
	${COMPILER} ${CCFLAGS} -c he01.cpp 
heavenlystem.o: heavenlystem.cpp heavenlystem.h
	${COMPILER} ${CCFLAGS} -c heavenlystem.cpp 
hou01.o: hou01.cpp hou01.h
	${COMPILER} ${CCFLAGS} -c hou01.cpp 
hour.o: hour.cpp hour.h
	${COMPILER} ${CCFLAGS} -c hour.cpp 
jiang01.o: jiang01.cpp jiang01.h
	${COMPILER} ${CCFLAGS} -c jiang01.cpp 
jiu01.o: jiu01.cpp jiu01.h
	${COMPILER} ${CCFLAGS} -c jiu01.cpp 
ke01.o: ke01.cpp ke01.h
	${COMPILER} ${CCFLAGS} -c ke01.cpp 
le01.o: le01.cpp le01.h
	${COMPILER} ${CCFLAGS} -c le01.cpp 
li01.o: li01.cpp li01.h
	${COMPILER} ${CCFLAGS} -c li01.cpp 
lu01.o: lu01.cpp lu01.h
	${COMPILER} ${CCFLAGS} -c lu01.cpp 
measure.o: measure.cpp measure.h
	${COMPILER} ${CCFLAGS} -c measure.cpp 
meiyou01.o: meiyou01.cpp meiyou01.h
	${COMPILER} ${CCFLAGS} -c meiyou01.cpp
men01.o: men01.cpp men01.h
	${COMPILER} ${CCFLAGS} -c men01.cpp
minute.o: minute.cpp minute.h
	${COMPILER} ${CCFLAGS} -c minute.cpp
mment.o: mment.cpp mment.h
	${COMPILER} ${CCFLAGS} -c mment.cpp
month.o: month.cpp month.h
	${COMPILER} ${CCFLAGS} -c month.cpp
name.o: name.cpp name.h
	${COMPILER} ${CCFLAGS} -c name.cpp
onomat.o: onomat.cpp onomat.h
	${COMPILER} ${CCFLAGS} -c onomat.cpp
organization.o: organization.cpp organization.h
	${COMPILER} ${CCFLAGS} -c organization.cpp
orguess.o: orguess.cpp orguess.h
	${COMPILER} ${CCFLAGS} -c orguess.cpp
other.o: other.cpp other.h
	${COMPILER} ${CCFLAGS} -c other.cpp
person.o: person.cpp person.h
	${COMPILER} ${CCFLAGS} -c person.cpp
phonetic.o: phonetic.cpp phonetic.h
	${COMPILER} ${CCFLAGS} -c phonetic.cpp
phrase.o: phrase.cpp phrase.h
	${COMPILER} ${CCFLAGS} -c phrase.cpp
prem.o: prem.cpp prem.h
	${COMPILER} ${CCFLAGS} -c prem.cpp
preposition.o: preposition.cpp preposition.h
	${COMPILER} ${CCFLAGS} -c preposition.cpp
pronoun.o: pronoun.cpp pronoun.h
	${COMPILER} ${CCFLAGS} -c pronoun.cpp
punctuation.o: punctuation.cpp punctuation.h
	${COMPILER} ${CCFLAGS} -c punctuation.cpp
quan01.o: quan01.cpp quan01.h
	${COMPILER} ${CCFLAGS} -c quan01.cpp
qu01.o: qu01.cpp qu01.h
	${COMPILER} ${CCFLAGS} -c qu01.cpp
roman.o: roman.cpp roman.h
	${COMPILER} ${CCFLAGS} -c roman.cpp
second.o: second.cpp second.h
	${COMPILER} ${CCFLAGS} -c second.cpp
shang01.o: shang01.cpp shang01.h
	${COMPILER} ${CCFLAGS} -c shang01.cpp
shi01.o: shi01.cpp shi01.h
	${COMPILER} ${CCFLAGS} -c shi01.cpp
shi02.o: shi02.cpp shi02.h
	${COMPILER} ${CCFLAGS} -c shi02.cpp
shi03.o: shi03.cpp shi03.h
	${COMPILER} ${CCFLAGS} -c shi03.cpp
suo01.o: suo01.cpp suo01.h
	${COMPILER} ${CCFLAGS} -c suo01.cpp
temporal.o: temporal.cpp temporal.h
	${COMPILER} ${CCFLAGS} -c temporal.cpp
time.o: time.cpp time.h
	${COMPILER} ${CCFLAGS} -c time.cpp
wei01.o: wei01.cpp wei01.h
	${COMPILER} ${CCFLAGS} -c wei01.cpp
xia01.o: xia01.cpp xia01.h
	${COMPILER} ${CCFLAGS} -c xia01.cpp
xian01.o: xian01.cpp xian01.h
	${COMPILER} ${CCFLAGS} -c xian01.cpp
year.o: year.cpp year.h
	${COMPILER} ${CCFLAGS} -c year.cpp
yi01.o: yi01.cpp yi01.h
	${COMPILER} ${CCFLAGS} -c yi01.cpp
you01.o: you01.cpp you01.h
	${COMPILER} ${CCFLAGS} -c you01.cpp
you02.o: you02.cpp you02.h
	${COMPILER} ${CCFLAGS} -c you02.cpp
you03.o: you03.cpp you03.h
	${COMPILER} ${CCFLAGS} -c you03.cpp
yu01.o: yu01.cpp yu01.h
	${COMPILER} ${CCFLAGS} -c yu01.cpp
yu02.o: yu02.cpp yu02.h
	${COMPILER} ${CCFLAGS} -c yu02.cpp
yu03.o: yu03.cpp yu03.h
	${COMPILER} ${CCFLAGS} -c yu03.cpp
yue01.o: yue01.cpp yue01.h
	${COMPILER} ${CCFLAGS} -c yue01.cpp
zai01.o: zai01.cpp zai01.h
	${COMPILER} ${CCFLAGS} -c zai01.cpp
zhe01.o: zhe01.cpp zhe01.h
	${COMPILER} ${CCFLAGS} -c zhe01.cpp
zhen01.o: zhengzai01.cpp zhen01.h
	${COMPILER} ${CCFLAGS} -c zhen01.cpp
zhengzai01.o: zhengzai01.cpp zhengzai01.h
	${COMPILER} ${CCFLAGS} -c zhengzai01.cpp
zhi01.o: zhi01.cpp zhi01.h
	${COMPILER} ${CCFLAGS} -c zhi01.cpp
zhi02.o: zhi02.cpp zhi02.h
	${COMPILER} ${CCFLAGS} -c zhi02.cpp
zhijian01.o: zhijian01.cpp zhijian01.h
	${COMPILER} ${CCFLAGS} -c zhijian01.cpp
zhiyi01.o: zhiyi01.cpp zhiyi01.h
	${COMPILER} ${CCFLAGS} -c zhiyi01.cpp
zhiyou01.o: zhiyou01.cpp zhiyou01.h
	${COMPILER} ${CCFLAGS} -c zhiyou01.cpp
zhong01.o: zhong01.cpp zhong01.h
	${COMPILER} ${CCFLAGS} -c zhong01.cpp
zhou01.o: zhou01.cpp zhou01.h
	${COMPILER} ${CCFLAGS} -c zhou01.cpp
zhu01.o: zhu01.cpp zhu01.h
	${COMPILER} ${CCFLAGS} -c zhu01.cpp
zi01.o: zi01.cpp zi01.h
	${COMPILER} ${CCFLAGS} -c zi01.cpp
ziji01.o: ziji01.cpp ziji01.h
	${COMPILER} ${CCFLAGS} -c ziji01.cpp
question.o: question.cpp question.h
	${COMPILER} ${CCFLAGS} -c question.cpp


clean:
	rm -f ./*.o
	rm -f ./adso

install:
	cp -f ./adso /bin/adso




