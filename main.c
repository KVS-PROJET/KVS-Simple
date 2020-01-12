#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvs.h"
#include "murmur3.h"

KVS *my_kvs = NULL ;


int main(int argc , char* argv[] ){
  printf("%s\n" , "Beginning of main ---");
  
  if ( argc > 2 || argc == 0 ){
    printf("%s" , "Entrer la taille du table de hashage");
    return 0 ;
  }
  const int N = atoi(argv[1]) ;
  //printf("%s\n" , "I'm here");
  
  int Init = initialiser_kvs(N , my_kvs) ;
  printf("%d\n" , Init);
  
  printf("%s\n" , "I'm here");
  
  
  // Test : kvs_put ------------------------------
  int ret = kvs_put("ab", "abcdef", 6 );
  //printf("%s\n" , "I'm here");
  Affichage();
  printf("%d     %s\n" , ret ,"Nouvelle valeur");
  
  ret = kvs_put("ba", "xyzw", 5);
  Affichage();
  printf("%d     %s\n" , ret ,"Nouvelle valeur");
  
  ret = kvs_put("rh", "hkjhs", 6);
  Affichage();
  printf("%d     %s\n" , ret ,"Nouvelle valeur");

  // Test  : kvs_get ----------------------------

  char* out_data   = NULL;
  size_t data_size = 0;
  
  ret = kvs_get("ba" , &out_data, &data_size);
  printf("%d\n" , ret);
  printf("%s ,  %ld\n" , out_data, data_size);
  
  ret = kvs_get("rh" , &out_data, &data_size);
  printf("%d\n" , ret);
  printf("%s ,  %ld\n" , out_data, data_size);

  free(my_kvs);
  return 0;
}
