#ifndef CGADS_BASIC_TYPE_OPERATIONS_H
#define CGADS_BASIC_TYPE_OPERATIONS_H



typedef void (*cgads_copy_func_t)(void* dst,const void* src);
typedef void (*cgads_move_func_t)(void* dst,const void* src);
typedef void (*cgads_delete_func_t)(void* dst);
typedef int (*cgads_compare_func_t)(const void* dst,const void* src);

/*struct cgads_basic_operations_t
{
	cgads_copy_func_t copy_func;
	cgads_delete_func_t delete_func;
	
};*/

/*void cgads_basic_operations_create(cgads_basic_operations_t* ops);
*/

#endif
