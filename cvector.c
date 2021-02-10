#include <stdlib.h>
#include <string.h>
#include "cvector.h"

size_t _vec_st;

VectorHeader* _vector_header(Vector(void) vec){
  return vector_is_valid(vec) ? ((VectorHeader*)(*vec))-1 : NULL;
}

Vector(void) _vector_create(size_t tp_sz, ushort auto_shrink){
  VectorHeader *vh = (VectorHeader*) malloc(sizeof(VectorHeader));
  vh->sz = vh->cap = 0;
  vh->tp_sz = tp_sz;
  vh->auto_shrink = auto_shrink ? 1 : 0;

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
      vh->sz = new_size;
    }
    vh->sz = new_size;
    if(new_size < vh->cap && vh->auto_shrink)
      vh = ((VectorHeader*) _shrink_to_fit(vec)) - 1;
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

  return (*vec);
}

void* _shrink_to_fit(Vector(void) vec){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL) return NULL;

  size_t new_cap = vh->cap/2;
  while(vh->sz < new_cap) new_cap /= _VEC_GROWTH_FACTOR;
  return _vector_set_capacity(vec, new_cap*_VEC_GROWTH_FACTOR);
}

void* _vector_set_gap(Vector(void) vec, size_t index, size_t len){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL || index>vh->sz) return NULL;

  size_t sz_left = index * vh->tp_sz, sz_right = (vh->sz - index) * vh->tp_sz,
    sz_block = len * vh->tp_sz;

  _vector_set_size(vec, vh->sz+len);

  byte *begin = (byte *) (*vec) + sz_left, *end = begin + sz_block;

  memmove(end, begin, sz_right);

  return (void*) begin;
}

void* _vector_insert_arr(Vector(void) vec, size_t index, void *arr, size_t len){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL || index>vh->sz) return NULL;
  size_t sz_block = len * vh->tp_sz;
  void *temp = malloc(sz_block); memcpy(temp, arr, sz_block);
  void *dest = _vector_set_gap(vec, index, len); memcpy(dest, temp, sz_block);
  free(temp);

  return dest;
}

void* _vector_erase_range(Vector(void) vec, size_t index, size_t len){
  VectorHeader *vh = _vector_header(vec);

  if(vh==NULL || index>=vh->sz) return NULL;

  len = MIN(len, vh->sz-index);

  Vector(byte) bv = (Vector(byte)) vec;
  size_t sz_left = index * vh->tp_sz, sz_right = (vh->sz - index - len) * vh->tp_sz,
    sz_block = len * vh->tp_sz;
  byte *begin = (*bv) + sz_left, *end = begin + sz_block;

  memmove(begin, end, sz_right); _vector_set_size(vec, vh->sz-len);

  return (void*) ((*bv) + sz_left);
}

void _vector_free(Vector(void) vec){
  free(_vector_header(vec)); free(vec);
}