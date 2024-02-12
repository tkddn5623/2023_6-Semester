#include <stdio.h>
#include <stdlib.h>

#define AUTOMATIC_RESIZE
#define MAXV (20000)
#define INF  (1000000000)

typedef struct {
	int value;
	int priority;
} HNode;

typedef struct _GNode {
	union { struct { int id, weight; }; struct _GNode* tail; };
	struct _GNode* next;
} GNode;

typedef struct {
	HNode* items;
	int size;
#ifdef AUTOMATIC_RESIZE
	int capacity;
#endif
} ArrayHeap;

typedef struct {
	int vtxsize;
	int edgesize;
	int edgecount;
	GNode* edges;
} Graph;


ArrayHeap* AH_new(int max) {
	ArrayHeap* pheap;
	if (!(pheap = calloc(1, sizeof(ArrayHeap)))) exit(1);
	if (!(pheap->items = calloc(max + 1, sizeof(HNode)))) exit(1);
#ifdef AUTOMATIC_RESIZE
	pheap->capacity = max + 1;
#endif
	return pheap;
}
void AH_delete(ArrayHeap* pheap) {
	free(pheap->items);
	free(pheap);
}
int AH_empty(ArrayHeap* pheap) {
	return pheap->size == 0;
}
void AH_push(ArrayHeap* pheap, HNode item) {
#ifdef AUTOMATIC_RESIZE
	if (pheap->size == pheap->capacity - 1) {
		pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof(HNode)); // if (!pheap->items) exit(1);
	}
#endif
	int parent, child = pheap->size + 1;
	while (child > 1) {
		if (pheap->items[(parent = child / 2)].priority <= item.priority) break; // Minheap
		pheap->items[child] = pheap->items[parent];
		child = parent;
	}
	pheap->items[child] = item;
	pheap->size++;
}
HNode AH_pop(ArrayHeap* pheap) {
	const int size = pheap->size;
	const HNode top = pheap->items[1];
	const HNode last = pheap->items[size];
	int child, parent = 1;
	while ((child = parent * 2) <= size) {
		if (child < size && pheap->items[child + 1].priority < pheap->items[child].priority) child++; // Minheap
		if (last.priority <= pheap->items[child].priority) break; // Minheap
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->size--;
	return top;
}
Graph* GR_new(int vtxsize, int edgesize) {
	Graph* graph;
	if (!(graph = malloc(sizeof(Graph)))) exit(1);
	if (!(graph->edges = calloc(edgesize + vtxsize, sizeof(GNode)))) exit(1);
	graph->vtxsize = vtxsize;
	graph->edgesize = edgesize + vtxsize;
	graph->edgecount = vtxsize;
	for (int i = 0; i < vtxsize; i++) {
		graph->edges[i].next = &graph->edges[i];
		graph->edges[i].tail = &graph->edges[i];
	}
	return graph;
}
void GR_delete(Graph* graph) {
	free(graph->edges);
	free(graph);
}
void GR_insert(Graph* graph, int from, int to, int weight) {
	graph->edges[graph->edgecount] = (GNode){ .id = to, .weight = weight, .next = &graph->edges[from] };
	graph->edges[from].tail->next = &graph->edges[graph->edgecount];
	graph->edges[from].tail = &graph->edges[graph->edgecount++];
}
void solve1753_dijkstra(int dist[], Graph* graph, int start) {
	for (int j = graph->vtxsize, i = 0; i < j; i++) { dist[i] = INF; }
	dist[start] = 0;

	ArrayHeap* heap = AH_new(1024);
	AH_push(heap, (HNode) { start, 0 });

	while (!AH_empty(heap)) {
		HNode e = AH_pop(heap);

		if (e.priority > dist[e.value]) continue;

		for (GNode* head = &graph->edges[e.value], *cur = head->next; cur != head; cur = cur->next) {
			int weight = e.priority + cur->weight, id = cur->id;
			if (weight < dist[id]) {
				dist[id] = weight;
				AH_push(heap, (HNode) { id, weight });
			}
		}
	}

	AH_delete(heap);
}
int main() {
	//freopen("i.txt", "r", stdin);
	static int dist[MAXV + 1];
	int V, E, S;
	Graph* graph;

	scanf("%d%d%d", &V, &E, &S);
	graph = GR_new(V + 1, E);

	for (int i = 0; i < E; i++) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		GR_insert(graph, from, to, weight);
	}

	solve1753_dijkstra(dist, graph, S);
	GR_delete(graph);

	for (int i = 1; i <= V; i++) {
		if (dist[i] == INF) printf("INF\n");
		else printf("%d\n", dist[i]);
	}
}