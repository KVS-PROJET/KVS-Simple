all : run

run: test
	./test $(size)

test: main.o kvs.o
	gcc main.o kvs.o -o test

main.o: main.c
	gcc -c main.c

kvs.o : kvs.c kvs.h
	gcc -c kvs.c

clean :
	rm -f test
