
struct hashtable_bucket_t
{
	void* keyArray;
	void* valueArray;
	size_t bucketSize;
};

struct hashtable_t
{
	hashtable_bucket_t* buckets;
	size_t numBuckets;
	size_t keySize;
	size_t valueSize;
	size_t (*hashfunc)(const void* key);
	int (*key_cmpfunc);
};

void hashtable_create(hashtable_t* ht,size_t numBuckets,
	size_t keySize,size_t valueSize,
	size_t (*hashfunc)(const void* key),
	int (*key_cmpfunc)(const void* keya,const void* keyb))
{
	ht->hashfunc=hashfunc;
	ht->key_cmpfunc=key_cmpfunc;
	ht->keySize=keySize;
	ht->valueSize=valueSize;
	ht->numBuckets=numBuckets;
	ht->buckets=(hashtable_bucket_t*)calloc(numBuckets*sizeof(hashtable_bucket_t));
}
void hashtable_delete(hashtable_t* ht)
{
	for(size_t i=0;i<ht->numBuckets;i++)
	{
		if(ht->buckets[i].bucketSize) 
		{
			free(ht->buckets[i].keyArray);
			free(ht->buckets[i].valueArray);
		}
	}
	free(ht->buckets);
}

void* hashtable_find(const hashtable_t* ht,const void* key)
{
	size_t hashvalue=ht->hashfunc(key);
	hashtable_bucket_t* bucket=ht->buckets+(hashvalue % ht->numBuckets);
	
	for(size_t i=0;i<bucket->bucketSize;i++)
	{
		const uint8_t* keyCur=((const uint8_t*)bucket->keyArray)+keySize*i;
		if(0==bucket->key_cmpfunc(keyCur,key))
		{
			return keyCur;
		}
	}
	return NULL;
}
void hashtable_insert(hashtable_t* ht,const void* key,const void* value)
{
	size_t hashvalue=ht->hashfunc(key);
	hashtable_bucket_t* bucket=ht->buckets+(hashvalue % ht->numBuckets);
	
	for(size_t i=0;i<bucket->bucketSize;i++)
	{
		if(0==bucket->key_cmpfunc(bucket->keyArray+i,key))
		{
			return bucket->keyArray+i;
		}
	}
}
