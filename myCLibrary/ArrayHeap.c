#include <stdlib.h>

// Version 1: Struct heap
typedef struct {
	int value1;
	int important_value;
} Nodeinfo;

typedef struct {
    Nodeinfo* items;
    int size;
} ArrayHeap;

ArrayHeap* AH_new(int max) {
    ArrayHeap* pheap;
    if (!(pheap = calloc(1, sizeof(ArrayHeap)))) exit(1);
    if (!(pheap->items = calloc(max + 1, sizeof(Nodeinfo)))) exit(1);
    return pheap;
}
void AH_delete(ArrayHeap* pheap) {
    free(pheap->items);
    free(pheap);
}
int AH_empty(ArrayHeap* pheap) {
    return pheap->size == 0;
}
void AH_push(ArrayHeap* pheap, Nodeinfo item) {
    int index = pheap->size + 1;
    while (index > 1) {
        int parentIndex = index / 2;
        if (item.important_value < pheap->items[parentIndex].important_value) {
            // Minheap
            pheap->items[index] = pheap->items[parentIndex];
            index = parentIndex;
        }
        else break;
    }
	pheap->items[index] = item;
    pheap->size++;
}
Nodeinfo AH_pop(ArrayHeap* pheap) {
    const int size = pheap->size;
	const Nodeinfo topitem = pheap->items[1];
    const Nodeinfo last = pheap->items[size];
    int left, pickedChild, parentIndex = 1;
    while ((left = parentIndex * 2) <= size) {
        if (left == size || pheap->items[left].important_value < pheap->items[left + 1].important_value) pickedChild = left;
        // Minheap
        else pickedChild = left + 1;
        if (last.important_value > pheap->items[pickedChild].important_value) {
            // Minheap
            pheap->items[parentIndex] = pheap->items[pickedChild];
            parentIndex = pickedChild;
        }
        else break;
    }
    pheap->items[parentIndex] = last;
    pheap->size--;
    return topitem;
}

// Version 2: Simple integer heap
/*
typedef struct {
    int* items;
    int size;
} ArrayHeap;

ArrayHeap* AH_new(int max) {
    ArrayHeap* pheap;
    if (!(pheap = calloc(1, sizeof(ArrayHeap)))) exit(1);
    if (!(pheap->items = calloc(max + 1, sizeof(int)))) exit(1);
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
    int index = pheap->size + 1;
    while (index > 1) {
        int parentIndex = index / 2;
        if (item < pheap->items[parentIndex]) {
            //Minheap
            pheap->items[index] = pheap->items[parentIndex];
            index = parentIndex;
        }
        else break;
    }
    pheap->items[index] = item;
    pheap->size++;
}
int AH_pop(ArrayHeap* pheap) {
    const int size = pheap->size;
    const int topitem = pheap->items[1];
    const int last = pheap->items[size];
    int left, pickedChild, parentIndex = 1;
    while ((left = parentIndex * 2) <= size) {
        if (left == size || pheap->items[left] < pheap->items[left + 1]) pickedChild = left;
        //Minheap
        else pickedChild = left + 1;
        if (last > pheap->items[pickedChild]) {
            //Minheap
            pheap->items[parentIndex] = pheap->items[pickedChild];
            parentIndex = pickedChild;
        }
        else break;
    }
    pheap->items[parentIndex] = last;
    pheap->size--;
    return topitem;
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
*/