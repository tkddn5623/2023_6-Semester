#include <stdlib.h>

// Version 1: Basic heap

typedef int Element;

typedef struct {
    Element item;
    int priority;
} HNode;

typedef struct {
    HNode* nodes;
    int size;
} ArrayHeap;

ArrayHeap* AH_new(int max) {
    ArrayHeap* pheap;
    if (!(pheap = calloc(1, sizeof(ArrayHeap)))) exit(1);
    if (!(pheap->nodes = calloc(max + 1, sizeof(HNode)))) exit(1);
    return pheap;
}
void AH_delete(ArrayHeap* pheap) {
    free(pheap->nodes);
    free(pheap);
}
int AH_isEmpty(ArrayHeap* pheap) {
    return pheap->size == 0;
}
void AH_push(ArrayHeap* pheap, Element item, int priority) {
    HNode newNode;
    int index = pheap->size + 1;
    while (index > 1) {
        int parentIndex = index / 2;
        if (priority < pheap->nodes[parentIndex].priority) {
            // Minheap
            pheap->nodes[index] = pheap->nodes[parentIndex];
            index = parentIndex;
        }
        else break;
    }
    newNode.item = item;
    newNode.priority = priority;
    pheap->nodes[index] = newNode;
    pheap->size++;
}
Element AH_pop(ArrayHeap* pheap) {
    const int size = pheap->size;
    const Element topitem = pheap->nodes[1].item;
    const HNode last = pheap->nodes[size];
    int left, pickedChild, parentIndex = 1;
    while ((left = parentIndex * 2) <= size) {
        if (left == size || pheap->nodes[left].priority < pheap->nodes[left + 1].priority) pickedChild = left;
        // Minheap
        else pickedChild = left + 1;
        if (last.priority > pheap->nodes[pickedChild].priority) {
            // Minheap
            pheap->nodes[parentIndex] = pheap->nodes[pickedChild];
            parentIndex = pickedChild;
        }
        else break;
    }
    pheap->nodes[parentIndex] = last;
    pheap->size--;
    return topitem;
}
void AH_heapSort(Element* Base, int NumOfElement) {
    ArrayHeap* heap = AH_new(NumOfElement);
    for (int i = 0; i < NumOfElement; i++)
        AH_push(heap, Base[i], Base[i]);
    for (int i = 0; i < NumOfElement; i++)
        Base[i] = AH_pop(heap);
    AH_delete(heap);
}

/*
Below are only for isFull.

int capacity;
pheap->capacity = max + 1;

int AH_isFull(ArrayHeap* pheap) {
    return pheap->size == pheap->capacity - 1;
}
*/


/*
* 2022.7.27 Wed
* 2023.7.18 Tue: Delete unnecessary code
* 2024.1.4  Thu: legacy code
*/