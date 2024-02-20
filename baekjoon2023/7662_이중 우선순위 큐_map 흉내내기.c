#include <stdio.h>
#include <stdlib.h>

#define AUTOMATIC_RESIZE

typedef struct {
	int key;
	int value;
	int valid;
} Keypair;

typedef struct {
	Keypair* bucket;
	int bucketbits;
#ifdef AUTOMATIC_RESIZE
	int bucketload;
#endif
} Hashtable;

typedef struct {
	int* items;
	int size;
#ifdef AUTOMATIC_RESIZE
	int capacity;
#endif
} ArrayHeap;

int tiny_hash_i64(unsigned long long k, int bits) {
	return (k * 11400714819323198485llu) >> (64 - bits);
}
Hashtable* HT_new(int required_bucketsize) {
	Hashtable* ht;
	int bucketbits;
	for (bucketbits = 4; (1 << bucketbits) < required_bucketsize; bucketbits++);
	ht = calloc(1, sizeof(Hashtable)); if (!ht) exit(1);
	ht->bucket = calloc(1LL << bucketbits, sizeof(Keypair)); if (!ht->bucket) exit(1);
	ht->bucketbits = bucketbits;
	return ht;
}
void HT_delete(Hashtable* ht) {
	free(ht->bucket);
	free(ht);
}
Keypair* HT_find(const Hashtable* ht, int key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_i64(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		if (!ht->bucket[index].valid || ht->bucket[index].key == key) return &ht->bucket[index];
	}
	return NULL;
}
#ifdef AUTOMATIC_RESIZE
void HT_resize(Hashtable* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Keypair* bucket2 = calloc(sz, sizeof(Keypair)); if (!bucket2) exit(1);
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (!ht->bucket[i].valid) continue;
		for (int index = tiny_hash_i64(ht->bucket[i].key, bits2); ; index = (index + 1) & (sz - 1)) {
			if (!bucket2[index].valid) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
#endif
void HT_insert_or_change(Hashtable* ht, int key, int value) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_i64(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		if (!ht->bucket[index].valid) {
			ht->bucket[index] = (Keypair){ key,value,1 };
#ifdef AUTOMATIC_RESIZE
			if (++ht->bucketload > sz / 2) HT_resize(ht);
#endif
			return;
		}
		if (ht->bucket[index].key == key) { ht->bucket[index].value += value; return; }
	}
}
ArrayHeap* AH_new(int max) {
	ArrayHeap* pheap;
	pheap = calloc(1, sizeof(ArrayHeap)); if (!pheap) exit(1);
	pheap->items = calloc(max + 1, sizeof(int)); if (!pheap->items) exit(1);
#ifdef AUTOMATIC_RESIZE
	pheap->capacity = max + 1;
#endif
	return pheap;
}
void AH_delete(ArrayHeap* pheap) {
	free(pheap->items);
	free(pheap);
}
int AH_empty(ArrayHeap* pheap) {
	return pheap->size == 0;
}
int AH_top(const ArrayHeap* pheap) {
	return pheap->items[1];
}
void AH_push_min(ArrayHeap* pheap, int item) {
	int parent, child = pheap->size + 1;
	while (child > 1) {
		if (pheap->items[(parent = child / 2)] <= item) break; // Minheap
		pheap->items[child] = pheap->items[parent];
		child = parent;
	}
	pheap->items[child] = item;
	pheap->size++;
#ifdef AUTOMATIC_RESIZE
	if (pheap->size == pheap->capacity - 1) {
		pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof(int)); if (!pheap->items) exit(1);
	}
#endif
}
int AH_pop_min(ArrayHeap* pheap) {
	const int size = pheap->size;
	const int top = pheap->items[1];
	const int last = pheap->items[size];
	int child, parent = 1;
	while ((child = parent * 2) <= size) {
		if (child < size && pheap->items[child + 1] < pheap->items[child]) child++; // Minheap
		if (last <= pheap->items[child]) break; // Minheap
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->size--;
	return top;
}
void AH_push_max(ArrayHeap* pheap, int item) {
	int parent, child = pheap->size + 1;
	while (child > 1) {
		if (pheap->items[(parent = child / 2)] >= item) break; // Maxheap
		pheap->items[child] = pheap->items[parent];
		child = parent;
	}
	pheap->items[child] = item;
	pheap->size++;
#ifdef AUTOMATIC_RESIZE
	if (pheap->size == pheap->capacity - 1) {
		pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof(int)); if (!pheap->items) exit(1);
	}
#endif
}
int AH_pop_max(ArrayHeap* pheap) {
	const int size = pheap->size;
	const int top = pheap->items[1];
	const int last = pheap->items[size];
	int child, parent = 1;
	while ((child = parent * 2) <= size) {
		if (child < size && pheap->items[child + 1] > pheap->items[child]) child++; // Maxheap
		if (last >= pheap->items[child]) break; // Maxheap
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->size--;
	return top;
}
void solve7662(int Q) {
	ArrayHeap* heap[2] = { AH_new(16), AH_new(16) };
	Hashtable* ht = HT_new(16);


	for (int i = 0; i < Q; i++) {
		char op;
		int num;

		scanf(" %c%d", &op, &num);

		if (op == 'I') {
			if (HT_find(ht, num)->value == 0) {
				AH_push_min(heap[0], num);
				AH_push_max(heap[1], num);
			}
			HT_insert_or_change(ht, num, 1);
		}

		if (op == 'D') {
			int top = -1;
			if (num == -1) {
				while (!AH_empty(heap[0]) && HT_find(ht, top = AH_top(heap[0]))->value == 0) {
					AH_pop_min(heap[0]);
				}
				if (!AH_empty(heap[0])) {
					if (HT_find(ht, top)->value == 1) AH_pop_min(heap[0]);
					HT_insert_or_change(ht, top, -1);
				}
			}
			else {
				while (!AH_empty(heap[1]) && HT_find(ht, top = AH_top(heap[1]))->value == 0) {
					AH_pop_max(heap[1]);
				}
				if (!AH_empty(heap[1])) {
					if (HT_find(ht, top)->value == 1) AH_pop_max(heap[1]);
					HT_insert_or_change(ht, top, -1);
				}
			}
		}
	}

	while (!AH_empty(heap[0]) && HT_find(ht, AH_top(heap[0]))->value == 0) {
		AH_pop_min(heap[0]);
	}
	while (!AH_empty(heap[1]) && HT_find(ht, AH_top(heap[1]))->value == 0) {
		AH_pop_max(heap[1]);
	}

	if (AH_empty(heap[0])) printf("EMPTY\n");
	else printf("%d %d\n", AH_top(heap[1]), AH_top(heap[0]));

	AH_delete(heap[0]);
	AH_delete(heap[1]);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	do {
		int Q;
		scanf("%d", &Q);
		solve7662(Q);
	} while (--T > 0);
}