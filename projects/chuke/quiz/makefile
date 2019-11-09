CFLAGS = -Wall -fpic -coverage -lm

testme:
	gcc -o testme testme.c $(CFLAGS)
	./testme

clean:
	rm -f testme *.gcov *.gcda *.gcno *.o
