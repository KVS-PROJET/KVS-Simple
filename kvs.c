#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "kvs.h"
#include "murmur3.h"

struct element** initialiser_kvs (const int N) { 
  struct element** kvs = malloc(sizeof(struct element *) * N);
  for (int i =0; i<N; ++i){
    kvs[i] = NULL ;
  }
  printf("%d\n" , N) ;
  return kvs ;
}


int kvs_get(char* key, char** out_data, size_t* data_size , const int N , struct element** kvs){
  
  uint32_t hash[4];
  uint32_t seed = 42 ;
  MurmurHash3_x64_128(key , strlen(key), seed, hash);
  int32_t index = hash[0] ;
  struct element * ptr = kvs[index]   ;
  struct element * ptr_prev ;
  if (ptr == NULL){
    return 0 ;
  }
  while( ptr != NULL){
    if (strcmp(ptr->key , key) == 0){
       *out_data = ptr->value;
      *data_size  =  strlen(*out_data);
      //printf("%ld\n" , *data_size);
      return 1 ;
    }
    ptr_prev = ptr ;
    ptr = ptr_prev -> Next ;
  }
}

int kvs_put(char* key, char * in_data, size_t data_size , const int N, struct element** kvs){
  uint32_t hash[4];
  uint32_t seed = 42 ;
  MurmurHash3_x64_128(key , strlen(key), seed, hash);
  int32_t index = hash[0] ;
  if ( kvs[index] == NULL ){
    printf("%s\n", "ajout sans collision");
    kvs[index] = malloc(sizeof(struct element));
    kvs[index] -> key   = key ;
    kvs[index] -> value = in_data ;
    kvs[index] -> Next  = NULL ;
    return 1 ;
  }
  else {
    printf("%s\n", "ajout avec collision");
    struct element * ptr = kvs[index] ;
    struct element * new_ptr = malloc(sizeof(struct element*));
    //printf("%ln" , ptr);
    new_ptr->key   =  key ;
    new_ptr->value =  in_data ;
    new_ptr->Next  = ptr ;
    kvs[index] = new_ptr ;
    return 1 ;
  }
  return 0 ;
}
void Affichage(const int N, struct element ** kvs){
  for (int i =0; i<N; ++i){
    if (kvs[i] == NULL)
      continue;
    printf("kvs[%d] = %s : %s   | ", i, kvs[i]->key, kvs[i]->value);
    struct element* ptr = kvs[i]->Next;
    //printf("%p", ptr);
    //printf("%s : %s", ptr->key, ptr->value);
    while (ptr != NULL){
      printf( "%s : %s   |", ptr->key, ptr->value );
      ptr = ptr->Next;
    }
    printf("\n");
  }
}
