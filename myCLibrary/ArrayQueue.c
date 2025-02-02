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
	pqueue = calloc(1, sizeof(ArrayQueue)); if (!pqueue) exit(1);
	pqueue->items = calloc(capacity, sizeof(Element)); if (!pqueue->items) exit(1);
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
	if (front - rear == 1 || front - rear == 1 - capacity) {
		pqueue->items = realloc(pqueue->items, (pqueue->capacity = capacity * 2) * sizeof(Element)); if (!pqueue->items) exit(1);
		if (front < rear) return;
		else if (rear <= capacity - front) {
			for (int i = 0; i < rear; i++) { pqueue->items[i + capacity] = pqueue->items[i]; }
			pqueue->rear = rear + capacity;
		}
		else {
			for (int i = front; i < capacity; i++) { pqueue->items[i + capacity] = pqueue->items[i]; }
			pqueue->front = front + capacity;
		}
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
