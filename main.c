#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvs.h"




int main(int argc , char* argv[] ){
  // kvs 4000 : argc = 2, argv[0] = kvs, argv[1] = 4000
  if ( argc > 2 || argc == 0 ){
    printf("%s" , "Entrer la taille du table de hashage");
    return 0 ;
  }
  const int N = atoi(argv[1]) ;
  struct element** kvs = initialiser_kvs(N) ; 

  char* c = "ab";
  //printf("%u\n", hash_function(c));
  
  // Test : kvs_put ------------------------------
  int ret = kvs_put("ab", "abcdef", 6 , N, kvs);
  Affichage(N , kvs);
  printf("%d     %s\n" , ret ,"Nouvelle valeur");
  
  ret = kvs_put("ba", "xyzw", 5 , N, kvs);
  Affichage(N, kvs);
  printf("%d     %s\n" , ret ,"Nouvelle valeur");
  
  ret = kvs_put("rh", "hkjhs", 6 , N, kvs);
  Affichage(N, kvs);
  printf("%d     %s\n" , ret ,"Nouvelle valeur");

  // Test  : kvs_get ----------------------------

  char* out_data   = NULL;
  size_t data_size = 0;
  
  ret = kvs_get("ba" , &out_data, &data_size , N, kvs);
  printf("%d\n" , ret);
  printf("%s ,  %ld\n" , out_data, data_size);
  
  ret = kvs_get("rh" , &out_data, &data_size , N, kvs);
  printf("%d\n" , ret);
  printf("%s ,  %ld\n" , out_data, data_size);
  
  return 0;
}