#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10 // Taille de table de hashage

struct element {
  char* key  ;
  char* value;
  struct element* Next ;
};

struct element ** kvs;

void initialiser_kvs () { 
  kvs = malloc(sizeof(struct element *) * N);
  for (int i =0; i<N; ++i){
    kvs[i] = NULL ;
  }  
}

int hash_function(char* key){
  // Une simple fonction de hashage :
  unsigned int index = 0;
  int n = strlen(key);
  while(n--){
    index += (int)key[n];
  }
  return index % N ;
}

int kvs_get(char* key, char** out_data, size_t* data_size){
  
  const int index = hash_function(key);
  struct element * ptr = kvs[index]   ;
  struct element * ptr_prev ;
  if (ptr == NULL){
    return 0 ;
  }
  while( ptr != NULL){
    if (strcmp(ptr->key , key) == 0){
      //char * tmp_key ;
      //strcpy(tmp_key , ptr->key);
      /*char * tmp_value ;
      strcpy(tmp_value , ptr->value);
      */
      //*data_size = strlen( tmp_value );
      //printf("%s = %ld" , ptr->value , strlen(ptr->value)); !! erreur de segmentation
      *out_data = malloc(sizeof(char*) * strlen(ptr->value)) ; // !
      strcpy(*out_data , tmp_value);
      return 1 ;
    }
    ptr_prev = ptr ;
    ptr = ptr_prev -> Next ;
  }
}

int kvs_put(char* key, char * in_data, size_t data_size){
  const int index = hash_function(key);
  if ( kvs[index] == NULL ){
    printf("%s\n", "ajout sans collision");
    kvs[index] = malloc(sizeof(struct element));
    kvs[index]-> key   = malloc(strlen(key));
    kvs[index]-> value = malloc( data_size );
    //memset(kvs[index]->value , '\0' , sizeof(kvs[index]->value));
    strcpy(kvs[index]->key , key) ;
    strcpy(kvs[index]->value , in_data) ;
    //printf("%s   %ld\n" , kvs[index]->value, strlen(kvs[index]->value));
    kvs[index] -> Next  = NULL;
    return 1 ;
  }
  else {
    printf("%s\n", "ajout avec collision");
    struct element * ptr = kvs[index] ;
    struct element * ptr_prev ;
    while (ptr != NULL){
      ptr_prev = ptr ;
      ptr = ptr_prev -> Next ;
    }
    ptr_prev -> Next = malloc(sizeof(struct element));
    ptr_prev -> Next -> key   = malloc(strlen(key));
    ptr_prev -> Next -> value = malloc( data_size );
    strcpy(ptr_prev -> Next -> key , key) ;
    strcpy(ptr_prev -> Next -> value , in_data) ;
    //printf("%s   %ld\n" ,ptr_prev -> Next ->value, strlen(ptr_prev -> Next->value));
    ptr_prev->Next  -> Next = NULL ;
    return 1 ;
  }
  return 0 ;
}
void Affichage(){
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

int main(){
  initialiser_kvs() ; 

  char* c = "ab";
  //printf("%u\n", hash_function(c));
  
  // Test : kvs_put ------------------------------
  int ret = kvs_put("ab", "abcdef", 6);
  Affichage();
  printf("%d     %s\n" , ret ,"Nouvelle valeur");
  
  ret = kvs_put("ba", "xyzw", 5);
  Affichage();
  printf("%d     %s\n" , ret ,"Nouvelle valeur");
  
  ret = kvs_put("rh", "hkjhs", 6);
  Affichage();
  printf("%d     %s\n" , ret ,"Nouvelle valeur");

  // Test  : kvs_get ----------------------------

  char** out_data ;
  size_t* data_size;
  ret = kvs_get("ba" , out_data, data_size);
  printf("%d" , ret);
  printf(" %s ,  %ld\n" , *out_data, *data_size);

  ret = kvs_get("rh" , out_data, data_size);
  printf("%d" , ret);
  printf(" %s ,  %ld\n" , *out_data, *data_size);
 
  return 0;
}
