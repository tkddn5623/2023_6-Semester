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
#ifdef AUTOMATIC_RESIZE
void AQ_resize(ArrayQueue* pqueue) {
	const int front = pqueue->front, rear = pqueue->rear, capacity = pqueue->capacity;
	const int sz = (rear - front + capacity) & (capacity - 1);
	if (sz == capacity - 1) {
		Element* items2 = calloc(capacity * 2, sizeof(Element));
		for (int i = 0; i < sz; i++) {
			items2[i] = pqueue->items[(front + i) & (capacity - 1)];
		}
		free(pqueue->items);
		*pqueue = (ArrayQueue){ items2, capacity * 2, 0, sz };
	}
}
#endif
void AQ_push(ArrayQueue* pqueue, Element item) {
#ifdef AUTOMATIC_RESIZE
	AQ_resize(pqueue);
#endif
	const int rear = pqueue->rear;
	pqueue->rear = (rear + 1) & (pqueue->capacity - 1);
	pqueue->items[rear] = item;
}
Element AQ_pop(ArrayQueue* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) & (pqueue->capacity - 1);
	return pqueue->items[front];
}
Element AQ_front(const ArrayQueue* pqueue) {
	return pqueue->items[pqueue->front];
}

/*
int AQ_full(const ArrayQueue* pqueue) {
	return pqueue->front == ((pqueue->rear + 1) & (pqueue->capacity - 1));
}
int AQ_size(const ArrayQueue* pqueue) {
	return (pqueue->rear - pqueue->front + pqueue->capacity) & (pqueue->capacity - 1);
}
*/



/*
* 2024-01-04 Thu
* The optimized Queue
*
* By replacing the % operation with bitwise &,
* performance is very close to linear queue.
*
*
* 2024-01-08 Mon
* Camel cases changed to snake cases
*
* 2024.1.22 Mon
* AQ_front moved below.
*
* 2024.2.11 Sun
* Dynamic resize support (But, unlike stack and heap, it is slow)
*/
