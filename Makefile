all :
	gcc -o test kvs.c
	./test
clean :
	rm -f test
