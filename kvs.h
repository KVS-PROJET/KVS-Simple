#ifndef _KVS_H_
#define _KVS_H_

#include <stdio.h>
#include <stdlib.h>

struct element {
  char* key  ;
  char* value;
  struct element* Next ;
};


struct element ** initialiser_kvs(const int N) ;
int hash_function(char* key, const int N) ;
int kvs_get(char* key, char** out_data, size_t* data_size, const int N, struct element** kvs);
int kvs_put(char* key, char* in_data, size_t data_size, const int N, struct element** kvs);
void Affichage(const int N , struct element** kvs);

#endif
