#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cvector.h"
#define MAXIMUM 10
#define LIM 101


void printIntVector(Vector(int) *vec){
  if(vector_valid(vec)){
    size_t i;
    printf("\nVector: {");
    for(i=0;i<vector_size(vec);i++){
      if(i!=0) printf(" ");
      printf("%d", (*vec)[i]);
    }
    printf("} // Size: %lu, Capacity: %lu\n", vector_size(vec), vector_capacity(vec));
  }
}

int main(){
  Vector(int) *vec = vector_new(int);
  int a[MAXIMUM];
  size_t i;
  srand(time(NULL));

  printf("Aux array:");
  for(i=0;i<MAXIMUM;i++)
    printf(" %d", a[i] = rand()%LIM);
  printf("\n");

  printf("\nVector(int) default initial attributes:\n"
    "Size: %lu\n"
    "Capacity: %lu\n"
    "Type size (tp_sz): %lu\n"
    "Capacity Management: %d\n"
    "Auto shrink: %d\n",
    vector_size(vec), vector_capacity(vec), vector_tp_sz(vec),
    vector_cap_man(vec),
    vector_auto_shrink(vec));

  vector_append_n(vec, a, MAXIMUM); printIntVector(vec);

  vector_erase_n(vec, 0, vector_size(vec)/2); printIntVector(vec);

  vector_set_auto_shrink(vec, 1); printIntVector(vec);

  vector_set_cap_man(vec, CVEC_CAPMAN_EQ_SZ); printIntVector(vec);

  vector_set_cap_man(vec, CVEC_CAPMAN_LOG);
  vector_insert_one(vec, 0, &(a[MAXIMUM-1])); printIntVector(vec);

  vector_erase(vec, vector_size(vec)-1); printIntVector(vec);
  
  vector_erase_n(vec, 0, vector_size(vec)-2); printIntVector(vec);

  vector_clear(vec); printIntVector(vec);

  vector_free(vec);

  return 0;
}