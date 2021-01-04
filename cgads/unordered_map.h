#ifndef CGADS_UNORDERED_MAP_H
#define CGADS_UNORDERED_MAP_H

struct cgads_unordered_map_bucket_t
{
	void* keyArray;
	void* valueArray;
	size_t bucketSize;
};

struct cgads_unordered_map_t
{
	cgads_unordered_map_bucket_t* buckets;
	size_t numBuckets;
	size_t keySize;
	size_t valueSize;
	size_t (*hashfunc)(const void* key);
	int (*key_cmpfunc);
};

void cgads_unordered_map_create(cgads_unordered_map_t* ht,size_t numBuckets,
	size_t keySize,size_t valueSize,
	size_t (*hashfunc)(const void* key),
	int (*key_cmpfunc)(const void* keya,const void* keyb));
void cgads_unordered_map_delete(cgads_unordered_map_t* ht);

void* cgads_unordered_map_find(const cgads_unordered_map_t* ht,const void* key);
void cgads_unordered_map_insert(cgads_unordered_map* ht,const void* key,const void* value);

#endif
