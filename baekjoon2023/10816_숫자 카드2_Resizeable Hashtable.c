#include <stdio.h>
#include <stdlib.h>

#define AUTOMATIC_RESIZE
#define MAXN       (500000)
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
	int index = tiny_hash_i32(key, ht->bucketbits);
	for (int sz = 1 << ht->bucketbits; ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY || key2 == key) return &ht->bucket[index];
	}
	return NULL;
}
#ifdef AUTOMATIC_RESIZE
void HT_resize(Hashtable* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Keypair* bucket2 = calloc(sz, sizeof(Keypair)); if (!bucket2) exit(1);
	for (int i = 0; i < sz; i++) {
		bucket2[i].key = HASH_EMPTY;
	}
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (ht->bucket[i].key == HASH_EMPTY) continue;
		int index = tiny_hash_i32(ht->bucket[i].key, bits2);
		for (; ; index = (index + 1) & (sz - 1)) {
			if (bucket2[index].key == HASH_EMPTY) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
#endif
void HT_insert_or_change(Hashtable* ht, int key, int value) {
	int index = tiny_hash_i32(key, ht->bucketbits);
	for (int sz = 1 << ht->bucketbits; ; index = (index + 1) & (sz - 1)) {
		int key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY) {
			ht->bucket[index].key = key;
			ht->bucket[index].value = value;
#ifdef AUTOMATIC_RESIZE
			if (++ht->bucketload > sz / 2) HT_resize(ht);
#endif
			return;
		}
		if (key2 == key) { ht->bucket[index].value += value; return; }
	}
}
int main() {
	//freopen("i.txt", "r", stdin);
	int N, M;

	scanf("%d", &N);

	Hashtable* ht = HT_new(1024);

	for (int i = 0; i < N; i++) {
		int temp;
		scanf("%d", &temp);
		HT_insert_or_change(ht, temp, 1);
	}

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int temp;
		scanf("%d", &temp);
		printf("%d ", HT_find(ht, temp)->value);
	}

	HT_delete(ht);
}
