#include <stdlib.h>

// Version 1: Struct heap
typedef struct {
	int value;
	int priority;
} HNode;

typedef struct {
	HNode* items;
	int size;
#ifdef AUTOMATIC_RESIZE
	int capacity;
#endif
} ArrayHeap;

ArrayHeap* AH_new(int max) {
	ArrayHeap* pheap;
	pheap = calloc(1, sizeof(ArrayHeap)); if (!pheap) exit(1);
	pheap->items = calloc(max + 1, sizeof(HNode)); if (!pheap->items) exit(1);
#ifdef AUTOMATIC_RESIZE
	pheap->capacity = max + 1;
#endif
	return pheap;
}
void AH_delete(ArrayHeap* pheap) {
	free(pheap->items);
	free(pheap);
}
int AH_empty(const ArrayHeap* pheap) {
	return pheap->size == 0;
}
void AH_push(ArrayHeap* pheap, HNode item) {
#ifdef AUTOMATIC_RESIZE
	if (pheap->size == pheap->capacity - 1) {
		pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof(HNode));
	}
#endif
	int parent, child = pheap->size + 1;
	while (child > 1) {
		if (pheap->items[(parent = child / 2)].priority <= item.priority) break; // Minheap
		pheap->items[child] = pheap->items[parent];
		child = parent;
	}
	pheap->items[child] = item;
	pheap->size++;
}
HNode AH_pop(ArrayHeap* pheap) {
	const int size = pheap->size;
	const HNode top = pheap->items[1];
	const HNode last = pheap->items[size];
	int child, parent = 1;
	while ((child = parent * 2) <= size) {
		if (child < size && pheap->items[child + 1].priority < pheap->items[child].priority) child++; // Minheap
		if (last.priority <= pheap->items[child].priority) break; // Minheap
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->size--;
	return top;
}

// Version 2: Simple integer heap
/*
typedef struct {
    int* items;
    int size;
#ifdef AUTOMATIC_RESIZE
	int capacity;
#endif
} ArrayHeap;

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
void AH_push(ArrayHeap* pheap, int item) {
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
		pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof(int));
	}
#endif
}
int AH_pop(ArrayHeap* pheap) {
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
*/



/*
Below are only for isFull.

int capacity;
pheap->capacity = max + 1;

int AH_isFull(ArrayHeap* pheap) {
    return pheap->size == pheap->capacity - 1;
}
*/


/*
* 2024-01-04: Modify to cleaner code
* 2024.02.02: Unnecessary variables deleted
* 2024.02.10: Automatic resize support
*/