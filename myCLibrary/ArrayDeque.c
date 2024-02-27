#include <stdlib.h>

typedef int Element;

typedef struct {
	Element* items;
	int capacity;
	int front;
	int rear;
} ArrayDeque;

ArrayDeque* AD_new(int required_size) {
	ArrayDeque* pdeque;
	int capacity;
	for (int i = 4; (capacity = 1 << i) < required_size; i++);
	pdeque = calloc(1, sizeof(ArrayDeque)); if (!pdeque) exit(1);
	pdeque->items = calloc(capacity, sizeof(Element)); if (!pdeque->items) exit(1);
	pdeque->capacity = capacity;
	return pdeque;
}
void AD_delete(ArrayDeque* pdeque) {
	free(pdeque->items);
	free(pdeque);
}
int AD_empty(const ArrayDeque* pdeque) {
	return pdeque->front == pdeque->rear;
}
Element AD_front(const ArrayDeque* pdeque) {
	return pdeque->items[pdeque->front];
}
Element AD_back(const ArrayDeque* pdeque) {
	return pdeque->items[(pdeque->rear - 1 + pdeque->capacity) & (pdeque->capacity - 1)];
}
#ifdef AUTOMATIC_RESIZE
void AD_resize(ArrayDeque* pdeque) {
	const int front = pdeque->front, rear = pdeque->rear, capacity = pdeque->capacity;
	if (front - rear == 1 || front - rear == 1 - capacity) {
		pdeque->items = realloc(pdeque->items, (deque->capacity = capacity * 2) * sizeof(Element)); if (!pdeque->items) exit(1);
		if (front < rear) return;
		else if (rear <= capacity - front) {
			for (int i = 0; i < rear; i++) { pdeque->items[i + capacity] = pdeque->items[i]; }
			pdeque->rear = rear + capacity;
		}
		else {
			for (int i = front; i < capacity; i++) { pdeque->items[i + capacity] = pdeque->items[i]; }
			pdeque->front = front + capacity;
		}
	}
}
#endif
void AD_push_front(ArrayDeque* pdeque, Element item) {
#ifdef AUTOMATIC_RESIZE
	AD_resize(pdeque);
#endif
	const int f_before = (pdeque->front - 1 + pdeque->capacity) & (pdeque->capacity - 1);
	pdeque->front = f_before;
	pdeque->items[f_before] = item;
}
void AD_push_back(ArrayDeque* pdeque, Element item) {
#ifdef AUTOMATIC_RESIZE
	AD_resize(pdeque);
#endif
	const int rear = pdeque->rear;
	pdeque->rear = (rear + 1) & (pdeque->capacity - 1);
	pdeque->items[rear] = item;
}
Element AD_pop_front(ArrayDeque* pdeque) {
	const int front = pdeque->front;
	pdeque->front = (front + 1) & (pdeque->capacity - 1);
	return pdeque->items[front];
}
Element AD_pop_back(ArrayDeque* pdeque) {
	const int r_before = (pdeque->rear - 1 + pdeque->capacity) & (pdeque->capacity - 1);
	pdeque->rear = r_before;
	return pdeque->items[r_before];
}

/*
int AD_full(const ArrayDeque* pdeque) {
	return pdeque->front == ((pdeque->rear + 1) & (pdeque->capacity - 1));
}
int AD_size(const ArrayDeque* pdeque) {
	return (pdeque->rear - pdeque->front + pdeque->capacity) & (pdeque->capacity - 1);
}
*/



/*
* 2024-01-08 Mon.
* Improved readability
* Modular operation optimization
*
* 2024.2.11 Sun
* Dynamic resize support (But, unlike stack and heap, it is slow)
*/