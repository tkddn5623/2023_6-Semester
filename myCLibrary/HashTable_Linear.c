#include <stdlib.h>

#define HASH_EMPTY (1 << 31)

typedef struct {
	int key;
	int value;
} Keypair;

typedef struct {
	Keypair* bucket;
	int bucketbits;
#ifdef AUTOMATIC_RESIZE
	int bucketload;
#endif
} Hashtable;

typedef struct {
	Keypair* bucket;
	int bucketbits;
#ifdef AUTOMATIC_RESIZE
	int bucketload;
#endif
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
Keypair* HT_find(const Hashtable* ht, int key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_i32(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY || key2 == key) return &ht->bucket[index];
	}
	return NULL;
}
#ifdef AUTOMATIC_RESIZE
void HT_resize(Hashtable* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Keypair* bucket2 = calloc(sz, sizeof(Keypair));
	for (int i = 0; i < sz; i++) {
		bucket2[i].key = HASH_EMPTY;
	}
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (ht->bucket[i].key == HASH_EMPTY) continue;
		for (int index = tiny_hash_i32(ht->bucket[i].key, bits2); ; index = (index + 1) & (sz - 1)) {
			if (bucket2[index].key == HASH_EMPTY) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
#endif
void HT_insert_or_change(Hashtable* ht, int key, int value) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_i32(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY) {
			ht->bucket[index] = (Keypair){ key,value };
#ifdef AUTOMATIC_RESIZE
			if (++ht->bucketload > sz / 2) HT_resize(ht);
#endif
			return;
		}
		if (key2 == key) { ht->bucket[index].value += value; return; }
	}
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
*
* 2024.2.12 Mon
* Resizeable hash table supported.
*/