#include <stdio.h>
#include <stdlib.h>

#define MAXH          (100)
#define INF           (1000000)
#define UNIT_BLNAK    ('.')
#define UNIT_WALL     ('*')
#define UNIT_DOOR     ('#')
#define UNIT_PRISONER ('$')

typedef struct {
	int r;
	int c;
	int dist;
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
Nodeinfo AD_front(const ArrayDeque* pdeque) {
	return pdeque->items[pdeque->front];
}
Nodeinfo AD_back(const ArrayDeque* pdeque) {
	return pdeque->items[(pdeque->rear - 1 + pdeque->capacity) & (pdeque->capacity - 1)];
}
void AD_push_front(ArrayDeque* pdeque, Nodeinfo item) {
	const int f_before = (pdeque->front - 1 + pdeque->capacity) & (pdeque->capacity - 1);
	pdeque->front = f_before;
	pdeque->items[f_before] = item;
}
void AD_push_back(ArrayDeque* pdeque, Nodeinfo item) {
	const int rear = pdeque->rear;
	pdeque->rear = (rear + 1) & (pdeque->capacity - 1);
	pdeque->items[rear] = item;
}
Nodeinfo AD_pop_front(ArrayDeque* pdeque) {
	const int front = pdeque->front;
	pdeque->front = (front + 1) & (pdeque->capacity - 1);
	return pdeque->items[front];
}
void solve9376_dijkstra(int dist[][MAXH + 2], const char units[][MAXH + 3], const int H, const int W, const int start_r, const int start_c) {
	static int dx[4] = { +1,-1,0,0 };
	static int dy[4] = { 0,0,+1,-1 };
	// Any priority queue that maintains sorting can be used.
	ArrayDeque* deq = AD_new(MAXH * MAXH / 2);

	for (int i = 0; i <= H + 1; i++) for (int j = 0; j <= W + 1; j++) {
		dist[i][j] = INF;
	}

	AD_push_back(deq, (Nodeinfo) { start_r, start_c, 0 });

	while (!AD_empty(deq)) {
		Nodeinfo pos = AD_pop_front(deq);

		// I think this program will probably work robustly without the continue statement below.
		// In normal dijkstra, this check is required.
		// if (pos.dist > dist[pos.r][pos.c]) continue;

		for (int i = 0; i < 4; i++) {
			int r = pos.r + dx[i];
			int c = pos.c + dy[i];
			char u = units[r][c];

			if (r < 0 || r > H + 1 || c < 0 || c > W + 1) continue;

			if ((r == 0 || r == H + 1 || c == 0 || c == W + 1 || u == UNIT_BLNAK || u == UNIT_PRISONER) && pos.dist < dist[r][c]) {
				AD_push_front(deq, (Nodeinfo) { r, c, pos.dist });
				dist[r][c] = pos.dist;
			}
			else if (u == UNIT_DOOR && pos.dist + 1 < dist[r][c]) {
				AD_push_back(deq, (Nodeinfo) { r, c, pos.dist + 1 });
				dist[r][c] = pos.dist + 1;
			}
		}
	}

	AD_delete(deq);
}

void solve9376(const char units[][MAXH + 3], const int H, const int W) {
	static int dist1[MAXH + 2][MAXH + 2];
	static int dist2[MAXH + 2][MAXH + 2];
	static int dist3[MAXH + 2][MAXH + 2];
	struct Coordinate {
		int r;
		int c;
	} prisoner[2] = { 0 };

	for (int k = 0, i = 1; i <= H; i++) for (int j = 1; j <= W; j++) {
		if (units[i][j] == UNIT_PRISONER) {
			prisoner[k++] = (struct Coordinate){ i,j };
		}
	}

	solve9376_dijkstra(dist1, units, H, W, 0, 0);
	solve9376_dijkstra(dist2, units, H, W, prisoner[0].r, prisoner[0].c);
	solve9376_dijkstra(dist3, units, H, W, prisoner[1].r, prisoner[1].c);

	if (dist1[0][0] + dist2[0][0] + dist3[0][0] == 0) {
		// No need to open any doors.
		printf("0\n");
	}
	else {
		int dist_min_sum_of_three = INF;
		for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) {
			// The answer must occur in the DIST sum of the DOOR location.
			if (units[i][j] != UNIT_DOOR) continue;
			int sum = dist1[i][j] + dist2[i][j] + dist3[i][j];
			if (dist_min_sum_of_three > sum) dist_min_sum_of_three = sum;
		}
		printf("%d\n", dist_min_sum_of_three - 2);
	}
}
int main() {
	static char units[MAXH + 1][MAXH + 3];
	int TC, H, W;

	scanf("%d", &TC);

	do {
		scanf("%d%d ", &H, &W);
		for (int i = 0; i < H; i++) {
			fgets(&units[i + 1][1], sizeof(units[i + 1]) - 1, stdin); 
		}
		solve9376(units, H, W);
	} while (--TC > 0);
}