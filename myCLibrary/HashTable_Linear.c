#include <stdlib.h>

#define HASH_EMPTY (1 << 31)

typedef struct {
	int key;
	int value;
} Keypair;

typedef struct {
	//int bucketload;
	int bucketbits;
	Keypair* bucket;
} Hashtable;

int tiny_hash_i32(unsigned int k, int bits) {
	return (k * 2654435769u) >> (32 - bits);
}
Hashtable* HT_new(int required_bucketsize) {
	Hashtable* ht;
	int bucketbits;
	for (bucketbits = 4; (1 << bucketbits) < required_bucketsize; bucketbits++);
	if (!(ht = calloc(1, sizeof(Hashtable)))) exit(1);
	if (!(ht->bucket = calloc(1LL << bucketbits, sizeof(Keypair)))) exit(1);
	for (int sz = 1 << bucketbits, i = 0; i < sz; i++) { ht->bucket[i].key = HASH_EMPTY; }
	ht->bucketbits = bucketbits;
	return ht;
}
void HT_delete(Hashtable* ht) {
	free(ht->bucket);
	free(ht);
}
void HT_push(Hashtable* ht, Keypair item) {
	int key = item.key, index = tiny_hash_i32(key, ht->bucketbits);
	for (int sz = 1 << ht->bucketbits; ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY) break;
		if (key2 == key) return;
	}
	ht->bucket[index] = item;
	//ht->bucketload++;
}
Keypair* HT_find(const Hashtable* ht, int key) {
	int index = tiny_hash_i32(key, ht->bucketbits);
	for (int sz = 1 << ht->bucketbits; ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY || key2 == key) return &ht->bucket[index];
	}
	return NULL;
}

int tiny_hash_str(const char str[]) {
	unsigned int h = 0;
	char ch;
	while (ch = (*str++)) { h = (h + ch) * 5381u + ch; }
	return h & (HASH_BLOCK_SIZE - 1);
}
int tiny_hash_i64(unsigned long long k, int bits) {
	return (k * 11400714819323198485llu) >> (64 - bits);
}



/*
* 2024-01-16 Tue
*
* The performance of linear probing is better than I think.
* Especially when I consider cache hits ratio.
*
* 2024-01-26 Fri
* Simple string hash func added.
*/