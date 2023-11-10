#include <stdlib.h>
#include "Trie.h"
/*
#define MAXCOL (26)
typedef struct _TreeNode {
	struct _TreeNode* next[MAXCOL];
	int state; // 1st bit: is final state?, 2nd bit: does it have child?
} TrieNode;
typedef struct {
	TrieNode* nodes;
	int len;
} Trie;
*/
Trie* Trie_new(int node) {
	Trie* t = malloc(sizeof(Trie)); if (!t) exit(1);
	if (!(t->nodes = calloc(node, sizeof(TrieNode)))) exit(1);
	t->len = 1;
	return t;
}
void Trie_delete(Trie* trie) {
	free(trie->nodes);
	free(trie);
}
void Trie_insert(Trie* trie, const char* str) {
	TrieNode* pn = &trie->nodes[0];
	int value;
	while (pn) {
		value = *str++ - '0';
		if (value < 0) {
			pn->state |= 0x1;
			break;
		}
		if (!pn->next[value]) {
			pn->next[value] = &trie->nodes[trie->len++];
			pn->state |= 0x2;
		}
		pn = pn->next[value];
	}
}
int _Trie_search(TrieNode* node) {
	if (node->state == 0x3) return 0;
	else if (node->state == 0x2) {
		for (int i = 0; i < MAXCOL; i++) {
			if (node->next[i] && !_Trie_search(node->next[i])) return 0;
		}
	}
	return 1;
}


/*
* 2023.7.19 Wed
*/