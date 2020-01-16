#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "kvs.h"
#include "murmur3.h"

uint32_t taille_kvs = 0;

KVS kvs = NULL ;

void insert_key_value(struct element* kvs, char* key, char* in_data, struct element* _next){
      kvs -> key   = key ;
      kvs -> value = in_data ;
      kvs -> Next  = _next ;
}


void initialiser_kvs (const int N) {
  printf("%s\n" , "Initialisation");
  taille_kvs = N;
  kvs = malloc(sizeof(struct element *) * N);
  for (int i =0; i<N; ++i){
    kvs[i] = NULL ;
  }
}


int kvs_get(char* key, char** out_data, size_t* data_size){
  
  uint32_t index = 0;
  int len = strlen(key);
  uint32_t seed = 42 ;
  MurmurHash3_x86_32(key , len, seed, &index);
  
  if (index > taille_kvs)
    index %= taille_kvs ;
  
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



int kvs_put(char* key, char * in_data, size_t data_size){
  uint32_t index = 0;
  int len = strlen(key);
  uint32_t seed = 42 ;
  MurmurHash3_x86_32(key , len, seed, &index);

  if (index > taille_kvs)
    index %= taille_kvs ;

  if ( kvs[index] == NULL ){
    printf("%s\n", "ajout sans collision");
    kvs[index] = malloc(sizeof(struct element));
    insert_key_value(kvs[index] , key, in_data, NULL);
    return 1 ;
  }
  else {
    while(kvs[index] != NULL){
      if (strcmp(kvs[index]->key , key) == 0)
	kvs[index]-> value = in_data ;
      return 1 ;
    }
    
    printf("%s\n", "ajout avec collision");
    struct element * ptr = kvs[index] ;
    struct element * new_ptr = malloc(sizeof(struct element*));
    //printf("%ln" , ptr);
    insert_key_value(new_ptr , key, in_data, ptr) ;
    kvs[index] = new_ptr ;
    return 1 ;
  }
  return 0 ;
}

void Affichage(){
  
  for (uint32_t i =0; i<taille_kvs; ++i){
    if (kvs[i] == NULL)
      continue;
    printf("kvs[%d] = %s : %s   | ", i, (kvs[i])->key, (kvs[i])->value);
    struct element* ptr = (kvs[i])->Next;
    //printf("%p", ptr);
    //printf("%s : %s", ptr->key, ptr->value);
    while (ptr != NULL){
      printf( "%s : %s   |", ptr->key, ptr->value );
      ptr = ptr->Next;
    }
    printf("\n");
  }
}

void free_kvs(){
  free(kvs);
}
