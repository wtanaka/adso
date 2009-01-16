#
# Demonstration of Compilation Using Adso as a Library
#
COMPILER = g++ 
#
#
#
# 32-bitUbuntu has problems running an application linked to 
# the compiled version that links to SQLite.
#
#
CCFLAGS = -I../
CCLIBS  = -ladso -lsqlite3  -L/usr/lib/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lc -lnss_files -lnss_dns -lresolv -lc -lnss_files -lnss_dns -lresolv

#
#
adso: main.o
	${COMPILER} -o adso main.o ${CCLIBS}

main.o: main.cpp
	${COMPILER} ${CCFLAGS} -c main.cpp 



clean:
	rm *.o
	rm adso

