#include <stdio.h>
#include "cvector.h"

void print_result(int *a){
  if(a==NULL) printf("Not inserted\n");
  else printf("Inserted: %d\n", (*a));
}

void print_dimensions(Vector(int) vec){
  VectorHeader *vh = vector_header(vec);
  printf("Size: %lu, Capacity: %lu\n\n", vh->sz, vh->cap);
}

void print_vector(Vector(int) vec){
  if(vector_empty(vec)) printf("Empty vector");
  else printf("Non-empty Vector:\n");

  size_t i;
  for(i=0;i<vector_size(vec);i++) printf("%d ", (*vec)[i]);
  printf("\n");
}

int main(){
  Vector(int) vec = vector_create(int);

  print_vector(vec); print_dimensions(vec);
  print_result(vector_push_back(vec, 2)); print_vector(vec); print_dimensions(vec);
  print_result(vector_push_back(vec, 4)); print_vector(vec); print_dimensions(vec);
  print_result(vector_push_back(vec, 5)); print_vector(vec); print_dimensions(vec);
  print_result(vector_insert(vec, 0, 1)); print_vector(vec); print_dimensions(vec);
  print_result(vector_insert(vec, 2, 3)); print_vector(vec); print_dimensions(vec);
  print_result(vector_push_back(vec, 6)); print_vector(vec); print_dimensions(vec);
  print_result(vector_insert(vec, 6, 7)); print_vector(vec); print_dimensions(vec);

  print_result(vector_insert(vec, -1, 0)); print_result(vector_insert(vec, 8, 8));
  print_vector(vec); print_dimensions(vec);
  
  return 0;
}