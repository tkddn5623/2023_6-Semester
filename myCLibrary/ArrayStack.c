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
	if (!(pstack = malloc(sizeof(ArrayStack)))) exit(1);
	if (!(pstack->items = calloc(max, sizeof(Element)))) exit(1);
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
	pstack->items[++(pstack->top)] = item;
#ifdef AUTOMATIC_RESIZE
	if (pstack->top == pstack->capacity - 1) {
		pstack->items = realloc(pstack->items, (pstack->capacity *= 2) * sizeof(Element));
	}
#endif
}
char AS_pop(ArrayStack* pstack) {
	return pstack->items[(pstack->top)--];
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