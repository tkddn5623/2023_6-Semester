#include <stdlib.h>

typedef int Element;

typedef struct {
	Element* items;
	int top;
#ifdef AUTOMATIC_RESIZE
	int capacity;
#endif
} ArrayStack;

ArrayStack* AS_new(int max) {
	ArrayStack* pstack;
	pstack = malloc(sizeof(ArrayStack)); if (!pstack) exit(1);
	pstack->items = calloc(max, sizeof(Element)) if (!pstack->items) exit(1);
	pstack->top = -1;
#ifdef AUTOMATIC_RESIZE
	pstack->capacity = max;
#endif
	return pstack;
}
void AS_delete(ArrayStack* pstack) {
	free(pstack->items);
	free(pstack);
}
int AS_empty(const ArrayStack* pstack) {
	return pstack->top == -1;
}
Element AS_top(const ArrayStack* pstack) {
	return pstack->items[pstack->top];
}
void AS_push(ArrayStack* pstack, int item) {
#ifdef AUTOMATIC_RESIZE
	if (pstack->top == pstack->capacity - 1) {
		pstack->items = realloc(pstack->items, (pstack->capacity *= 2) * sizeof(Element));
	}
#endif
	pstack->items[++pstack->top] = item;
}
char AS_pop(ArrayStack* pstack) {
	return pstack->items[pstack->top--];
}


/*
int capacity;
pstack->capacity = max;

int AS_full(const ArrayStack* pstack) {
	return pstack->top == pstack->capacity - 1;
}
*/

/*
* 2024.1.20.
* 
* Function names imitates C++ STL methods.
*
*
* 2024.2.10.
* Now, the stack supports automatic resize.
*/