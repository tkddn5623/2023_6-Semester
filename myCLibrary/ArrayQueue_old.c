#include <stdlib.h>

typedef int Element;
typedef struct {
	Element* items;
	int capacity;
	int front;
	int rear;
} ArrayQueue;

ArrayQueue* AQ_new(int max) {
	ArrayQueue* pqueue;
	if (!(pqueue = calloc(1, sizeof(ArrayQueue)))) exit(1);
	if (!(pqueue->items = calloc(max + 1, sizeof(Element)))) exit(1);
	pqueue->capacity = max + 1;
	return pqueue;
}
void AQ_delete(ArrayQueue* pqueue) {
	free(pqueue->items);
	free(pqueue);
}
int AQ_isEmpty(ArrayQueue* pqueue) {
	return pqueue->front == pqueue->rear;
}
Element AQ_front(ArrayQueue* pqueue) {
	return pqueue->items[pqueue->front];
}
void AQ_push(ArrayQueue* pqueue, Element item) {
	const int rear = pqueue->rear;
	pqueue->items[rear] = item;
	pqueue->rear = (rear + 1) % pqueue->capacity;
}
Element AQ_pop(ArrayQueue* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) % pqueue->capacity;
	return pqueue->items[front];
}
int AQ_size(ArrayQueue* pqueue) {
	const int subtract = pqueue->rear - pqueue->front;
	if (subtract >= 0) return subtract;
	else return pqueue->capacity + subtract;
}
int AQ_isFull(ArrayQueue* pqueue) {
	return pqueue->front == (pqueue->rear + 1) % pqueue->capacity;
}
/*Element AQ_back(const ArrayQueue* pqueue) {
	const int capacity = pqueue->capacity;
	return pqueue->items[(pqueue->rear + capacity - 1) % capacity];
}*/

// The Simple Linear Queue (2023.7.17 Mon)
/* 

typedef int Element;
typedef struct {
	Element* items;
	int front;
	int rear;
} ArrayQueue;
ArrayQueue* AQ_new(int max) {
	ArrayQueue* pqueue;
	if (!(pqueue = calloc(1, sizeof(ArrayQueue)))) exit(1);
	if (!(pqueue->items = calloc(max, sizeof(Element)))) exit(1);
	return pqueue;
}
void AQ_delete(ArrayQueue* pqueue) {
	free(pqueue->items);
	free(pqueue);
}
int AQ_isEmpty(ArrayQueue* pqueue) {
	return pqueue->front == pqueue->rear;
}
Element AQ_front(ArrayQueue* pqueue) {
	return pqueue->items[pqueue->front];
}
void AQ_push(ArrayQueue* pqueue, Element item) {
	pqueue->items[pqueue->rear++] = item;
}
Element AQ_pop(ArrayQueue* pqueue) {
	return pqueue->items[pqueue->front++];
}
int AQ_size(ArrayQueue* pqueue) {
	return pqueue->rear - pqueue->front;
}

*/
