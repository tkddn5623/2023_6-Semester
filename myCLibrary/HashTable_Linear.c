#include <stdlib.h>

#define HASH_MSB_BITS (20)
#define HASH_BLOCK_SIZE (1 << HASH_MSB_BITS)

typedef struct {
	int idx;
	int count;
} Countpair;

typedef struct {
	int bucketsize;
	//int bucketload;
	Countpair* bucket;
} Hashtable;

int tiny_hash_i32(unsigned int k) {
	return (k * 2654435769u) >> (32 - HASH_MSB_BITS);
}
Hashtable* HT_new(int required_bucketsize) {
	Hashtable* ht;
	int bucketsize;
	for (int i = 4; (bucketsize = 1 << i) < required_bucketsize; i++);
	if (!(ht = calloc(1, sizeof(Hashtable)))) exit(1);
	if (!(ht->bucket = calloc(bucketsize, sizeof(Countpair)))) exit(1);
	for (int i = 0; i < bucketsize; i++) { ht->bucket[i].idx = 1 << 31; }
	ht->bucketsize = bucketsize;
	return ht;
}
void HT_delete(Hashtable* ht) {
	free(ht->bucket);
	free(ht);
}
void HT_push(Hashtable* ht, Countpair item) {
	int key = item.idx, index = tiny_hash_i32(key);
	for (int sz = ht->bucketsize; ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].idx;
		if (key2 == 1 << 31) break;
		if (key2 == key) return;
	}
	ht->bucket[index] = item;
	//ht->bucketload++;
}
Countpair* HT_find(const Hashtable* ht, int key) {
	int index = tiny_hash_i32(key);
	for (int sz = ht->bucketsize; ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].idx;
		if (key2 == 1 << 31 || key2 == key) return &ht->bucket[index];
	}
	return NULL;
}



int tiny_hash_i64(unsigned long long k) {
	return (k * 11400714819323198485llu) >> (64 - HASH_MSB_BITS);
}

/*
* 2024-01-16 Tue
*
* The performance of linear probing is better than I think.
* Especially when I consider cache hits ratio.
*/