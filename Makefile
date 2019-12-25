all :
	gcc -o test kvs_hash.c
	./test
clean :
	rm -f test
