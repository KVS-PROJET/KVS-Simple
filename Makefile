all : run

run: test
	./test $(size)

test: main.o kvs.o murmur3.o
	gcc main.o kvs.o murmur3.o -o test

shared : murmur3.c murmur3.h
	gcc -c murmur3.c
	gcc -shared -Wl, --export-dynamic murmur3.o -o libmurmur3.so
main.o: main.c
	gcc -c main.c

kvs.o : kvs.c kvs.h
	gcc -c kvs.c

clean :
	rm -f test
