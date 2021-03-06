#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvs.h"
#include "murmur3.h"
#include <sys/time.h>
#include <time.h> //

int main(int argc , char* argv[] ){
  
  if ( argc > 2 || argc == 0 ){
    printf("%s" , "Entrer la taille du table de hashage");
    return 0 ;
  } 
  const int N = atoi(argv[1]) ;
  initialiser_kvs(N) ; // initilise kvs with N
  
  char * key   = malloc(sizeof(char*));
  char * value = malloc(sizeof(char*));

  // arguments for kvs_get
  char* out_data = NULL;
  size_t data_size = 0 ; 

  // variables for time measuring  
  struct timeval st, et ;
  srand(time(0));

  gettimeofday(&st , NULL); // start time
  
  for (int i = 0; i<1000000; ++i){
    int a = rand() , b = rand() , aa = rand();    
    sprintf(key,   "%d" , a) ; // for kvs_put
    sprintf(value, "%d" , b) ; // ----------

    // for kvs_get
    sprintf(key, "%d", aa);

    int len = strlen(value) ;
    kvs_put(key, value, len );
    
    kvs_get(key, &out_data, &data_size);
    
  }
  
  gettimeofday(&et, NULL); // end time

  int elapsed = ( (et.tv_sec - st.tv_sec)*1000000 ) + (et.tv_usec - st.tv_usec);
  printf("Time elapsed for 1 Million put/get of random data in microsecond: %d\n" , elapsed);

  
  free_kvs();  
  return 0;
}
