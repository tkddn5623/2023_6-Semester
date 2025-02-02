#include <stdio.h>
#include <stdlib.h>
// #include <time.h>

typedef struct {
	int* items;
	int capacity;
	int front;
	int rear;
} ArrayQueue;

typedef struct _GNode {
	int id;
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
void GR_insert(Graph* graph, int from, int to) {
	graph->_edges[graph->edgecount].id = to;
	graph->_edges[graph->edgecount].next = graph->tails[from]->next;
	graph->tails[from]->next = &graph->_edges[graph->edgecount];
	graph->tails[from] = &graph->_edges[graph->edgecount++];
}
void solve11437_setup(const Graph* graph, int parent[], int depth[]) {
	ArrayQueue* queue = AQ_new(graph->vtxsize / 2);

	parent[1] = -1;
	depth[1] = 1;
	AQ_push(queue, 1);

	while (!AQ_empty(queue)) {
		int vtx = AQ_pop(queue);

		for (GNode* head = &graph->_edges[vtx], *cur = head->next; cur != head; cur = cur->next) {
			if (parent[cur->id]) continue;
			parent[cur->id] = vtx;
			depth[cur->id] = depth[vtx] + 1;
			AQ_push(queue, cur->id);
		}
	}

	AQ_delete(queue);
}
void solve11437_query(const int parent[], const int depth[], int v[2]) {
	int d[2] = { depth[v[0]], depth[v[1]] };
	int v_picked, p;

	while (v[0] != v[1]) {
		/*
		* Below code 8 times slower... (4.5 sec)
		
		v_picked = d[0] >= d[1] ? 0 : 1;

		p = parent[v[v_picked]];
		d[v_picked] = depth[p];
		v[v_picked] = p;
		
		*/
		
		if (d[0] >= d[1]) {
			d[0] = depth[parent[v[0]]];
			v[0] = parent[v[0]];
		}
		else {
			d[1] = depth[parent[v[1]]];
			v[1] = parent[v[1]];
		}
	}

	printf("%d\n", v[0]);
}
int main() {
	// freopen("i.txt", "r", stdin);
	// freopen("o.txt", "w", stdout);
	// double RT = (double)clock() / CLOCKS_PER_SEC;
	Graph* graph;
	int* parent;
	int* depth;
	int V, Q;

	scanf("%d", &V);
	if (!(parent = calloc(V + 1, sizeof(int)))) exit(1);
	if (!(depth = calloc(V + 1, sizeof(int)))) exit(1);
	graph = GR_new(V + 1, V * 2);

	for (int i = 0; i < V - 1; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		GR_insert(graph, v1, v2);
		GR_insert(graph, v2, v1);
	}

	solve11437_setup(graph, parent, depth);
	GR_delete(graph);

	scanf("%d", &Q);

	for (int i = 0; i < Q; i++) {
		int v[2];
		scanf("%d%d", &v[0], &v[1]);
		solve11437_query(parent, depth, v);
	}

	free(parent);
	free(depth);
	// double ET = (double)clock() / CLOCKS_PER_SEC;
	// printf("time: %.3f\n", ET - RT);
}