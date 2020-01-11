#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "kvs.h"
#include "murmur3.h"

struct element** kvs = NULL ;
int taille_kvs = 0;

void initialiser_kvs (const int N) {
  taille_kvs = N;
  struct element** kvs = malloc(sizeof(struct element *) * N);
  for (int i =0; i<N; ++i){
    kvs[i] = NULL ;
  }
  //printf("%d\n" , N) ;
}


int kvs_get(char* key, char** out_data, size_t* data_size){
  
  uint32_t *index ;
  int len = strlen(key);
  uint32_t seed = 42 ;
  MurmurHash3_x86_32(key , len, seed, index);
  
  if (*index > taille_kvs)
    *index %= taille_kvs ;
  
  struct element * ptr = kvs[*index]   ;
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

int kvs_put(char* key, char * in_data, size_t data_size){
  uint32_t *index;
  int len = strlen(key);
  uint32_t seed = 42 ;
  MurmurHash3_x86_32(key , len, seed, index);

  if (*index > taille_kvs)
    *index %= taille_kvs ;

  if ( kvs[*index] == NULL ){
    printf("%s\n", "ajout sans collision");
    kvs[*index] = malloc(sizeof(struct element));
    kvs[*index] -> key   = key ;
    kvs[*index] -> value = in_data ;
    kvs[*index] -> Next  = NULL ;
    return 1 ;
  }
  else {
    printf("%s\n", "ajout avec collision");
    struct element * ptr = kvs[*index] ;
    struct element * new_ptr = malloc(sizeof(struct element*));
    //printf("%ln" , ptr);
    new_ptr->key   =  key ;
    new_ptr->value =  in_data ;
    new_ptr->Next  = ptr ;
    kvs[*index] = new_ptr ;
    return 1 ;
  }
  return 0 ;
}
void Affichage(){
  for (int i =0; i<taille_kvs; ++i){
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
