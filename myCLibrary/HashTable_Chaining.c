#include <stdlib.h>

#define HASH_MSB_BITS (17)
#define HASH_BLOCK_SIZE (1 << HASH_MSB_BITS)
int tiny_hash_i32(unsigned int k) {
	return (k * 2654435769u) >> (32 - HASH_MSB_BITS);
}
int tiny_hash_i64(unsigned long long k) {
	return (k * 11400714819323198485llu) >> (64 - HASH_MSB_BITS);
}
#define HASH_BLOCK_SIZE (1 << 17)
int tiny_hash_str(const char str[]) {
	unsigned int h = 0;
	char ch;
	while (ch = (*str++)) {
		h = (h + ch) * 5381u + ch;
	}
	return h & (HASH_BLOCK_SIZE - 1);
}

typedef int Element;

typedef struct _HNode {
	Element item;
	struct _HNode* next;
} HNode;

typedef struct {
	int blocksize;
	int nodesize;
	int nodecount;
	HNode** tails;
	HNode* _edges;
} Hashtable;

Hashtable* HT_new(int blocksize, int nodesize) {
	Hashtable* table;
	if (!(table = malloc(sizeof(Hashtable)))) exit(1);
	if (!(table->tails = calloc(blocksize, sizeof(HNode*)))) exit(1);
	if (!(table->_edges = calloc(nodesize + blocksize, sizeof(HNode)))) exit(1);
	table->blocksize = blocksize;
	table->nodesize = nodesize + blocksize;
	table->nodecount = blocksize;
	for (int i = 0; i < blocksize; i++) {
		table->tails[i] = &table->_edges[i];
		table->tails[i]->next = table->tails[i];
	}
	return table;
}
void HT_delete(Hashtable* table) {
	free(table->_edges);
	free(table->tails);
	free(table);
}
void HT_push(Hashtable* table, Element item) {
	int index = tiny_hash_i32(item);
	table->_edges[table->nodecount].item = item;
	table->_edges[table->nodecount].next = table->tails[index]->next;
	table->tails[index]->next = &table->_edges[table->nodecount];
	table->tails[index] = &table->_edges[table->nodecount++];
}
int HT_search(const Hashtable* table, Element item) {
	int index = tiny_hash_i32(item);
	HNode* head = &table->_edges[index];
	for (HNode* cur = head->next; cur != head; cur = cur->next) {
		if (cur->item == item) return 1;
	}
	return 0;
}

/*
* 2023.2.1 
* Hashtable
*
* 2023.2.1 
* And Simple STATIC hashing function.
*
* 2024.1.20 
* Trivial change: modular to bitwise and
*/

/*
HNode* const head = table->tails[index]->next; //Slower.
HNode* const head = &table->_edges[index];     //Faster.
*/