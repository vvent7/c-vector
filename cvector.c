#include <stdlib.h>
#include <string.h>
#include "cvector.h"

size_t _vec_st;

VectorHeader* _vector_header(Vector(void) vec){
  return vector_is_valid(vec) ? ((VectorHeader*)(*vec))-1 : NULL;
}

Vector(void) _vector_create(size_t tp_sz){
  VectorHeader *vh = (VectorHeader*) malloc(sizeof(VectorHeader));
  vh->sz = vh->cap = 0;
  vh->tp_sz = tp_sz;

  Vector(void) vec = (Vector(void)) malloc(sizeof(void*));
  *vec = (void*) (vh+1);

  return vec;
}

size_t _vector_size(Vector(void) vec){
  VectorHeader *vh = _vector_header(vec);
  if(vh==NULL) return (size_t)0;
  return vh->sz;
}

size_t _vector_capacity(Vector(void) vec){
  VectorHeader *vh = _vector_header(vec);
  if(vh==NULL) return (size_t)0;
  return vh->cap;
}

void* _vector_set_size(Vector(void) vec, size_t new_size){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL) return NULL;
  
  if(new_size!=vh->sz){
    if(new_size > vh->cap){
      size_t new_cap = MAX(vh->cap, 1);
      while(new_size > new_cap) new_cap *= _VEC_GROWTH_FACTOR;
      vh = ((VectorHeader*) _vector_set_capacity(vec, new_cap)) - 1;
    }
    vh->sz = new_size;
  }

  return (void*) (vh+1);
}

void* _vector_set_capacity(Vector(void) vec, size_t new_cap){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL) return NULL;

  if(new_cap!=vh->cap){
    vh = realloc(vh, sizeof(VectorHeader) + vh->tp_sz * new_cap);
    vh->cap = new_cap; vh->sz = MIN(vh->cap, vh->sz);
    (*vec) = (void*) (vh+1);
  }

  return (void*) (vh+1);
}

void* _vector_set_gap(Vector(void) vec, size_t index, size_t length){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL || index>vh->sz) return NULL;

  vh = ((VectorHeader*) _vector_set_size(vec, vh->sz+length)) - 1;
  byte *a = (byte*) (*vec);

  memmove(a + (index+length) * vh->tp_sz,
    a + index * vh->tp_sz,
    (vh->sz - length - index) * vh->tp_sz);

  return (void*) (a + index*vh->tp_sz);
}

void* _vector_insert_arr(Vector(void) vec, size_t index, void *arr, int qt){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL || index>vh->sz) return NULL;

  size_t block_size = qt * vh->tp_sz;
  void *temp = malloc(block_size); memcpy(temp, arr, block_size);

  _vector_set_gap(vec, index, qt); vh = _vector_header(vec);

  void *dest = (byte*) (*vec) + index * vh->tp_sz;
  memcpy(dest, temp, block_size);
  free(temp);

  return dest;
}

void _vector_free(Vector(void) vec){
  free(_vector_header(vec)); free(vec);
}