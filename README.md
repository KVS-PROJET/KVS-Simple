# KVS-Simple
Table de hashage faite avec murmurhash3 x64 128bits
void MurmurHash3_x64_128(const void *key, int len, uint32_t seed, void *out);

	===================================================================
  Makefile Modified:

#declare the variable 
CC=gcc
CFLAGS=-c -Wall

all : execu

execu: main.o kvs.o murmur3.o
	$(CC) main.o kvs.o murmur3.o -o execu

shared : murmur3.c murmur3.h
	$(CC) $(CFLAGS) murmur3.c
	$(CC) -shared -Wl, --export-dynamic murmur3.o -o libmurmur3.so
main.o: main.c
	$(CC) $(CFLAGS) main.c

kvs.o : kvs.c kvs.h
	$(CC) $(CFLAGS) kvs.c

clean :
	rm -f execu
	
	==================================================================

==> fichier executable : tapez make all
			
	====> le fichier "execu" sera le fichier executable ! 
