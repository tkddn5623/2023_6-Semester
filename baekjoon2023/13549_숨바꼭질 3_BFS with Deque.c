#include <stdio.h>
#include <stdlib.h>
#define MAXN (100000)

typedef struct {
    int pos;
    int time;
} Nodeinfo;

typedef struct {
	Nodeinfo* items;
	int capacity;
	int front;
	int rear;
} ArrayDeque;

ArrayDeque* AD_new(int required_size) {
	ArrayDeque* pdeque;
	int capacity;
	for (int i = 4; (capacity = 1 << i) < required_size; i++);
	if (!(pdeque = calloc(1, sizeof(ArrayDeque)))) exit(1);
	if (!(pdeque->items = calloc(capacity, sizeof(Nodeinfo)))) exit(1);
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
void AD_push_front(ArrayDeque* pdeque, Nodeinfo item) {
	const int f_before = (pdeque->front - 1 + pdeque->capacity) & (pdeque->capacity - 1);
	pdeque->items[f_before] = item;
	pdeque->front = f_before;
}
void AD_push_back(ArrayDeque* pdeque, Nodeinfo item) {
	const int rear = pdeque->rear;
	pdeque->items[rear] = item;
	pdeque->rear = (rear + 1) & (pdeque->capacity - 1);
}
Nodeinfo AD_pop_front(ArrayDeque* pdeque) {
	const int front = pdeque->front;
	pdeque->front = (front + 1) & (pdeque->capacity - 1);
	return pdeque->items[front];
}

void solve13549(int N, int K) {
    static int visited[MAXN];
    int states = -1;
    ArrayDeque* deq = AD_new(70000);

    AD_push_back(deq, (Nodeinfo) { N, 1 });

    while (!AD_empty(deq)) {
        Nodeinfo node = AD_pop_front(deq);

        if (node.pos == K) { states = node.time - 1; break; }
        if (visited[node.pos] && visited[node.pos] <= node.time) continue;

        visited[node.pos] = node.time;

        if (node.pos * 2 <= 100000) AD_push_front(deq, (Nodeinfo) { node.pos * 2, node.time });
        if (node.pos - 1 >= 0) AD_push_back(deq, (Nodeinfo) { node.pos - 1, node.time + 1 });
        if (node.pos + 1 <= 100000) AD_push_back(deq, (Nodeinfo) { node.pos + 1, node.time + 1 });
    }

    AD_delete(deq);
    printf("%d\n", states);
}
int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    solve13549(N, K);
}