#ifndef CGADS_VECTOR_H
#define CGADS_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include<stdlib.h>
#include<stddef.h>

#include "basic_type_operations.h"

typedef struct 
{
	size_t size;
	size_t element_size;
	size_t capacity;
	void* data;
	
	cgads_copy_func_t move_func;
	cgads_delete_func_t delete_func;
} cgads_vector_t;

cgads_vector_t cgads_vector_create(size_t element_size,size_t size);
void cgads_vector_push_back(cgads_vector_t* self, const void* elem,size_t num_elem,size_t elem_size,cgads_copy_func_t copy_func);
void cgads_vector_pop_back(cgads_vector_t* self);
void cgads_vector_clear(cgads_vector_t* self);
void cgads_vector_reserve(cgads_vector_t* self,size_t new_capacity);
void cgads_vector_destroy(cgads_vector_t* self);

#ifdef __cplusplus
}
#endif


#endif
