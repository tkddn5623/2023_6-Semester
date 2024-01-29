#include <stdio.h>
#include <stdlib.h>

#define MAXN (50)
#define INF (200000000)

typedef struct {
	int* items;
	int capacity;
	int front;
	int rear;
} ArrayQueue;

typedef struct _GNode {
	int id;
	int weight;
	struct _GNode* next;
} GNode;

typedef struct {
	int vtxsize;
	int edgesize;
	int edgecount;
	GNode** tails;
	GNode* _edges;
} Graph;

ArrayQueue* AQ_new(int required_size) {
	ArrayQueue* pqueue;
	int capacity;
	for (int i = 4; (capacity = 1 << i) < required_size; i++);
	if (!(pqueue = calloc(1, sizeof(ArrayQueue)))) exit(1);
	if (!(pqueue->items = calloc(capacity, sizeof(int)))) exit(1);
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
void AQ_push(ArrayQueue* pqueue, int item) {
	const int rear = pqueue->rear;
	pqueue->rear = (rear + 1) & (pqueue->capacity - 1);
	pqueue->items[rear] = item;
}
int AQ_pop(ArrayQueue* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) & (pqueue->capacity - 1);
	return pqueue->items[front];
}
Graph* GR_new(int vtxsize, int edgesize) {
	Graph* graph;
	if ((graph = malloc(sizeof(Graph))) == NULL) exit(1);
	if ((graph->tails = calloc(vtxsize, sizeof(GNode*))) == NULL) exit(1);
	if ((graph->_edges = calloc(edgesize + vtxsize, sizeof(GNode))) == NULL) exit(1);
	graph->vtxsize = vtxsize;
	graph->edgesize = edgesize + vtxsize;
	graph->edgecount = vtxsize;
	for (int i = 0; i < vtxsize; i++) {
		graph->tails[i] = &graph->_edges[i];
		graph->tails[i]->next = graph->tails[i];
	}
	return graph;
}
void GR_delete(Graph* graph) {
	free(graph->_edges);
	free(graph->tails);
	free(graph);
}
void GR_insert(Graph* graph, int from, int to, int weight) {
	graph->_edges[graph->edgecount].id = to;
	graph->_edges[graph->edgecount].weight = weight;
	graph->_edges[graph->edgecount].next = graph->tails[from]->next;
	graph->tails[from]->next = &graph->_edges[graph->edgecount];
	graph->tails[from] = &graph->_edges[graph->edgecount++];
}
int solve1219_Bellman_Ford(long long dist[], const Graph* graph, const int profit[], int start, int end) {
	const int vtxmax = graph->vtxsize - 1;
	
	for (int i = 0; i <= vtxmax; i++) { dist[i] = INF; }
	dist[start] = -profit[start];

	// A loop of (vtxmax) is enough to propagate.
	for (int i = 0; i < vtxmax; i++) for (int j = 0; j <= vtxmax; j++) {
		for (GNode* head = &graph->_edges[j], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (dist[j] == INF || dist[id] <= dist[j] - profit[id] + weight) continue;
			dist[id] = dist[j] - profit[id] + weight;
		}
	}

	ArrayQueue* bfsq = AQ_new(vtxmax + 1);
	int* bfs_visited = calloc(vtxmax + 1, sizeof(int)); if (!bfs_visited) exit(1);
	int minuscycle = 0;

	// Minus cycle check
	for (int j = 0; j <= vtxmax; j++) {
		for (GNode* head = &graph->_edges[j], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (dist[j] == INF || dist[id] <= dist[j] - profit[id] + weight) continue;
			if (bfs_visited[id]) continue;
			AQ_push(bfsq, id);
			bfs_visited[id] = 1;
		}
	}

	// Is it possible to reach end vtx?
	while (!AQ_empty(bfsq)) {
		int vtx = AQ_pop(bfsq);

		if (vtx == end) { minuscycle = 1; break; }

		for (GNode* head = &graph->_edges[vtx], *cur = head->next; cur != head; cur = cur->next) {
			int id = cur->id;
			if (bfs_visited[id]) continue;
			AQ_push(bfsq, id);
			bfs_visited[id] = 1;
		}
	}

	AQ_delete(bfsq);
	free(bfs_visited);

	return minuscycle;
}
int main() {
	//freopen("i.txt", "r", stdin);
	static long long dist[MAXN];
	static int profit[MAXN];
	int N, S, E, M, minus_cycle;

	scanf("%d%d%d%d", &N, &S, &E, &M);
	Graph* g = GR_new(N, M);

	for (int i = 0; i < M; i++) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		GR_insert(g, from, to, weight);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &profit[i]);
	}

	minus_cycle = solve1219_Bellman_Ford(dist, g, profit, S, E);
	GR_delete(g);

	if (dist[E] == INF)		printf("gg\n");
	else if (minus_cycle)	printf("Gee\n");
	else					printf("%lld\n", -dist[E]);
}