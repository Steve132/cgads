#include "vector.h"
#include<stdint.h>
#include<string.h>

static size_t npot(size_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	if(sizeof(size_t) > 4)
	{
		v|=v >> 32;
	}
	v++;
	return v;
}

cgads_vector_t cgads_vector_create(size_t element_size,size_t size)
{
	cgads_vector_t vec;
	vec.size=size;
	vec.capacity=npot(size);
	vec.element_size=element_size;
	vec.delete_func=0;
	vec.move_func=0;

	if(vec.capacity==0) vec.capacity=8;
	vec.data=malloc(vec.capacity*element_size);
	return vec;
}

void cgads_vector_destroy(cgads_vector_t* self)
{
	cgads_vector_clear(self);
	free(self->data);
}

void cgads_vector_clear(cgads_vector_t* self)
{
	if(self->delete_func) 
	{
		uint8_t* first=(uint8_t*)self->data;
		for(size_t i=0;i<self->size;i++)
		{
			self->delete_func(first);
			first+=self->element_size;
		}
	}
	self->size=0;
}

void cgads_vector_reserve(cgads_vector_t* self,size_t new_cap)
{
	new_cap=npot(new_cap);
	if(self->capacity < new_cap)
	{
		self->capacity=new_cap;
		if(self->move_func)
		{
			void* olddata=self->data;
			self->data=malloc(self->capacity*self->element_size);
			uint8_t* first_dst=self->data;
			uint8_t* first_src=olddata;
			for(size_t i=0;i<self->size;i++)
			{
				self->move_func(first_dst,first_src);
				first_dst+=self->element_size;
				first_src+=self->element_size;
			}
		}
		else
		{
			self->data=realloc(self->data,self->capacity*self->element_size);
		}
	}
}

void cgads_vector_pop_back(cgads_vector_t* self)
{
	if(self->size == 0) return;
	if(self->delete_func)
	{
		uint8_t* end=(uint8_t*)self->data;
		end+=(self->size-1)*self->element_size;
		self->delete_func(end);
	}
	self->size--;
}
void cgads_vector_push_back(cgads_vector_t* self, const void* elem,size_t num_elem,size_t elem_size,cgads_copy_func_t copy_func)
{
	cgads_vector_reserve(self,self->size+num_elem);
	uint8_t* first_dst=(uint8_t*)self->data;
	first_dst+=self->size*self->element_size;
	uint8_t* first_src=(uint8_t*)elem;
	if(copy_func)
	{
		for(size_t i=0;i<num_elem;i++)
		{
			copy_func(first_dst,first_src);
			first_dst+=self->element_size;
			first_src+=elem_size;
		}
	}
	else
	{
		memcpy(first_dst,first_src,self->element_size*num_elem);
	}
}
