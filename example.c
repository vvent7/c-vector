#include <stdio.h>
#include "cvector.h"

void print_return(char *op, int *a){
  if(a==NULL) printf("Not %s return\n", op);
  else printf("%s return: %d\n", op, (*a));
}

void print_dimensions(Vector(int) vec){
  VectorHeader *vh = vector_header(vec);
  printf("Size: %lu, Capacity: %lu\n\n", vh->sz, vh->cap);
}

void print_vector(Vector(int) vec){
  if(vector_empty(vec)) printf("Empty vector");

  size_t i;
  for(i=0;i<vector_size(vec);i++) printf("%d ", (*vec)[i]);
  printf("\n");
}

int main(){
  Vector(int) vec = vector_create(int);

  printf("Inserting elements:\n");
  print_return("Insert", vector_push_back(vec, 2)); print_return("Insert", vector_push_back(vec, 4));
  print_return("Insert", vector_insert(vec, 0, 1)); print_return("Insert", vector_insert(vec, 2, 3));
  print_vector(vec); print_dimensions(vec);

  printf("Clearing vector:\n"); vector_clear(vec); print_vector(vec); print_dimensions(vec);

  int arr[5] = {-1, 0, 1, 2, 3};

  printf("Inserting array [0, 1, 2, 3] at index 0:\n");
  print_return("Insert array (first el)", vector_insert_arr(vec, 0, arr + 1, 4));
  print_vector(vec); print_dimensions(vec);

  printf("Copying 2 vector elements, starting from index 1, to the penultimate position:\n");
  vector_insert_arr(vec, vector_size(vec)-1, (*vec) + 1, 2); print_vector(vec); print_dimensions(vec);

  printf("Inserting array [-1] to the end of the vector:\n");
  vector_insert_arr(vec, vector_size(vec), arr, 1); print_vector(vec); print_dimensions(vec);

  printf("Insert error tests:\n");
  if(vector_insert(vec, -1, 0)==NULL && vector_insert(vec, vector_size(vec)+1, 8)==NULL &&
    vector_insert_arr(vec, -1, arr, 1)==NULL && vector_insert_arr(vec, vector_size(vec)+1, arr, 1)==NULL)
    printf("Errors were well handled.\n\n");

  printf("Erasing last element:\n");
  vector_erase(vec, vector_size(vec)-1); print_vector(vec); print_dimensions(vec);

  printf("Erasing 2 elements starting at index 1:\n");
  vector_erase_range(vec, 1, 2); print_vector(vec); print_dimensions(vec);
  
  printf("Erasing 2 element starting at index 1:\n");
  vector_erase_range(vec, 1, 2); print_vector(vec); print_dimensions(vec);

  printf("Erasing all elements:\n");
  vector_erase_range(vec, 0, vector_size(vec)); print_vector(vec); print_dimensions(vec);
  
  return 0;
}