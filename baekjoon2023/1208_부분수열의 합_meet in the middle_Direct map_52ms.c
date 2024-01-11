// boj 1182, 1208
#include <stdio.h>
#include <stdlib.h>

#define MAXN (40)
#define MAXI (100000)

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
long long  _solve1208_impl(const int seq[], int N, int S, int table[], int state) {
	long long answer = 0;
	ArrayQueue* que = AQ_new(1 << (N + 1));

	AQ_push(que, (Nodeinfo) { 0, 0, 0x1 });
	AQ_push(que, (Nodeinfo) { 0, seq[0], 0x1 });

	while (!AQ_empty(que)) {
		Nodeinfo node = AQ_pop(que);

		if (node.valid) {
			if (state == 0x0) table[MAXN * MAXI + node.value]++;
			else if (state == 0x1) answer += table[MAXN * MAXI - node.value + S];
		}

		if (node.pos + 1 < N) {
			AQ_push(que, (Nodeinfo) { node.pos + 1, node.value, 0x0 });
			AQ_push(que, (Nodeinfo) { node.pos + 1, node.value + seq[node.pos + 1], 0x1 });
		}
	}

	AQ_delete(que);
	return answer;
}
void solve1208(const int seq[], int N, int S) {
	if (N == 1) {
		printf("%s\n", S == seq[0] ? "1" : "0");
		return;
	}
	static int table[MAXN * MAXI * 2 + 1];
	long long answer;

	_solve1208_impl(&seq[0], N / 2, S, table, 0x0);
	answer = _solve1208_impl(&seq[N / 2], N - (N / 2), S, table, 0x1) - (S == 0 ? 1 : 0);;

	printf("%lld\n", answer);
}
int main() {
	static int seq[MAXN];
	int N, S;
	scanf("%d%d", &N, &S);
	for (int i = 0; i < N; i++) { scanf("%d", &seq[i]); }
	solve1208(seq, N, S);
}