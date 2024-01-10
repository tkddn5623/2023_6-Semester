// boj 1182, 1208
#include <stdio.h>
#include <stdlib.h>

#define MAXN (40)
#define HASH_MSB_BITS (21)
#define HASH_BLOCK_SIZE (1 << HASH_MSB_BITS)

typedef struct {
	int idx;
	int count;
} Countpair;

typedef struct {
	int pos;
	int value;
	int valid;
} Nodeinfo;

typedef struct _HNode {
	Countpair item;
	struct _HNode* next;
} HNode;

typedef struct {
	Nodeinfo* items;
	int capacity;
	int front;
	int rear;
} ArrayQueue;

typedef struct {
	int blocksize;
	int nodesize;
	int nodecount;
	HNode** tails;
	HNode* _edges;
} Hashtable;

int tiny_hash_i32(unsigned int k) {
	return (k * 2654435769u) >> (32 - HASH_MSB_BITS);
}
ArrayQueue* AQ_new(int required_size) {
	ArrayQueue* pqueue;
	int capacity;
	for (int i = 4; (capacity = 1 << i) < required_size; i++);
	if (!(pqueue = calloc(1, sizeof(ArrayQueue)))) exit(1);
	if (!(pqueue->items = calloc(capacity, sizeof(Nodeinfo)))) exit(1);
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
Nodeinfo AQ_front(const ArrayQueue* pqueue) {
	return pqueue->items[pqueue->front];
}
void AQ_push(ArrayQueue* pqueue, Nodeinfo item) {
	const int rear = pqueue->rear;
	pqueue->rear = (rear + 1) & (pqueue->capacity - 1);
	pqueue->items[rear] = item;
}
Nodeinfo AQ_pop(ArrayQueue* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) & (pqueue->capacity - 1);
	return pqueue->items[front];
}
Hashtable* HT_new(int blocksize, int nodesize) {
	Hashtable* table;
	if (!(table = malloc(sizeof(Hashtable)))) exit(1);
	if (!(table->tails = calloc(blocksize, sizeof(HNode*)))) exit(1);
	if (!(table->_edges = calloc(nodesize + blocksize, sizeof(HNode)))) exit(1);
	table->blocksize = blocksize;
	table->nodesize = nodesize + blocksize;
	table->nodecount = blocksize;
	for (int i = 0; i < blocksize; i++) {
		table->tails[i] = &table->_edges[i];
		table->tails[i]->next = table->tails[i];
	}
	return table;
}
void HT_delete(Hashtable* table) {
	free(table->_edges);
	free(table->tails);
	free(table);
}
void HT_push(Hashtable* table, Countpair item) {
	int index = tiny_hash_i32(item.idx);
	table->_edges[table->nodecount].item = item;
	table->_edges[table->nodecount].next = table->tails[index]->next;
	table->tails[index]->next = &table->_edges[table->nodecount];
	table->tails[index] = &table->_edges[table->nodecount++];
}
Countpair* HT_search(const Hashtable* table, int key) {
	int index = tiny_hash_i32(key);
	HNode* head = &table->_edges[index];
	for (HNode* cur = head->next; cur != head; cur = cur->next) {
		if (cur->item.idx == key) return &cur->item;
	}
	return NULL;
}
long long _solve1208_table_traversal(const Hashtable* ht1, const Hashtable* ht2, int S) {
	long long sum = 0;
	for (int nc = ht1->nodecount, i = ht1->blocksize; i < nc; i++) {
		Countpair pair1 = ht1->_edges[i].item;
		Countpair* pair2;
		//printf("TRV: %d\n", pair1.idx);
		if ((pair2 = HT_search(ht2, S - pair1.idx))) {
			sum += (long long)pair1.count * pair2->count;
		}
	}
	return sum;
}
void _solve1208_fill_table(const int seq[], int N, Hashtable* ht) {
	ArrayQueue* que = AQ_new(1 << (N + 1));

	AQ_push(que, (Nodeinfo) { 0, 0, 0x1 });
	AQ_push(que, (Nodeinfo) { 0, seq[0], 0x1 });

	while (!AQ_empty(que)) {
		Nodeinfo node = AQ_pop(que);

		if (node.valid) {
			Countpair* pair;
			if ((pair = HT_search(ht, node.value))) pair->count++;
			else HT_push(ht, (Countpair) { node.value, 1 });
		}

		if (node.pos + 1 < N) {
			AQ_push(que, (Nodeinfo) { node.pos + 1, node.value, 0x0 });
			AQ_push(que, (Nodeinfo) { node.pos + 1, node.value + seq[node.pos + 1], 0x1 });
		}
	}

	AQ_delete(que);
}
void solve1208(const int seq[], int N, int S) {
	if (N == 1) {
		printf("%s\n", S == seq[0] ? "1" : "0");
		return;
	}
	Hashtable* ht1 = HT_new(HASH_BLOCK_SIZE, HASH_BLOCK_SIZE);
	Hashtable* ht2 = HT_new(HASH_BLOCK_SIZE, HASH_BLOCK_SIZE);

	_solve1208_fill_table(&seq[0], N / 2, ht1);
	_solve1208_fill_table(&seq[N / 2], N - (N / 2), ht2);

	long long answer = _solve1208_table_traversal(ht1, ht2, S) - (S == 0 ? 1 : 0);

	printf("%lld\n", answer);

	HT_delete(ht1);
	HT_delete(ht2);
}
int main() {
	//freopen("i.txt", "r", stdin);
	static int seq[MAXN];
	int N, S;
	scanf("%d%d", &N, &S);
	for (int i = 0; i < N; i++) { scanf("%d", &seq[i]); }
	solve1208(seq, N, S);
}