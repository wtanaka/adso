# Makefile for the Adso Translation System
#
COMPILER = g++ 
#
#
#USE_SQLITE=1
#
#
#
# This Compiles the Data into the Application Rather than Using an External DB
#
#
# Default Compile with SQLite
CCFLAGS = 
#-mtune=i486 -fno-strength-reduce 
CCLIBS  = 
#
#
adso: database.o adso.o code.o encoding.o feedback.o main.o memory.o ontology.o parser.o polisher.o text.o unit.o nonchinese.o noun.o number.o verb.o adverb.o adjective.o conjunction.o xing.o address.o auxiliary.o ba01.o bei01.o bi01.o bing01.o bu01.o cadverb.o special.o cai01.o chengyu.o chu01.o city.o complement.o cong01.o country.o cun01.o dang01.o dao01.o date.o day.o de01.o de02.o determiner.o geography.o propernoun.o place.o directional.o dui01.o duiyu01.o earthlybranch.o er01.o ershi01.o eryan01.o fou01.o gei01.o gen01.o hangxian01.o he01.o heavenlystem.o hou01.o hour.o jiang01.o jiu01.o ke01.o le01.o li01.o lu01.o measure.o meiyou01.o men01.o minute.o mment.o month.o name.o onomat.o organization.o orguess.o other.o person.o phonetic.o phrase.o prem.o preposition.o pronoun.o punctuation.o quan01.o qu01.o roman.o second.o shang01.o shi01.o shi02.o shi03.o suo01.o temporal.o time.o wei01.o xia01.o xian01.o year.o yi01.o you01.o you02.o you03.o yu01.o yu02.o yu03.o yue01.o zai01.o zhe01.o zhen01.o zhengzai01.o zhi01.o zhi02.o zhijian01.o zhiyi01.o zhiyou01.o zhong01.o zhou01.o zhu01.o zi01.o ziji01.o question.o database/db1.o database/db2.o database/db3.o database/db4.o database/db5.o database/db6.o database/db7.o database/db8.o database/db9.o database/db10.o database/db11.o database/db12.o database/db13.o database/db14.o database/db15.o database/db16.o database/db17.o database/db18.o database/db19.o database/db20.o database/db21.o database/db22.o database/db23.o database/db24.o database/db25.o database/db26.o database/db27.o database/db28.o database/db29.o database/db30.o database/db31.o database/db32.o database/db33.o database/db34.o database/db35.o database/db36.o database/db37.o database/db38.o database/db39.o database/db40.o database/db41.o database/db42.o database/db43.o database/db44.o database/db45.o database/db46.o database/db47.o database/db48.o database/db49.o database/db50.o database/db51.o database/db52.o database/db53.o database/db54.o database/db55.o database/db56.o database/db57.o database/db58.o database/db59.o database/db60.o database/db61.o database/db62.o database/db63.o database/db64.o database/db65.o database/db66.o database/db67.o database/db68.o database/db69.o database/db70.o database/db71.o database/db72.o database/db73.o database/db74.o database/db75.o database/db76.o database/db77.o database/db78.o database/db79.o database/db80.o database/db81.o database/db82.o database/db83.o database/db84.o database/db85.o database/db86.o database/db87.o database/db88.o database/db89.o database/db90.o database/db91.o database/db92.o database/db93.o database/db94.o database/db95.o database/db96.o database/db97.o database/db98.o database/db99.o database/db100.o database/db101.o database/db102.o database/db103.o database/db104.o database/db105.o database/db106.o database/db107.o database/db108.o database/db109.o database/db110.o database/db111.o database/db112.o database/db113.o database/db114.o database/db115.o database/db116.o database/db117.o database/db118.o database/db119.o database/db120.o database/db121.o database/db122.o database/db123.o database/db124.o database/db125.o database/db126.o database/db127.o database/db128.o database/db129.o database/db130.o database/db131.o database/db132.o database/db133.o database/db134.o database/db135.o database/db136.o database/db137.o database/db138.o database/db139.o database/db140.o database/db141.o database/db142.o database/db143.o database/db144.o database/db145.o database/db146.o database/db147.o database/db148.o database/db149.o database/db150.o database/db151.o database/db152.o database/db153.o database/db154.o database/db155.o database/db156.o database/db157.o database/db158.o database/db159.o database/db160.o database/db161.o database/db162.o database/db163.o database/db164.o database/db165.o database/db166.o database/db167.o database/db168.o database/db169.o database/db170.o database/db171.o database/db172.o database/db173.o database/db174.o database/db175.o database/db176.o database/db177.o database/db178.o database/db179.o database/db180.o database/db181.o database/db182.o database/db183.o database/db184.o database/db185.o database/db186.o database/db187.o database/db188.o database/db189.o database/db190.o database/db191.o database/db192.o database/db193.o database/db194.o database/db195.o database/db196.o database/db197.o database/db198.o database/db199.o database/db200.o database/db201.o database/db202.o database/db203.o database/db204.o database/db205.o database/db206.o database/db207.o database/db208.o database/db209.o database/db210.o database/db211.o database/db212.o database/db213.o database/db214.o database/db215.o database/db216.o database/db217.o database/db218.o database/db219.o database/db220.o database/db221.o database/db222.o database/db223.o database/db224.o database/db225.o database/db226.o database/db227.o database/db228.o database/db229.o database/db230.o database/db231.o database/db232.o database/db233.o database/db234.o database/db235.o database/db236.o database/db237.o database/db238.o database/db239.o database/db240.o database/db241.o database/db242.o database/db243.o database/db244.o database/db245.o database/db246.o database/db247.o database/db248.o database/db249.o database/db250.o database/db251.o database/db252.o database/db253.o database/db254.o database/db255.o database/db256.o database/db257.o database/db258.o database/db259.o database/db260.o database/db261.o database/db262.o database/db263.o database/db264.o database/db265.o database/db266.o database/db267.o database/db268.o database/db269.o database/db270.o database/db271.o database/db272.o database/db273.o database/db274.o database/db275.o database/db276.o database/db277.o database/db278.o database/db279.o database/db280.o database/db281.o database/db282.o database/db283.o database/db284.o database/db285.o database/db286.o database/db287.o database/db288.o database/db289.o database/db290.o database/db291.o database/db292.o database/db293.o database/db294.o database/db295.o database/db296.o database/db297.o database/db298.o database/db299.o database/db300.o database/db301.o database/db302.o database/db303.o database/db304.o database/db305.o database/db306.o database/db307.o database/db308.o database/db309.o database/db310.o database/db311.o database/db312.o database/db313.o database/db314.o database/db315.o database/db316.o database/db317.o database/db318.o database/db319.o database/db320.o database/db321.o database/db322.o database/db323.o database/db324.o database/db325.o database/db326.o database/db327.o database/db328.o database/db329.o database/db330.o database/db331.o database/db332.o database/db333.o database/db334.o database/db335.o database/db336.o database/db337.o database/db338.o database/db339.o database/db340.o database/db341.o database/db342.o database/db343.o database/db344.o database/db345.o database/db346.o database/db347.o database/db348.o database/db349.o database/db350.o database/compiled_database.o
	${COMPILER} -o adso database.o adso.o code.o encoding.o feedback.o main.o memory.o ontology.o parser.o polisher.o text.o unit.o nonchinese.o noun.o number.o verb.o adverb.o adjective.o conjunction.o xing.o address.o auxiliary.o ba01.o bei01.o bi01.o bing01.o bu01.o cadverb.o special.o cai01.o chengyu.o chu01.o city.o complement.o cong01.o country.o cun01.o dang01.o dao01.o date.o day.o de01.o de02.o determiner.o geography.o propernoun.o place.o directional.o dui01.o duiyu01.o earthlybranch.o er01.o ershi01.o eryan01.o fou01.o gei01.o gen01.o hangxian01.o he01.o heavenlystem.o hou01.o hour.o jiang01.o jiu01.o ke01.o le01.o li01.o lu01.o measure.o meiyou01.o men01.o minute.o mment.o month.o name.o onomat.o organization.o orguess.o other.o person.o phonetic.o phrase.o prem.o preposition.o pronoun.o punctuation.o quan01.o qu01.o roman.o second.o shang01.o shi01.o shi02.o shi03.o suo01.o temporal.o time.o wei01.o xia01.o xian01.o year.o yi01.o you01.o you02.o you03.o yu01.o yu02.o yu03.o yue01.o zai01.o zhe01.o zhen01.o zhengzai01.o zhi01.o zhi02.o zhijian01.o zhiyi01.o zhiyou01.o zhong01.o zhou01.o zhu01.o zi01.o ziji01.o question.o database/db1.o database/db2.o database/db3.o database/db4.o database/db5.o database/db6.o database/db7.o database/db8.o database/db9.o database/db10.o database/db11.o database/db12.o database/db13.o database/db14.o database/db15.o database/db16.o database/db17.o database/db18.o database/db19.o database/db20.o database/db21.o database/db22.o database/db23.o database/db24.o database/db25.o database/db26.o database/db27.o database/db28.o database/db29.o database/db30.o database/db31.o database/db32.o database/db33.o database/db34.o database/db35.o database/db36.o database/db37.o database/db38.o database/db39.o database/db40.o database/db41.o database/db42.o database/db43.o database/db44.o database/db45.o database/db46.o database/db47.o database/db48.o database/db49.o database/db50.o database/db51.o database/db52.o database/db53.o database/db54.o database/db55.o database/db56.o database/db57.o database/db58.o database/db59.o database/db60.o database/db61.o database/db62.o database/db63.o database/db64.o database/db65.o database/db66.o database/db67.o database/db68.o database/db69.o database/db70.o database/db71.o database/db72.o database/db73.o database/db74.o database/db75.o database/db76.o database/db77.o database/db78.o database/db79.o database/db80.o database/db81.o database/db82.o database/db83.o database/db84.o database/db85.o database/db86.o database/db87.o database/db88.o database/db89.o database/db90.o database/db91.o database/db92.o database/db93.o database/db94.o database/db95.o database/db96.o database/db97.o database/db98.o database/db99.o database/db100.o database/db101.o database/db102.o database/db103.o database/db104.o database/db105.o database/db106.o database/db107.o database/db108.o database/db109.o database/db110.o database/db111.o database/db112.o database/db113.o database/db114.o database/db115.o database/db116.o database/db117.o database/db118.o database/db119.o database/db120.o database/db121.o database/db122.o database/db123.o database/db124.o database/db125.o database/db126.o database/db127.o database/db128.o database/db129.o database/db130.o database/db131.o database/db132.o database/db133.o database/db134.o database/db135.o database/db136.o database/db137.o database/db138.o database/db139.o database/db140.o database/db141.o database/db142.o database/db143.o database/db144.o database/db145.o database/db146.o database/db147.o database/db148.o database/db149.o database/db150.o database/db151.o database/db152.o database/db153.o database/db154.o database/db155.o database/db156.o database/db157.o database/db158.o database/db159.o database/db160.o database/db161.o database/db162.o database/db163.o database/db164.o database/db165.o database/db166.o database/db167.o database/db168.o database/db169.o database/db170.o database/db171.o database/db172.o database/db173.o database/db174.o database/db175.o database/db176.o database/db177.o database/db178.o database/db179.o database/db180.o database/db181.o database/db182.o database/db183.o database/db184.o database/db185.o database/db186.o database/db187.o database/db188.o database/db189.o database/db190.o database/db191.o database/db192.o database/db193.o database/db194.o database/db195.o database/db196.o database/db197.o database/db198.o database/db199.o database/db200.o database/db201.o database/db202.o database/db203.o database/db204.o database/db205.o database/db206.o database/db207.o database/db208.o database/db209.o database/db210.o database/db211.o database/db212.o database/db213.o database/db214.o database/db215.o database/db216.o database/db217.o database/db218.o database/db219.o database/db220.o database/db221.o database/db222.o database/db223.o database/db224.o database/db225.o database/db226.o database/db227.o database/db228.o database/db229.o database/db230.o database/db231.o database/db232.o database/db233.o database/db234.o database/db235.o database/db236.o database/db237.o database/db238.o database/db239.o database/db240.o database/db241.o database/db242.o database/db243.o database/db244.o database/db245.o database/db246.o database/db247.o database/db248.o database/db249.o database/db250.o database/db251.o database/db252.o database/db253.o database/db254.o database/db255.o database/db256.o database/db257.o database/db258.o database/db259.o database/db260.o database/db261.o database/db262.o database/db263.o database/db264.o database/db265.o database/db266.o database/db267.o database/db268.o database/db269.o database/db270.o database/db271.o database/db272.o database/db273.o database/db274.o database/db275.o database/db276.o database/db277.o database/db278.o database/db279.o database/db280.o database/db281.o database/db282.o database/db283.o database/db284.o database/db285.o database/db286.o database/db287.o database/db288.o database/db289.o database/db290.o database/db291.o database/db292.o database/db293.o database/db294.o database/db295.o database/db296.o database/db297.o database/db298.o database/db299.o database/db300.o database/db301.o database/db302.o database/db303.o database/db304.o database/db305.o database/db306.o database/db307.o database/db308.o database/db309.o database/db310.o database/db311.o database/db312.o database/db313.o database/db314.o database/db315.o database/db316.o database/db317.o database/db318.o database/db319.o database/db320.o database/db321.o database/db322.o database/db323.o database/db324.o database/db325.o database/db326.o database/db327.o database/db328.o database/db329.o database/db330.o database/db331.o database/db332.o database/db333.o database/db334.o database/db335.o database/db336.o database/db337.o database/db338.o database/db339.o database/db340.o database/db341.o database/db342.o database/db343.o database/db344.o database/db345.o database/db346.o database/db347.o database/db348.o database/db349.o database/db350.o database/compiled_database.o ${CCLIBS}
	ar r libadso.a database.o adso.o code.o encoding.o feedback.o main.o memory.o ontology.o parser.o polisher.o text.o unit.o nonchinese.o noun.o number.o verb.o adverb.o adjective.o conjunction.o xing.o address.o auxiliary.o ba01.o bei01.o bi01.o bing01.o bu01.o cadverb.o special.o cai01.o chengyu.o chu01.o city.o complement.o cong01.o country.o cun01.o dang01.o dao01.o date.o day.o de01.o de02.o determiner.o geography.o propernoun.o place.o directional.o dui01.o duiyu01.o earthlybranch.o er01.o ershi01.o eryan01.o fou01.o gei01.o gen01.o hangxian01.o he01.o heavenlystem.o hou01.o hour.o jiang01.o jiu01.o ke01.o le01.o li01.o lu01.o measure.o meiyou01.o men01.o minute.o mment.o month.o name.o onomat.o organization.o orguess.o other.o person.o phonetic.o phrase.o prem.o preposition.o pronoun.o punctuation.o quan01.o qu01.o roman.o second.o shang01.o shi01.o shi02.o shi03.o suo01.o temporal.o time.o wei01.o xia01.o xian01.o year.o yi01.o you01.o you02.o you03.o yu01.o yu02.o yu03.o yue01.o zai01.o zhe01.o zhen01.o zhengzai01.o zhi01.o zhi02.o zhijian01.o zhiyi01.o zhiyou01.o zhong01.o zhou01.o zhu01.o zi01.o ziji01.o question.o database/db1.o database/db2.o database/db3.o database/db4.o database/db5.o database/db6.o database/db7.o database/db8.o database/db9.o database/db10.o database/db11.o database/db12.o database/db13.o database/db14.o database/db15.o database/db16.o database/db17.o database/db18.o database/db19.o database/db20.o database/db21.o database/db22.o database/db23.o database/db24.o database/db25.o database/db26.o database/db27.o database/db28.o database/db29.o database/db30.o database/db31.o database/db32.o database/db33.o database/db34.o database/db35.o database/db36.o database/db37.o database/db38.o database/db39.o database/db40.o database/db41.o database/db42.o database/db43.o database/db44.o database/db45.o database/db46.o database/db47.o database/db48.o database/db49.o database/db50.o database/db51.o database/db52.o database/db53.o database/db54.o database/db55.o database/db56.o database/db57.o database/db58.o database/db59.o database/db60.o database/db61.o database/db62.o database/db63.o database/db64.o database/db65.o database/db66.o database/db67.o database/db68.o database/db69.o database/db70.o database/db71.o database/db72.o database/db73.o database/db74.o database/db75.o database/db76.o database/db77.o database/db78.o database/db79.o database/db80.o database/db81.o database/db82.o database/db83.o database/db84.o database/db85.o database/db86.o database/db87.o database/db88.o database/db89.o database/db90.o database/db91.o database/db92.o database/db93.o database/db94.o database/db95.o database/db96.o database/db97.o database/db98.o database/db99.o database/db100.o database/db101.o database/db102.o database/db103.o database/db104.o database/db105.o database/db106.o database/db107.o database/db108.o database/db109.o database/db110.o database/db111.o database/db112.o database/db113.o database/db114.o database/db115.o database/db116.o database/db117.o database/db118.o database/db119.o database/db120.o database/db121.o database/db122.o database/db123.o database/db124.o database/db125.o database/db126.o database/db127.o database/db128.o database/db129.o database/db130.o database/db131.o database/db132.o database/db133.o database/db134.o database/db135.o database/db136.o database/db137.o database/db138.o database/db139.o database/db140.o database/db141.o database/db142.o database/db143.o database/db144.o database/db145.o database/db146.o database/db147.o database/db148.o database/db149.o database/db150.o database/db151.o database/db152.o database/db153.o database/db154.o database/db155.o database/db156.o database/db157.o database/db158.o database/db159.o database/db160.o database/db161.o database/db162.o database/db163.o database/db164.o database/db165.o database/db166.o database/db167.o database/db168.o database/db169.o database/db170.o database/db171.o database/db172.o database/db173.o database/db174.o database/db175.o database/db176.o database/db177.o database/db178.o database/db179.o database/db180.o database/db181.o database/db182.o database/db183.o database/db184.o database/db185.o database/db186.o database/db187.o database/db188.o database/db189.o database/db190.o database/db191.o database/db192.o database/db193.o database/db194.o database/db195.o database/db196.o database/db197.o database/db198.o database/db199.o database/db200.o database/db201.o database/db202.o database/db203.o database/db204.o database/db205.o database/db206.o database/db207.o database/db208.o database/db209.o database/db210.o database/db211.o database/db212.o database/db213.o database/db214.o database/db215.o database/db216.o database/db217.o database/db218.o database/db219.o database/db220.o database/db221.o database/db222.o database/db223.o database/db224.o database/db225.o database/db226.o database/db227.o database/db228.o database/db229.o database/db230.o database/db231.o database/db232.o database/db233.o database/db234.o database/db235.o database/db236.o database/db237.o database/db238.o database/db239.o database/db240.o database/db241.o database/db242.o database/db243.o database/db244.o database/db245.o database/db246.o database/db247.o database/db248.o database/db249.o database/db250.o database/db251.o database/db252.o database/db253.o database/db254.o database/db255.o database/db256.o database/db257.o database/db258.o database/db259.o database/db260.o database/db261.o database/db262.o database/db263.o database/db264.o database/db265.o database/db266.o database/db267.o database/db268.o database/db269.o database/db270.o database/db271.o database/db272.o database/db273.o database/db274.o database/db275.o database/db276.o database/db277.o database/db278.o database/db279.o database/db280.o database/db281.o database/db282.o database/db283.o database/db284.o database/db285.o database/db286.o database/db287.o database/db288.o database/db289.o database/db290.o database/db291.o database/db292.o database/db293.o database/db294.o database/db295.o database/db296.o database/db297.o database/db298.o database/db299.o database/db300.o database/db301.o database/db302.o database/db303.o database/db304.o database/db305.o database/db306.o database/db307.o database/db308.o database/db309.o database/db310.o database/db311.o database/db312.o database/db313.o database/db314.o database/db315.o database/db316.o database/db317.o database/db318.o database/db319.o database/db320.o database/db321.o database/db322.o database/db323.o database/db324.o database/db325.o database/db326.o database/db327.o database/db328.o database/db329.o database/db330.o database/db331.o database/db332.o database/db333.o database/db334.o database/db335.o database/db336.o database/db337.o database/db338.o database/db339.o database/db340.o database/db341.o database/db342.o database/db343.o database/db344.o database/db345.o database/db346.o database/db347.o database/db348.o database/db349.o database/db350.o database/compiled_database.o


# Recent Changes to Database Classes
compiled_database.o: database/compiled_database.cpp database/compiled_database.h
	${COMPILER} ${CCFLAGS} -c database/compiled_database.cpp 
#database.o: mysql_database.cpp mysql_database.h
#	${COMPILER} ${CCFLAGS} -o database.o -c mysql_database.cpp
#database.o: sqlite_database.cpp sqlite_database.h
#	${COMPILER} ${CCFLAGS} -o database.o -c sqlite_database.cpp
database.o: ghost_database.cpp ghost_database.h
	${COMPILER} ${CCFLAGS} -o database.o -c ghost_database.cpp
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
time.o: time.cpp adsotime.h
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
zhen01.o: zhen01.cpp zhen01.h
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
	rm -f ./libadso.a
	rm -f adso

install:
	cp -f ./adso /bin/adso
	cp -f ./libadso.a /usr/lib/libadso.a





