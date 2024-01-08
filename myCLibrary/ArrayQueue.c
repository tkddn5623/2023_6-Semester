#include <stdlib.h>

typedef int Element;

typedef struct {
	Element* items;
	int capacity;
	int front;
	int rear;
} ArrayQueue;

ArrayQueue* AQ_new(int required_size) {
	ArrayQueue* pqueue;
	int capacity;
	for (int i = 4; (capacity = 1 << i) < required_size; i++);
	if (!(pqueue = calloc(1, sizeof(ArrayQueue)))) exit(1);
	if (!(pqueue->items = calloc(capacity, sizeof(Element)))) exit(1);
	pqueue->capacity = capacity;
	return pqueue;
}
void AQ_delete(ArrayQueue* pqueue) {
	free(pqueue->items);
	free(pqueue);
}
int AQ_empty(const ArrayQueue* pqueue) {
	return pqueue->front == pqueue->rear;
}
Element AQ_front(const ArrayQueue* pqueue) {
	return pqueue->items[pqueue->front];
}
void AQ_push(ArrayQueue* pqueue, Element item) {
	const int rear = pqueue->rear;
	pqueue->rear = (rear + 1) & (pqueue->capacity - 1);
	pqueue->items[rear] = item;
}
Element AQ_pop(ArrayQueue* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) & (pqueue->capacity - 1);
	return pqueue->items[front];
}


int AQ_full(const ArrayQueue* pqueue) {
	return pqueue->front == ((pqueue->rear + 1) & (pqueue->capacity - 1));
}
int AQ_size(const ArrayQueue* pqueue) {
	return (pqueue->rear - pqueue->front + pqueue->capacity) & (pqueue->capacity - 1);
}

/*
* In its strict definition, queues do not have this feature.
* Element AQ_back(const ArrayQueue* pqueue) {
*	return pqueue->items[(pqueue->rear + pqueue->capacity - 1) & (pqueue->capacity - 1)];
*}
*/

/*
* 2024-01-04 Thu
*
* The optimized Queue
*
* By replacing the % operation with bitwise &,
* performance is very close to linear queue.
*
*
* 2024-01-08 Mon
*
* Camel cases changed to snake cases
*/
