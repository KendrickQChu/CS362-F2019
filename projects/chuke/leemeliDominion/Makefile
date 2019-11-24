CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1 >> testresults.out
	./unittest2 >> testresults.out
	./unittest3 >> testresults.out
	./unittest4 >> testresults.out
	./unittest5 >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	cat dominion.c.gcov >> testresults.out

randomtest1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtest1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtest2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtest3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtest3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)

randomtestresults: randomtest1 randomtest2 randomtest3
	./randomtest1 >> testresults.out
	./randomtest2 >> testresults.out
	./randomtest3 >> testresults.out
	gcov -b -f dominion.c >> testresults.out
	cat dominion.c.gcov >> testresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unittestresults randomtestresults 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe unittest5 unittest5.exe randomtest1 randomtest1.exe randomtest2 randomtest2.exe randomtest3 randomtest3.exe
