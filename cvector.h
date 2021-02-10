#ifndef CVECTOR_H
#define CVECTOR_H

#define _VEC_GROWTH_FACTOR 2

#ifndef MIN
  #define MIN(x, y) (x<y ? x : y) /* Returns the minimum number (x or y). */
#endif

#ifndef MAX
  #define MAX(x, y) (x>y ? x : y) /* Returns the maximum number (x or y). */
#endif

typedef unsigned char byte;

typedef struct{
  size_t sz, cap, tp_sz; /*size, capacity, type_size */
} VectorHeader;

extern size_t _vec_st;


/*----------------------------------Auxiliaries----------------------------------*/
/* Macro for Vector's type (int, double, float, boolean, etc...) */
#define Vector(type) type**

/* Verifies whether the Vector is valid */
#define vector_is_valid(vec) (vec!=NULL && (*vec)!=NULL)

/* Returns Vector's Header Address */
VectorHeader* _vector_header(Vector(void) vec);
#define vector_header(vec) (_vector_header((Vector(void)) vec))
/*==============================================================================*/

/*----------------------------------Constructor----------------------------------*/
/* Creates the vector and returns its address 
 * (pointer to array / pointer to pointer) */
Vector(void) _vector_create(size_t tp_sz);
#define vector_create(type) ((Vector(type)) _vector_create(sizeof(type)))
/*==============================================================================*/

/*-----------------------------------Pointers-----------------------------------*/
/* Returns pointer to the begin of Vector */
#define vector_begin(vec) ((*vec))

/* Returns pointer to the end of Vector */
#define vector_end(vec) ((*vec) + vector_header(vec)->sz)
/*==============================================================================*/

/*----------------------------------Dimensions----------------------------------*/
/* Returns Vector's Size */
size_t _vector_size(Vector(void) vec);
#define vector_size(vec) (_vector_size((Vector(void)) vec))

/* Returns Vector's Total Capacity */
size_t _vector_capacity(Vector(void) vec);
#define vector_capacity(vec) (_vector_capacity((Vector(void)) vec))

/* Verifies whether the Vector is empty */
#define vector_empty(vec) (vector_size(vec)==0)

/* Sets Vector's Size
 * Returns: Pointer to the beginning of Vector's array*/
void* _vector_set_size(Vector(void) vec, size_t new_size);
#define vector_set_size(vec, size) (_vector_set_size((Vector(void)) vec, size))

/* Sets Vector's Capacity
 * Returns: Pointer to the beginning of Vector's array*/
#define vector_set_capacity(vec, new_cap) (_vector_set_capacity((Vector(void)) vec,new_cap))
void* _vector_set_capacity(Vector(void) vec, size_t new_cap);
/*==============================================================================*/

/*-----------------------------------Modifiers-----------------------------------*/
/* Sets a gap with specific length starting at specific index in the vector.
 * Returns: Pointer to the beginning of gap in the array of the Vector */
void* _vector_set_gap(Vector(void) vec, size_t index, size_t length);

/* Inserts one single element inside vector at specific index
 * Returns: Pointer to element in the array of the vector */
#define vector_insert(vec, index, data)                                    \
  (                                                                        \
    (                                                                      \
      (_vector_set_gap((Vector(void)) vec, (_vec_st = index), 1))!=NULL && \
      ((*vec)[_vec_st] = data) == data                                     \
    )                                                                      \
      ? (*vec) + _vec_st                                                   \
      : NULL                                                               \
  )

/* Inserts data at Vector's end */
#define vector_push_back(vec, data) (vector_insert(vec, vector_size(vec), data))

/* Inserts array inside vector at specific index
 * Returns: Pointer to first element inserted in the vector*/
void* _vector_insert_arr(Vector(void) vec, size_t index, void *arr, int len);
#define vector_insert_arr(vec, index, arr, len)                                   \
  (                                                                               \
    ((_vector_insert_arr((Vector(void)) vec, (_vec_st = index), arr, len))!=NULL) \
      ? ((*vec) + _vec_st)                                                        \
      : NULL                                                                      \
  )

/* Removes a specific quantity of elements starting at a specific index from vector
 * Returns: A pointer to the new location of the element that followed the last element erased by the function call. This is the vector end if the operation erased the last element in the sequence. */
void* _vector_erase_range(Vector(void) vec, size_t index, size_t len);
#define vector_erase_range(vec, index, len) (_vector_erase_range((Vector(void)) vec, index, len))

/* Removes a single element from vector at specific index
 * Returns: A pointer to the new location of the element that followed the element erased by the function call. This is the vector end if the operation erased the last element.*/
#define vector_erase(vec, index) (_vector_erase_range((Vector(void)) vec, index, 1))

/* Clears Vector's content */
#define vector_clear(vec) (vector_set_capacity(vec, 0))

/* Frees all memory associated with the vector */
void _vector_free(Vector(void) vec);
#define vector_free(vec) (_vector_free((Vector(void)) vec))

#endif