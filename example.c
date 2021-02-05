#include <stdio.h>
#include "cvector.h"

void print_dimensions(Vector(int) vec){
  VectorHeader *vh = vector_header(vec);
  printf("Size: %lu, Capacity: %lu\n\n", vh->size, vh->capacity);
}

void print_vector(Vector(int) vec){
  if(vector_empty(vec)) printf("Empty vector");
  else printf("Non-empty Vector:\n");

  size_t i;
  for(i=0;i<vector_size(vec);i++) printf("%d ", (*vec)[i]);
  printf("\n\n");
}

int main(){
  Vector(int) vec = (Vector(int)) vector_create();

  print_dimensions(vec);
  printf("First push back:\n");
  vector_push_back(vec, 5); print_dimensions(vec);

  //WRONG INSERTS (Won't be inserted)
  vector_insert(vec, -1, 99);
  vector_insert(vec, 2, 99);
  printf("After Wrong inserts:\n");
  print_dimensions(vec);
  //======

  printf("Inserts and pushes:\n");
  vector_push_back(vec, 10); print_dimensions(vec);
  vector_insert(vec, 0, -10); print_dimensions(vec);
  vector_insert(vec, 1, -5); print_dimensions(vec);
  vector_insert(vec, 2, 0); print_dimensions(vec);

  printf("Result:\n");
  print_vector(vec);

  vector_clear(vec);

  printf("After clear:\n");
  print_vector(vec);
  
  return 0;
}