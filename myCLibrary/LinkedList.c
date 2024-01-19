#include <stdlib.h>

#define LL_push_back(list, item)  LL_insert(list, list->tails, item)
#define LL_push_front(list, item) LL_insert(list, list->_nodes, item)

typedef int Element;

typedef struct _LNode {
	Element item;
	struct _LNode* next;
} LNode;

typedef struct {
	int nodes_count;
	LNode* tails;
	LNode* _nodes;
} List;

List* LL_new(int required_size) {
	List* list;
	if (!(list =calloc(1, sizeof(List)))) exit(1);
	if (!(list->_nodes = calloc(required_size + 1, sizeof(LNode)))) exit(1);
	list->tails = list->_nodes[0].next = &list->_nodes[0];
	list->nodes_count = 1;
	return list;
}
void LL_delete(List* list) {
	free(list->_nodes);
	free(list);
}
LNode* LL_insert(List* list, LNode* cur, Element item) {
	LNode* new_node = &list->_nodes[list->nodes_count++];
	if (list->tails == cur) list->tails = new_node;
	new_node->item = item;
	new_node->next = cur->next;
	cur->next = new_node;
	return new_node;
}
void LL_erase(List* list, LNode* cur) {
	if (list->tails == cur->next) list->tails = cur;
	cur->next = cur->next->next;
}

/* Traversal example:

for (LNode* head = list->tails->next, *cur = head->next; cur != head; cur = cur->next) {
	printf("%d ", cur->item);
}

*/

/*
void LL_flush(List* list) {
	list->tails = list->_nodes[0].next = &list->_nodes[0];
	list->nodes_count = 1;
}
*/


/*
* 2024-01-20 Sat
*
* Linked list renewal (imitates C++ STL)
*/