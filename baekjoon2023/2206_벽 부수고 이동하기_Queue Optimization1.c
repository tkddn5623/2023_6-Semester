#include <stdio.h>
#include <stdlib.h>
#define MAXN (1000)
#define QUEUE_CAPACITY (1 << 18)
#define INF (100000000)

typedef struct {
	int r;
	int c;
} Nodeinfo;

typedef struct {
	Nodeinfo* items;
	//int capacity;
	int front;
	int rear;
} ArrayQueue;

ArrayQueue* AQ_new() {
	ArrayQueue* pqueue;
	if (!(pqueue = calloc(1, sizeof(ArrayQueue)))) exit(1);
	if (!(pqueue->items = calloc(QUEUE_CAPACITY, sizeof(Nodeinfo)))) exit(1);
	return pqueue;
}
void AQ_delete(ArrayQueue* pqueue) {
	free(pqueue->items);
	free(pqueue);
}
int AQ_isEmpty(ArrayQueue* pqueue) {
	return pqueue->front == pqueue->rear;
}
Nodeinfo AQ_front(ArrayQueue* pqueue) {
	return pqueue->items[pqueue->front];
}
void AQ_push(ArrayQueue* pqueue, Nodeinfo item) {
	const int rear = pqueue->rear;
	pqueue->items[rear] = item;
	pqueue->rear = (rear + 1) & (QUEUE_CAPACITY - 1);
}
Nodeinfo AQ_pop(ArrayQueue* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) & (QUEUE_CAPACITY - 1);
	return pqueue->items[front];
}
void solve2206(const char wall[][MAXN + 3], const int sz_row, const int sz_col) {
	static const int dx[4] = { +1, -1, 0, 0 };
	static const int dy[4] = { 0, 0, +1, -1 };
	static int dist[MAXN + 1][MAXN + 1];
	ArrayQueue* que = AQ_new();
	int state = -1;

	for (int i = 0; i < sz_row; i++) for (int j = 0; j < sz_col; j++) {
		// 'dist' indicates not only actual distance,
		// also the wall was broken on the way.
		dist[i + 1][j + 1] = INF;
	}

	dist[1][1] = 1;
	AQ_push(que, (Nodeinfo) { 1, 1 });

	while (!AQ_isEmpty(que)) {
		Nodeinfo pos = AQ_pop(que);

		if (pos.r == sz_row && pos.c == sz_col) { state = dist[pos.r][pos.c] % (INF / 2); break; }

		for (int i = 0; i < 4; i++) {
			int row = pos.r + dx[i];
			int col = pos.c + dy[i];
			int d;

			if (row < 1 || row > sz_row || col < 1 || col > sz_col) continue;

			d = dist[pos.r][pos.c] + 1 + (wall[row][col] & 0xf) * (INF / 2);

			if (d >= dist[row][col]) continue;

			dist[row][col] = d;
			AQ_push(que, (Nodeinfo) { row, col });
		}
	}
	AQ_delete(que);
	printf("%d\n", state);
}
int main() {
	// wall would be considered to be a logical not of adjmat.
	static char wall[MAXN + 1][MAXN + 3];
	int sz_row, sz_col;

	// Read input
	scanf("%d%d ", &sz_row, &sz_col);
	for (int i = 0; i < sz_row; i++) {
		fgets(&wall[i + 1][1], sizeof(wall[i + 1]) - 1, stdin);
	}

	// Solve problem
	solve2206(wall, sz_row, sz_col);
}