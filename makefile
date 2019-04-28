all: utest

utest: test.o searcher.o
	g++ test.o searcher.o -o utest

test.o: test.cpp
	gcc -c test.cpp -o test.o

searcher.o: searcher.cpp
	gcc -c searcher.cpp -o searcher.o

clean: rm -r *.o utest